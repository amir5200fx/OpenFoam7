#pragma once
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class arg2>
	class innerProduct<one, arg2>
	{
	public:

		typedef arg2 type;
	};

	inline scalar operator+(const scalar& t, const one&)
	{
		return t + 1;
	}

	inline scalar operator+(const one&, const scalar& t)
	{
		return 1 + t;
	}

	inline scalar operator-(const scalar& t, const one&)
	{
		return t - 1;
	}

	inline scalar operator-(const one&, const scalar& t)
	{
		return 1 - t;
	}

	inline const one& operator*(const one& o, const one&)
	{
		return o;
	}

	template<class Type>
	inline const Type& operator*(const Type& t, const one&)
	{
		return t;
	}

	template<class Type>
	inline const Type& operator*(const one&, const Type& t)
	{
		return t;
	}

	template<class Type>
	inline const Type& operator&(const one&, const Type& t)
	{
		return t;
	}

	inline const one& operator/(const one& o, const one&)
	{
		return o;
	}

	template<class Type>
	inline Type operator/(const one&, const Type& t)
	{
		return scalar(1) / t;
	}

	template<class Type>
	inline const Type& operator/(const Type& t, const one&)
	{
		return t;
	}

	inline const one& min(const one& o, const one&)
	{
		return o;
	}

	template<class Type>
	inline Type min(const one&, const Type& t)
	{
		return min(scalar(1), t);
	}

	template<class Type>
	inline Type min(const Type& t, const one&)
	{
		return min(t, scalar(1));
	}

	inline const one& max(const one& o, const one&)
	{
		return o;
	}

	template<class Type>
	inline Type max(const one&, const Type& t)
	{
		return max(scalar(1), t);
	}

	template<class Type>
	inline Type max(const Type& t, const one&)
	{
		return max(t, scalar(1));
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //