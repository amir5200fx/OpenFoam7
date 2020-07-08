#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::UniformField<Type>::UniformField(const Type& value)
	:
	value_(value)
{}


template<class Type>
inline tnbLib::UniformField<Type>::operator Type() const
{
	return value_;
}


template<class Type>
inline Type tnbLib::UniformField<Type>::operator[](const label) const
{
	return value_;
}


template<class Type>
inline tnbLib::UniformField<Type> tnbLib::UniformField<Type>::field() const
{
	return UniformField(value_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type>
	inline UniformField<Type> min
	(
		const UniformField<Type>& u1,
		const UniformField<Type>& u2
	)
	{
		return UniformField<Type>(min(u1.operator Type(), u2.operator Type()));
	}


	template<class Type, class OtherType>
	inline OtherType min(const UniformField<Type>& u, const OtherType& o)
	{
		return min(u.operator Type(), o);
	}


	template<class Type, class OtherType>
	inline OtherType min(const OtherType& o, const UniformField<Type>& u)
	{
		return min(o, u.operator Type());
	}


	template<class Type>
	inline UniformField<Type> max
	(
		const UniformField<Type>& u1,
		const UniformField<Type>& u2
	)
	{
		return UniformField<Type>(max(u1.operator Type(), u2.operator Type()));
	}


	template<class Type, class OtherType>
	inline OtherType max(const UniformField<Type>& u, const OtherType& o)
	{
		return max(u.operator Type(), o);
	}


	template<class Type, class OtherType>
	inline OtherType max(const OtherType& o, const UniformField<Type>& u)
	{
		return max(o, u.operator Type());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //