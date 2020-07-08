#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::zeroField::operator[](const label) const
{
	return scalar(0);
}


inline tnbLib::zeroField tnbLib::zeroField::field() const
{
	return zeroField();
}


inline tnbLib::zeroField tnbLib::zeroField::operator()() const
{
	return zeroField();
}


inline tnbLib::zeroField tnbLib::zeroField::operator-() const
{
	return zeroField();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const zeroField operator+(const zeroField&, const zeroField&)
	{
		return zeroField();
	}

	template<class Type>
	inline const Type& operator+(const Type& t, const zeroField&)
	{
		return t;
	}

	template<class Type>
	inline const Type& operator+(const zeroField&, const Type& t)
	{
		return t;
	}

	inline const zeroField operator-(const zeroField&, const zeroField&)
	{
		return zeroField();
	}

	template<class Type>
	inline const Type& operator-(const Type& t, const zeroField&)
	{
		return t;
	}

	template<class Type>
	inline Type operator-(const zeroField&, const Type& t)
	{
		return -t;
	}

	template<class Type>
	inline zeroField operator*(const Type& t, const zeroField&)
	{
		return zeroField();
	}

	template<class Type>
	inline zeroField operator*(const zeroField&, const Type& t)
	{
		return zeroField();
	}

	template<class Type>
	inline zeroField operator/(const zeroField&, const Type& t)
	{
		return zeroField();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //