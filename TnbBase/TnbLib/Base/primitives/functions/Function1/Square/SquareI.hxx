#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::Square<Type>::value(const scalar t) const
{
	// Number of waves including fractions
	scalar waves = frequency_->value(t)*(t - t0_);

	// Number of complete waves
	scalar nWaves;

	// Fraction of last incomplete wave
	scalar waveFrac = std::modf(waves, &nWaves);

	// Mark fraction of a wave
	scalar markFrac = markSpace_ / (1.0 + markSpace_);

	return
		amplitude_->value(t)
		*(waveFrac < markFrac ? 1 : -1)
		*scale_->value(t)
		+ level_->value(t);
}


// ************************************************************************* //