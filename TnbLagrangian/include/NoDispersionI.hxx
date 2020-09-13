#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoDispersion<CloudType>::NoDispersion(const dictionary&, CloudType& owner)
	:
	DispersionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoDispersion<CloudType>::NoDispersion(const NoDispersion<CloudType>& dm)
	:
	DispersionModel<CloudType>(dm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoDispersion<CloudType>::~NoDispersion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoDispersion<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::vector tnbLib::NoDispersion<CloudType>::update
(
	const scalar,
	const label,
	const vector&,
	const vector& Uc,
	vector&,
	scalar&
)
{
	return Uc;
}


// ************************************************************************* //