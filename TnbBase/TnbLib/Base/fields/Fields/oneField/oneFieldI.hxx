#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline tnbLib::one tnbLib::oneField::operator[](const label) const
{
	return one();
}


inline tnbLib::oneField tnbLib::oneField::field() const
{
	return oneField();
}


inline const tnbLib::oneField& tnbLib::operator*
(
	const oneField& of,
	const oneField&
	)
{
	return of;
}


inline const tnbLib::oneField& tnbLib::operator/
(
	const oneField& of,
	const oneField&
	)
{
	return of;
}


// ************************************************************************* //