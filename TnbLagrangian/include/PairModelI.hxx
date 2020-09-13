#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PairModel<CloudType>::PairModel
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
tnbLib::PairModel<CloudType>::~PairModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType&
tnbLib::PairModel<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
const tnbLib::dictionary& tnbLib::PairModel<CloudType>::dict() const
{
	return dict_;
}


template<class CloudType>
const tnbLib::dictionary&
tnbLib::PairModel<CloudType>::coeffDict() const
{
	return coeffDict_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //