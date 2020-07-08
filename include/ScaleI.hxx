#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::Scale<Type>::value(const scalar t) const
{
	const scalar st = xScale_->value(t)*t;
	return scale_->value(st)*value_->value(st);
}


// ************************************************************************* //