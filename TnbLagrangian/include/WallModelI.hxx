#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::WallModel<CloudType>::WallModel
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
tnbLib::WallModel<CloudType>::~WallModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType&
tnbLib::WallModel<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
CloudType&
tnbLib::WallModel<CloudType>::owner()
{
	return owner_;
}


template<class CloudType>
const tnbLib::dictionary& tnbLib::WallModel<CloudType>::dict() const
{
	return dict_;
}


template<class CloudType>
const tnbLib::dictionary&
tnbLib::WallModel<CloudType>::coeffDict() const
{
	return coeffDict_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //