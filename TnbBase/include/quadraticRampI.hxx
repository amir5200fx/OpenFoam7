#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Function1Types::quadraticRamp::value
(
	const scalar t
) const
{
	return sqr(linearRamp(t));
}


// ************************************************************************* //