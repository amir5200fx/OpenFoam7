#pragma once
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::Sine<Type>::value(const scalar t) const
{
	return
		amplitude_->value(t)
		*sin(constant::mathematical::twoPi*frequency_->value(t)*(t - t0_))
		*scale_->value(t)
		+ level_->value(t);
}


// ************************************************************************* //