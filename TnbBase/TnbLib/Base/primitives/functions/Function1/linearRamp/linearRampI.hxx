#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Function1Types::linearRamp::value
(
	const scalar t
) const
{
	return ramp::linearRamp(t);
}


// ************************************************************************* //