#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::dimensionSet& tnbLib::geometricZeroField::dimensions() const
{
	return dimless;
}

inline tnbLib::scalar tnbLib::geometricZeroField::operator[](const label) const
{
	return scalar(0);
}

inline tnbLib::zeroField tnbLib::geometricZeroField::field() const
{
	return zeroField();
}

inline tnbLib::zeroField tnbLib::geometricZeroField::operator()() const
{
	return zeroField();
}

inline tnbLib::zeroField tnbLib::geometricZeroField::oldTime() const
{
	return zeroField();
}

inline tnbLib::zeroFieldField tnbLib::geometricZeroField::boundaryField() const
{
	return zeroFieldField();
}


// ************************************************************************* //