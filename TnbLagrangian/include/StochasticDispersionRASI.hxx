#pragma once
#include <constants.hxx>

#include <Random.hxx>  // added by amir

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::StochasticDispersionRAS<CloudType>::StochasticDispersionRAS
(
	const dictionary& dict,
	CloudType& owner
)
	:
	DispersionRASModel<CloudType>(dict, owner)
{}


template<class CloudType>
tnbLib::StochasticDispersionRAS<CloudType>::StochasticDispersionRAS
(
	const StochasticDispersionRAS<CloudType>& dm
)
	:
	DispersionRASModel<CloudType>(dm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::StochasticDispersionRAS<CloudType>::~StochasticDispersionRAS()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::vector tnbLib::StochasticDispersionRAS<CloudType>::update
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

	const scalar UrelMag = mag(U - Uc - UTurb);

	const scalar tTurbLoc =
		min(k / epsilon, cps*pow(k, 1.5) / epsilon / (UrelMag + small));


	// Parcel is perturbed by the turbulence
	if (dt < tTurbLoc)
	{
		tTurb += dt;

		if (tTurb > tTurbLoc)
		{
			tTurb = 0;

			const scalar sigma = sqrt(2 * k / 3.0);

			// Calculate a random direction dir distributed uniformly
			// in spherical coordinates

			const scalar theta = rnd.scalar01()*twoPi;
			const scalar u = 2 * rnd.scalar01() - 1;

			const scalar a = sqrt(1 - sqr(u));
			const vector dir(a*cos(theta), a*sin(theta), u);

			UTurb = sigma * mag(rnd.scalarNormal())*dir;
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