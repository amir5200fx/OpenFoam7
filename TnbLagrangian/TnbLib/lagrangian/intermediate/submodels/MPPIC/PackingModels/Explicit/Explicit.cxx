#include <Explicit.hxx>

#include <fvMesh.hxx>  // added by amir
#include <tetIndices.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModels::Explicit<CloudType>::Explicit
(
	const dictionary& dict,
	CloudType& owner
)
	:
	PackingModel<CloudType>(dict, owner, typeName),
	stressAverage_(nullptr),
	correctionLimiting_
	(
		CorrectionLimitingMethod::New
		(
			this->coeffDict().subDict(CorrectionLimitingMethod::typeName)
		)
	)
{}


template<class CloudType>
tnbLib::PackingModels::Explicit<CloudType>::Explicit
(
	const Explicit<CloudType>& cm
)
	:
	PackingModel<CloudType>(cm),
	stressAverage_(cm.stressAverage_->clone()),
	correctionLimiting_
	(
		cm.correctionLimiting_->clone()
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModels::Explicit<CloudType>::~Explicit()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PackingModels::Explicit<CloudType>::cacheFields(const bool store)
{
	PackingModel<CloudType>::cacheFields(store);

	if (store)
	{
		const fvMesh& mesh = this->owner().mesh();
		const word& cloudName = this->owner().name();

		const AveragingMethod<scalar>& volumeAverage =
			mesh.lookupObject<AveragingMethod<scalar>>
			(
				cloudName + ":volumeAverage"
				);
		const AveragingMethod<scalar>& rhoAverage =
			mesh.lookupObject<AveragingMethod<scalar>>
			(
				cloudName + ":rhoAverage"
				);
		const AveragingMethod<vector>& uAverage =
			mesh.lookupObject<AveragingMethod<vector>>
			(
				cloudName + ":uAverage"
				);
		const AveragingMethod<scalar>& uSqrAverage =
			mesh.lookupObject<AveragingMethod<scalar>>
			(
				cloudName + ":uSqrAverage"
				);

		volumeAverage_ = &volumeAverage;
		uAverage_ = &uAverage;

		stressAverage_.reset
		(
			AveragingMethod<scalar>::New
			(
				IOobject
				(
					cloudName + ":stressAverage",
					this->owner().db().time().timeName(),
					mesh
				),
				this->owner().solution().dict(),
				mesh
			).ptr()
		);

		stressAverage_() =
			this->particleStressModel_->tau
			(
				*volumeAverage_,
				rhoAverage,
				uSqrAverage
			)();
	}
	else
	{
		volumeAverage_ = nullptr;
		uAverage_ = nullptr;
		stressAverage_.clear();
	}
}


template<class CloudType>
tnbLib::vector tnbLib::PackingModels::Explicit<CloudType>::velocityCorrection
(
	typename CloudType::parcelType& p,
	const scalar deltaT
) const
{
	const tetIndices tetIs(p.currentTetIndices());

	// interpolated quantities
	const scalar alpha =
		this->volumeAverage_->interpolate(p.coordinates(), tetIs);
	const vector alphaGrad =
		this->volumeAverage_->interpolateGrad(p.coordinates(), tetIs);
	const vector uMean =
		this->uAverage_->interpolate(p.coordinates(), tetIs);

	// stress gradient
	const vector tauGrad =
		stressAverage_->interpolateGrad(p.coordinates(), tetIs);

	// parcel relative velocity
	const vector uRelative = p.U() - uMean;

	// correction velocity
	vector dU = Zero;

	//// existing forces
	// const scalar Re = p.Re(td);
	// const typename CloudType::forceType& forces = this->owner().forces();
	// const forceSuSp F =
	//    forces.calcCoupled(p, td, deltaT, p.mass(), Re, td.muc())
	//  + forces.calcNonCoupled(p, td, deltaT, p.mass(), Re, td.muc());

	// correction velocity
	if ((uRelative & alphaGrad) > 0)
	{
		dU = -deltaT * tauGrad / (p.rho()*alpha/* + deltaT*F.Sp()*/);
	}

	// apply the velocity limiters
	return
		correctionLimiting_->limitedVelocity
		(
			p.U(),
			dU,
			uMean
		);
}


// ************************************************************************* //