#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BinaryCollisionModel<CloudType>::BinaryCollisionModel(CloudType& owner)
	:
	dict_(dictionary::null),
	owner_(owner),
	coeffDict_(dictionary::null)
{}


template<class CloudType>
tnbLib::BinaryCollisionModel<CloudType>::BinaryCollisionModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	dict_(dict),
	owner_(owner),
	coeffDict_(dict.subDict(type + "Coeffs"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::BinaryCollisionModel<CloudType>::~BinaryCollisionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType&
tnbLib::BinaryCollisionModel<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
CloudType&
tnbLib::BinaryCollisionModel<CloudType>::owner()
{
	return owner_;
}


template<class CloudType>
const tnbLib::dictionary&
tnbLib::BinaryCollisionModel<CloudType>::dict() const
{
	return dict_;
}


template<class CloudType>
const tnbLib::dictionary&
tnbLib::BinaryCollisionModel<CloudType>::coeffDict() const
{
	return coeffDict_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //