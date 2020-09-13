#pragma once
// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::NoStochasticCollision<CloudType>::collide
(
	typename CloudType::parcelType::trackingData&,
	const scalar
)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoStochasticCollision<CloudType>::NoStochasticCollision
(
	const dictionary& dict,
	CloudType& owner
)
	:
	StochasticCollisionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoStochasticCollision<CloudType>::NoStochasticCollision
(
	const NoStochasticCollision<CloudType>& cm
)
	:
	StochasticCollisionModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoStochasticCollision<CloudType>::~NoStochasticCollision()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoStochasticCollision<CloudType>::active() const
{
	return false;
}


// ************************************************************************* //