#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoBreakup<CloudType>::NoBreakup
(
	const dictionary&,
	CloudType& owner
)
	:
	BreakupModel<CloudType>(owner)
{}



template<class CloudType>
tnbLib::NoBreakup<CloudType>::NoBreakup(const NoBreakup<CloudType>& bum)
	:
	BreakupModel<CloudType>(bum)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoBreakup<CloudType>::~NoBreakup()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoBreakup<CloudType>::active() const
{
	return false;
}


template<class CloudType>
bool tnbLib::NoBreakup<CloudType>::update
(
	const scalar dt,
	const vector& g,
	scalar& d,
	scalar& tc,
	scalar& ms,
	scalar& nParticle,
	scalar& KHindex,
	scalar& y,
	scalar& yDot,
	const scalar d0,
	const scalar rho,
	const scalar mu,
	const scalar sigma,
	const vector& U,
	const scalar rhoc,
	const scalar muc,
	const vector& Urel,
	const scalar Urmag,
	const scalar tMom,
	scalar& dChild,
	scalar& massChild
)
{
	return false;
}


// ************************************************************************* //