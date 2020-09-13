#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoPhaseChange<CloudType>::NoPhaseChange
(
	const dictionary&,
	CloudType& owner
)
	:
	PhaseChangeModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoPhaseChange<CloudType>::NoPhaseChange
(
	const NoPhaseChange<CloudType>& pcm
)
	:
	PhaseChangeModel<CloudType>(pcm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoPhaseChange<CloudType>::~NoPhaseChange()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoPhaseChange<CloudType>::active() const
{
	return false;
}


template<class CloudType>
void tnbLib::NoPhaseChange<CloudType>::calculate
(
	const scalar dt,
	const label celli,
	const scalar Re,
	const scalar Pr,
	const scalar d,
	const scalar nu,
	const scalar T,
	const scalar Ts,
	const scalar pc,
	const scalar Tc,
	const scalarField& X,
	scalarField& dMassPC
) const
{
	// Nothing to do...
}


// ************************************************************************* //