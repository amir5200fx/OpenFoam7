#pragma once
#include <constants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoBinaryCollision<CloudType>::NoBinaryCollision
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	BinaryCollisionModel<CloudType>(cloud)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoBinaryCollision<CloudType>::~NoBinaryCollision()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoBinaryCollision<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoBinaryCollision<CloudType>::sigmaTcR
(
	const typename CloudType::parcelType& pP,
	const typename CloudType::parcelType& pQ
) const
{
	FatalErrorInFunction
		<< "sigmaTcR called on NoBinaryCollision model, this should "
		<< "not happen, this is not an actual model." << nl
		<< "Enclose calls to sigmaTcR within a if (binaryCollision().active()) "
		<< " check."
		<< abort(FatalError);

	return 0.0;
}


template<class CloudType>
void tnbLib::NoBinaryCollision<CloudType>::collide
(
	typename CloudType::parcelType& pP,
	typename CloudType::parcelType& pQ
)
{}


// ************************************************************************* //