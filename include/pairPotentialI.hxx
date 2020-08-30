#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::pairPotential::rMin() const
{
	return rMin_;
}


inline tnbLib::scalar tnbLib::pairPotential::dr() const
{
	return dr_;
}


inline tnbLib::scalar tnbLib::pairPotential::rCut() const
{
	return rCut_;
}


inline tnbLib::scalar tnbLib::pairPotential::rCutSqr() const
{
	return rCutSqr_;
}


inline bool tnbLib::pairPotential::writeTables() const
{
	return writeTables_;
}

// ************************************************************************* //