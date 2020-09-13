#pragma once
#include <Random.hxx>  // added by amir
#include <AveragingMethod.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModels::Stochastic<CloudType>::Stochastic
(
	const dictionary& dict,
	CloudType& owner
)
	:
	IsotropyModel<CloudType>(dict, owner, typeName)
{}


template<class CloudType>
tnbLib::IsotropyModels::Stochastic<CloudType>::Stochastic
(
	const Stochastic<CloudType>& cm
)
	:
	IsotropyModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModels::Stochastic<CloudType>::~Stochastic()
{}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::IsotropyModels::Stochastic<CloudType>::sampleGauss()
{
	static bool isCached = true;
	static scalar xCached;

	if (isCached)
	{
		isCached = false;

		return xCached;
	}
	else
	{
		Random& rndGen = this->owner().rndGen();

		scalar f, m, x, y;

		do
		{
			x = 2.0*rndGen.sample01<scalar>() - 1.0;
			y = 2.0*rndGen.sample01<scalar>() - 1.0;
			m = x * x + y * y;
		} while (m >= 1.0 || m == 0.0);

		f = sqrt(-2.0*log(m) / m);
		xCached = x * f;
		isCached = true;

		return y * f;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::IsotropyModels::Stochastic<CloudType>::calculate()
{
	const fvMesh& mesh = this->owner().mesh();
	const scalar deltaT(this->owner().db().time().deltaTValue());
	Random& rndGen = this->owner().rndGen();

	const scalar oneBySqrtThree = sqrt(1.0 / 3.0);

	const AveragingMethod<scalar>& volumeAverage =
		mesh.lookupObject<AveragingMethod<scalar>>
		(
			this->owner().name() + ":volumeAverage"
			);
	const AveragingMethod<scalar>& radiusAverage =
		mesh.lookupObject<AveragingMethod<scalar>>
		(
			this->owner().name() + ":radiusAverage"
			);
	const AveragingMethod<vector>& uAverage =
		mesh.lookupObject<AveragingMethod<vector>>
		(
			this->owner().name() + ":uAverage"
			);
	const AveragingMethod<scalar>& uSqrAverage =
		mesh.lookupObject<AveragingMethod<scalar>>
		(
			this->owner().name() + ":uSqrAverage"
			);
	const AveragingMethod<scalar>& frequencyAverage =
		mesh.lookupObject<AveragingMethod<scalar>>
		(
			this->owner().name() + ":frequencyAverage"
			);
	const AveragingMethod<scalar>& massAverage =
		mesh.lookupObject<AveragingMethod<scalar>>
		(
			this->owner().name() + ":massAverage"
			);

	// calculate time scales and pdf exponent
	autoPtr<AveragingMethod<scalar>> exponentAveragePtr
	(
		AveragingMethod<scalar>::New
		(
			IOobject
			(
				this->owner().name() + ":exponentAverage",
				this->owner().db().time().timeName(),
				mesh
			),
			this->owner().solution().dict(),
			mesh
		)
	);
	AveragingMethod<scalar>& exponentAverage = exponentAveragePtr();
	exponentAverage =
		exp
		(
			-deltaT
			* this->timeScaleModel_->oneByTau
			(
				volumeAverage,
				radiusAverage,
				uSqrAverage,
				frequencyAverage
			)
		)();

	// random sampling
	forAllIter(typename CloudType, this->owner(), iter)
	{
		typename CloudType::parcelType& p = iter();
		const tetIndices tetIs(p.currentTetIndices());

		const scalar x = exponentAverage.interpolate(p.coordinates(), tetIs);

		if (x < rndGen.sample01<scalar>())
		{
			const vector r(sampleGauss(), sampleGauss(), sampleGauss());

			const vector u = uAverage.interpolate(p.coordinates(), tetIs);
			const scalar uRms =
				sqrt(max(uSqrAverage.interpolate(p.coordinates(), tetIs), 0.0));

			p.U() = u + r * uRms*oneBySqrtThree;
		}
	}

	// correction velocity averages
	autoPtr<AveragingMethod<vector>> uTildeAveragePtr
	(
		AveragingMethod<vector>::New
		(
			IOobject
			(
				this->owner().name() + ":uTildeAverage",
				this->owner().db().time().timeName(),
				mesh
			),
			this->owner().solution().dict(),
			mesh
		)
	);
	AveragingMethod<vector>& uTildeAverage = uTildeAveragePtr();
	forAllIter(typename CloudType, this->owner(), iter)
	{
		typename CloudType::parcelType& p = iter();
		const tetIndices tetIs(p.currentTetIndices());
		uTildeAverage.add(p.coordinates(), tetIs, p.nParticle()*p.mass()*p.U());
	}
	uTildeAverage.average(massAverage);

	autoPtr<AveragingMethod<scalar>> uTildeSqrAveragePtr
	(
		AveragingMethod<scalar>::New
		(
			IOobject
			(
				this->owner().name() + ":uTildeSqrAverage",
				this->owner().db().time().timeName(),
				mesh
			),
			this->owner().solution().dict(),
			mesh
		)
	);
	AveragingMethod<scalar>& uTildeSqrAverage = uTildeSqrAveragePtr();
	forAllIter(typename CloudType, this->owner(), iter)
	{
		typename CloudType::parcelType& p = iter();
		const tetIndices tetIs(p.currentTetIndices());
		const vector uTilde = uTildeAverage.interpolate(p.coordinates(), tetIs);
		uTildeSqrAverage.add
		(
			p.coordinates(),
			tetIs,
			p.nParticle()*p.mass()*magSqr(p.U() - uTilde)
		);
	}
	uTildeSqrAverage.average(massAverage);

	// conservation correction
	forAllIter(typename CloudType, this->owner(), iter)
	{
		typename CloudType::parcelType& p = iter();
		const tetIndices tetIs(p.currentTetIndices());

		const vector u = uAverage.interpolate(p.coordinates(), tetIs);
		const scalar uRms =
			sqrt(max(uSqrAverage.interpolate(p.coordinates(), tetIs), 0.0));

		const vector uTilde = uTildeAverage.interpolate(p.coordinates(), tetIs);
		const scalar uTildeRms =
			sqrt
			(
				max(uTildeSqrAverage.interpolate(p.coordinates(), tetIs), 0.0)
			);

		p.U() = u + (p.U() - uTilde)*uRms / max(uTildeRms, small);
	}
}


// ************************************************************************* //