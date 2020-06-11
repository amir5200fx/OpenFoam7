#pragma once
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Function1Types::quarterCosineRamp::value
(
	const scalar t
) const
{
	return 1 - cos(0.5*constant::mathematical::pi*linearRamp(t));
}


// ************************************************************************* //