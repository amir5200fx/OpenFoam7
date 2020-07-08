#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline tnbLib::zeroField tnbLib::zeroFieldField::operator[](const label) const
{
	return zeroField();
}


// ************************************************************************* //