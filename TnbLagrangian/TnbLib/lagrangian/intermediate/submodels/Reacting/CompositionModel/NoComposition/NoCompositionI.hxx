#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoComposition<CloudType>::NoComposition
(
	const dictionary&,
	CloudType& owner
)
	:
	CompositionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoComposition<CloudType>::NoComposition
(
	const NoComposition<CloudType>& cm
)
	:
	CompositionModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoComposition<CloudType>::~NoComposition()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::scalarField& tnbLib::NoComposition<CloudType>::YMixture0() const
{
	return scalarField::null();
}


template<class CloudType>
tnbLib::label tnbLib::NoComposition<CloudType>::idGas() const
{
	return -1;
}


template<class CloudType>
tnbLib::label tnbLib::NoComposition<CloudType>::idLiquid() const
{
	return -1;
}


template<class CloudType>
tnbLib::label tnbLib::NoComposition<CloudType>::idSolid() const
{
	return -1;
}


// ************************************************************************* //