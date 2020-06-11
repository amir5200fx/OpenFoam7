#pragma once
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Function1Types::quarterSineRamp::value
(
	const scalar t
) const
{
	return sin(0.5*constant::mathematical::pi*linearRamp(t));
}


// ************************************************************************* //