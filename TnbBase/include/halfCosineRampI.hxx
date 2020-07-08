#pragma once
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Function1Types::halfCosineRamp::value
(
	const scalar t
) const
{
	return 0.5*(1 - cos(constant::mathematical::pi*linearRamp(t)));
}


// ************************************************************************* //
