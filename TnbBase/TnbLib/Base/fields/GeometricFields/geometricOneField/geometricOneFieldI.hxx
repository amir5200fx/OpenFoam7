#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::dimensionSet& tnbLib::geometricOneField::dimensions() const
{
	return dimless;
}


inline tnbLib::one tnbLib::geometricOneField::operator[](const label) const
{
	return one();
}


inline tnbLib::oneField tnbLib::geometricOneField::field() const
{
	return oneField();
}


inline tnbLib::oneField tnbLib::geometricOneField::oldTime() const
{
	return oneField();
}


inline tnbLib::geometricOneField::Internal
tnbLib::geometricOneField::operator()() const
{
	return Internal();
}


inline tnbLib::geometricOneField::Internal
tnbLib::geometricOneField::v() const
{
	return Internal();
}


inline typename tnbLib::geometricOneField::Internal::FieldType
tnbLib::geometricOneField::primitiveField() const
{
	return typename Internal::FieldType();
}


inline tnbLib::geometricOneField::Boundary
tnbLib::geometricOneField::boundaryField() const
{
	return Boundary();
}


inline const tnbLib::geometricOneField& tnbLib::operator*
(
	const geometricOneField& gof,
	const geometricOneField&
	)
{
	return gof;
}


inline const tnbLib::geometricOneField::Internal& tnbLib::operator*
(
	const geometricOneField::Internal& of,
	const geometricOneField&
	)
{
	return of;
}


inline const tnbLib::geometricOneField::Internal& tnbLib::operator*
(
	const geometricOneField&,
	const geometricOneField::Internal& of
	)
{
	return of;
}


inline const tnbLib::geometricOneField& tnbLib::operator/
(
	const geometricOneField& gof,
	const geometricOneField&
	)
{
	return gof;
}


inline const tnbLib::geometricOneField::Internal& tnbLib::operator/
(
	const geometricOneField::Internal& of,
	const geometricOneField&
	)
{
	return of;
}


inline const tnbLib::geometricOneField::Internal& tnbLib::operator/
(
	const geometricOneField&,
	const geometricOneField::Internal& of
	)
{
	return of;
}


// ************************************************************************* //