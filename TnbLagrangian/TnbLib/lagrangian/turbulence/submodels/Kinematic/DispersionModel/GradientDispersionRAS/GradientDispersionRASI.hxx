#pragma once
#include <demandDrivenData.hxx>
#include <fvcGrad.hxx>

#include <Random.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::GradientDispersionRAS<CloudType>::GradientDispersionRAS
(
	const dictionary& dict,
	CloudType& owner
)
	:
	DispersionRASModel<CloudType>(dict, owner),
	gradkPtr_(nullptr),
	ownGradK_(false)
{}


template<class CloudType>
tnbLib::GradientDispersionRAS<CloudType>::GradientDispersionRAS
(
	const GradientDispersionRAS<CloudType>& dm
)
	:
	DispersionRASModel<CloudType>(dm),
	gradkPtr_(dm.gradkPtr_),
	ownGradK_(dm.ownGradK_)
{
	dm.ownGradK_ = false;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::GradientDispersionRAS<CloudType>::~GradientDispersionRAS()
{
	cacheFields(false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::GradientDispersionRAS<CloudType>::cacheFields(const bool store)
{
	DispersionRASModel<CloudType>::cacheFields(store);

	if (store)
	{
		gradkPtr_ = fvc::grad(*this->kPtr_).ptr();
		ownGradK_ = true;
	}
	else
	{
		if (ownGradK_)
		{
			deleteDemandDrivenData(gradkPtr_);
			gradkPtr_ = nullptr;
			ownGradK_ = false;
		}
	}
}


template<class CloudType>
tnbLib::vector tnbLib::GradientDispersionRAS<CloudType>::update
(
	const scalar dt,
	const label celli,
	const vector& U,
	const vector& Uc,
	vector& UTurb,
	scalar& tTurb
)
{
	Random& rnd = this->owner().rndGen();

	const scalar cps = 0.16432;

	const scalar k = this->kPtr_->primitiveField()[celli];
	const scalar epsilon =
		this->epsilonPtr_->primitiveField()[celli] + rootVSmall;
	const vector& gradk = this->gradkPtr_->primitiveField()[celli];

	const scalar UrelMag = mag(U - Uc - UTurb);

	const scalar tTurbLoc =
		min(k / epsilon, cps*pow(k, 1.5) / epsilon / (UrelMag + small));


	// Parcel is perturbed by the turbulence
	if (dt < tTurbLoc)
	{
		tTurb += dt;

		if (tTurb > tTurbLoc)
		{
			tTurb = 0.0;

			const scalar sigma = sqrt(2.0*k / 3.0);
			const vector dir = -gradk / (mag(gradk) + small);

			scalar fac = 0.0;

			// In 2D calculations the -grad(k) is always
			// away from the axis of symmetry
			// This creates a 'hole' in the spray and to
			// prevent this we let fac be both negative/positive
			if (this->owner().mesh().nSolutionD() == 2)
			{
				fac = rnd.scalarNormal();
			}
			else
			{
				fac = mag(rnd.scalarNormal());
			}

			UTurb = sigma * fac*dir;
		}
	}
	else
	{
		tTurb = great;
		UTurb = Zero;
	}

	return Uc + UTurb;
}


// ************************************************************************* //