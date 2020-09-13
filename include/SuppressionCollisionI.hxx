#pragma once
#include <KinematicCloudTemplate.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::SuppressionCollision<CloudType>::collide
(
	typename CloudType::parcelType::trackingData& td,
	const scalar dt
)
{
	const kinematicCloud& sc =
		this->owner().mesh().template
		lookupObject<kinematicCloud>(suppressionCloud_);

	volScalarField vDotSweep(sc.vDotSweep());

	dimensionedScalar Dt("dt", dimTime, dt);
	volScalarField P(type() + ":p", 1.0 - exp(-vDotSweep * Dt));

	forAllIter(typename CloudType, this->owner(), iter)
	{
		typename CloudType::parcelType& p = iter();
		label celli = p.cell();

		scalar xx = this->owner().rndGen().template sample01<scalar>();

		if (xx < P[celli])
		{
			p.canCombust() = -1;
			p.typeId() = max(p.typeId(), suppressedParcelType_);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SuppressionCollision<CloudType>::SuppressionCollision
(
	const dictionary& dict,
	CloudType& owner
)
	:
	StochasticCollisionModel<CloudType>(dict, owner, typeName),
	suppressionCloud_(this->coeffDict().lookup("suppressionCloud")),
	suppressedParcelType_
	(
		this->coeffDict().lookupOrDefault("suppressedParcelType", -1)
	)
{}


template<class CloudType>
tnbLib::SuppressionCollision<CloudType>::SuppressionCollision
(
	const SuppressionCollision<CloudType>& cm
)
	:
	StochasticCollisionModel<CloudType>(cm),
	suppressionCloud_(cm.suppressionCloud_),
	suppressedParcelType_(cm.suppressedParcelType_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SuppressionCollision<CloudType>::~SuppressionCollision()
{}


// ************************************************************************* //