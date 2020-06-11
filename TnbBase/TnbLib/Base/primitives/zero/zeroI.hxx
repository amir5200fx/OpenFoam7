#pragma once
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline zero operator+(const zero&, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline const Type& operator+(const Type& t, const zero&)
	{
		return t;
	}

	template<class Type>
	inline const Type& operator+(const zero&, const Type& t)
	{
		return t;
	}

	inline zero operator-(const zero&, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline const Type& operator-(const Type& t, const zero&)
	{
		return t;
	}

	template<class Type>
	inline Type operator-(const zero&, const Type& t)
	{
		return -t;
	}

	inline zero operator*(const zero&, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline zero operator*(const Type& t, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline zero operator*(const zero&, const Type& t)
	{
		return Zero;
	}

	template<class Type>
	inline zero operator/(const zero&, const Type& t)
	{
		return Zero;
	}

	inline zero min(const zero&, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline Type min(const zero&, const Type& t)
	{
		return min(scalar(0), t);
	}

	template<class Type>
	inline Type min(const Type& t, const zero&)
	{
		return min(t, scalar(0));
	}

	inline zero max(const zero&, const zero&)
	{
		return Zero;
	}

	template<class Type>
	inline Type max(const zero&, const Type& t)
	{
		return max(scalar(0), t);
	}

	template<class Type>
	inline Type max(const Type& t, const zero&)
	{
		return max(t, scalar(0));
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //