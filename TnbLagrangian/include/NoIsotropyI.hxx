#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModels::NoIsotropy<CloudType>::NoIsotropy
(
	const dictionary& dict,
	CloudType& owner
)
	:
	IsotropyModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::IsotropyModels::NoIsotropy<CloudType>::NoIsotropy
(
	const NoIsotropy<CloudType>& cm
)
	:
	IsotropyModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModels::NoIsotropy<CloudType>::~NoIsotropy()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::IsotropyModels::NoIsotropy<CloudType>::calculate()
{}


template<class CloudType>
bool tnbLib::IsotropyModels::NoIsotropy<CloudType>::active() const
{
	return false;
}


// ************************************************************************* //