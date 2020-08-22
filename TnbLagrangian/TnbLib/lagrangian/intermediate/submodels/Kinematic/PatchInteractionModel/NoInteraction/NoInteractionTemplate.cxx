#include <NoInteractionTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoInteraction<CloudType>::NoInteraction
(
	const dictionary&,
	CloudType& owner
)
	:
	PatchInteractionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoInteraction<CloudType>::NoInteraction
(
	const NoInteraction<CloudType>& pim
)
	:
	PatchInteractionModel<CloudType>(pim)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoInteraction<CloudType>::~NoInteraction()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoInteraction<CloudType>::active() const
{
	return false;
}


template<class CloudType>
bool tnbLib::NoInteraction<CloudType>::correct
(
	typename CloudType::parcelType& p,
	const polyPatch&,
	bool&
)
{
	return false;
}


// ************************************************************************* //