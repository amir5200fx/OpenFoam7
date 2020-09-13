#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModels::NoPacking<CloudType>::NoPacking
(
	const dictionary& dict,
	CloudType& owner
)
	:
	PackingModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::PackingModels::NoPacking<CloudType>::NoPacking
(
	const NoPacking<CloudType>& cm
)
	:
	PackingModel<CloudType>(cm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModels::NoPacking<CloudType>::~NoPacking()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::vector tnbLib::PackingModels::NoPacking<CloudType>::velocityCorrection
(
	typename CloudType::parcelType& p,
	const scalar deltaT
) const
{
	return Zero;
}


template<class CloudType>
bool tnbLib::PackingModels::NoPacking<CloudType>::active() const
{
	return false;
}


// ************************************************************************* //