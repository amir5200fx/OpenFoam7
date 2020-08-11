#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::LindemannFallOffFunction::LindemannFallOffFunction()
{}


inline tnbLib::LindemannFallOffFunction::LindemannFallOffFunction
(
	const dictionary& dict
)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::LindemannFallOffFunction::operator()
(
	const scalar,
	const scalar
	) const
{
	return 1.0;
}


inline tnbLib::scalar tnbLib::LindemannFallOffFunction::ddT
(
	const scalar,
	const scalar,
	const scalar,
	const scalar
) const
{
	return 0;
}


inline tnbLib::scalar tnbLib::LindemannFallOffFunction::ddc
(
	const scalar,
	const scalar,
	const scalar,
	const scalar
) const
{
	return 0;
}


inline void tnbLib::LindemannFallOffFunction::write(Ostream& os) const
{}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::LindemannFallOffFunction&
	)
{
	return os;
}


// ************************************************************************* //