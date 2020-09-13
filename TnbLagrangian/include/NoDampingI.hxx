#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DampingModels::NoDamping<CloudType>::NoDamping
(
	const dictionary& dict,
	CloudType& owner
)
	:
	DampingModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::DampingModels::NoDamping<CloudType>::NoDamping
(
	const NoDamping<CloudType>& cm
)
	:
	DampingModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DampingModels::NoDamping<CloudType>::~NoDamping()
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::vector tnbLib::DampingModels::NoDamping<CloudType>::velocityCorrection
(
	typename CloudType::parcelType& p,
	const scalar deltaT
) const
{
	return Zero;
}


template<class CloudType>
bool tnbLib::DampingModels::NoDamping<CloudType>::active() const
{
	return false;
}


// ************************************************************************* //