#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::solidReactionThermo& tnbLib::basicSolidChemistryModel::solidThermo()
{
	return solidThermo_;
}


inline const tnbLib::solidReactionThermo&
tnbLib::basicSolidChemistryModel::solidThermo() const
{
	return solidThermo_;
}


// ************************************************************************* //