#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoSurfaceReaction<CloudType>::NoSurfaceReaction
(
	const dictionary&,
	CloudType& owner
)
	:
	SurfaceReactionModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoSurfaceReaction<CloudType>::NoSurfaceReaction
(
	const NoSurfaceReaction<CloudType>& srm
)
	:
	SurfaceReactionModel<CloudType>(srm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoSurfaceReaction<CloudType>::~NoSurfaceReaction()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoSurfaceReaction<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoSurfaceReaction<CloudType>::calculate
(
	const scalar,
	const label,
	const scalar,
	const scalar,
	const scalar,
	const scalar,
	const scalar,
	const scalar,
	const scalarField&,
	const scalarField&,
	const scalarField&,
	const scalarField&,
	const scalar,
	scalarField&,
	scalarField&,
	scalarField&,
	scalarField&
) const
{
	return 0;
}


// ************************************************************************* //