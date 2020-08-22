#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::potential::nIds() const
{
	return idList_.size();
}


inline const tnbLib::List<tnbLib::word>& tnbLib::potential::idList() const
{
	return idList_;
}


inline const tnbLib::List<tnbLib::word>& tnbLib::potential::siteIdList() const
{
	return siteIdList_;
}


inline tnbLib::scalar tnbLib::potential::potentialEnergyLimit() const
{
	return potentialEnergyLimit_;
}


inline tnbLib::label tnbLib::potential::nPairPotentials() const
{
	return pairPotentials_.size();
}


inline const tnbLib::labelList& tnbLib::potential::removalOrder() const
{
	return removalOrder_;
}


inline const tnbLib::pairPotentialList& tnbLib::potential::pairPotentials() const
{
	return pairPotentials_;
}


inline const tnbLib::tetherPotentialList&
tnbLib::potential::tetherPotentials() const
{
	return tetherPotentials_;
}


inline const tnbLib::vector& tnbLib::potential::gravity() const
{
	return gravity_;
}


// ************************************************************************* //