#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::InflowBoundaryModel<CloudType>::InflowBoundaryModel(CloudType& owner)
	:
	dict_(dictionary::null),
	owner_(owner),
	coeffDict_(dictionary::null)
{}


template<class CloudType>
tnbLib::InflowBoundaryModel<CloudType>::InflowBoundaryModel
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
tnbLib::InflowBoundaryModel<CloudType>::~InflowBoundaryModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType& tnbLib::InflowBoundaryModel<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
CloudType& tnbLib::InflowBoundaryModel<CloudType>::owner()
{
	return owner_;
}


template<class CloudType>
const tnbLib::dictionary& tnbLib::InflowBoundaryModel<CloudType>::dict() const
{
	return dict_;
}


template<class CloudType>
const tnbLib::dictionary& tnbLib::InflowBoundaryModel<CloudType>::coeffDict() const
{
	return coeffDict_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //