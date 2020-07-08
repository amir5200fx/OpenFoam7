#pragma once
#ifndef _longDoubleScalar_Header
#define _longDoubleScalar_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Typedef
	tnbLib::longDoubleScalar

Description
	Lang double precision floating point scalar type.

SourceFiles
	longDoubleScalar.C

\*---------------------------------------------------------------------------*/

#include <doubleFloat.hxx>
#include <direction.hxx>
#include <word.hxx>

#include <limits>
using std::numeric_limits;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef long double longDoubleScalar;

	// Largest and smallest scalar values allowed in certain parts of the code.
	static const longDoubleScalar longDoubleScalarVGreat
		= numeric_limits<long double>::max() / 10;
	static const longDoubleScalar longDoubleScalarVSmall
		= numeric_limits<double>::min();

	static const longDoubleScalar longDoubleScalarSmall
		= 1e3*numeric_limits<long double>::epsilon();
	static const longDoubleScalar longDoubleScalarGreat
		= 1.0 / longDoubleScalarSmall;

	static const longDoubleScalar longDoubleScalarRootVGreat
		= ::sqrtl(longDoubleScalarVGreat);
	static const longDoubleScalar longDoubleScalarRootVSmall
		= ::sqrtl(longDoubleScalarVSmall);

	static const longDoubleScalar longDoubleScalarRootGreat
		= ::sqrtl(longDoubleScalarGreat);
	static const longDoubleScalar longDoubleScalarRootSmall
		= ::sqrtl(longDoubleScalarSmall);

	//- Read whole of buf as a scalar. Return true if successful.
	inline bool readScalar(const char* buf, longDoubleScalar& s)
	{
		char* endPtr;
		s = strtold(buf, &endPtr);

		return (*endPtr == '\0');
	}

#define ScalarVGreat longDoubleScalarVGreat
#define ScalarVSmall longDoubleScalarVSmall
#define ScalarRootVGreat longDoubleScalarRootVGreat
#define ScalarRootVSmall longDoubleScalarRootVSmall
#define readScalar readLongDoubleScalar

	inline longDoubleScalar mag(const longDoubleScalar s)
	{
		return ::fabsl(s);
	}

#define MAXMINPOW(retType, type1, type2)          \
                                                  \
MAXMIN(retType, type1, type2)                     \
                                                  \
inline double pow(const type1 s, const type2 e)   \
{                                                 \
    return ::powl(longDoubleScalar(s), longDoubleScalar(e));          \
}

	MAXMINPOW(longDoubleScalar, longDoubleScalar, longDoubleScalar)
		MAXMINPOW(longDoubleScalar, longDoubleScalar, int)
		MAXMINPOW(longDoubleScalar, int, longDoubleScalar)
		MAXMINPOW(longDoubleScalar, longDoubleScalar, long)
		MAXMINPOW(longDoubleScalar, long, longDoubleScalar)
		MAXMINPOW(longDoubleScalar, longDoubleScalar, float)
		MAXMINPOW(longDoubleScalar, float, longDoubleScalar)
		MAXMINPOW(longDoubleScalar, longDoubleScalar, double)
		MAXMINPOW(longDoubleScalar, double, longDoubleScalar)

#undef MAXMINPOW

#define transFunc(func)            \
inline longDoubleScalar func(const longDoubleScalar s) \
{                                  \
    return ::func(s);              \
}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// template specialisation for pTraits<longDoubleScalar>
	template<>
	class pTraits<longDoubleScalar>
	{
		longDoubleScalar p_;

	public:

		//- Component type
		typedef longDoubleScalar cmptType;

		//- Equivalent type of labels used for valid component indexing
		typedef label labelType;


		// Member constants

			//- Dimensionality of space
		static const direction dim = 3;

		//- Rank of longDoubleScalar is 0
		static const direction rank = 0;

		//- Number of components in longDoubleScalar is 1
		static const direction nComponents = 1;


		// Static Data Members

		static const char* const typeName;
		static const char* const componentNames[];
		static const longDoubleScalar zero;
		static const longDoubleScalar one;
		static const longDoubleScalar max;
		static const longDoubleScalar min;
		static const longDoubleScalar rootMax;
		static const longDoubleScalar rootMin;


		// Constructors

			//- Construct from primitive
		explicit pTraits(const longDoubleScalar&);

		//- Construct from Istream
		pTraits(Istream&);


		// Member Functions

			//- Access to the longDoubleScalar value
		operator longDoubleScalar() const
		{
			return p_;
		}

		//- Access to the longDoubleScalar value
		operator longDoubleScalar&()
		{
			return p_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Return a string representation of a longDoubleScalar
	word name(const longDoubleScalar);


	// Standard C++ transcendental functions
	transFunc(sqrt)

		transFunc(cbrt)
		transFunc(exp)
		transFunc(log)
		transFunc(log10)
		transFunc(sin)
		transFunc(cos)
		transFunc(tan)
		transFunc(asin)
		transFunc(acos)
		transFunc(atan)
		transFunc(sinh)
		transFunc(cosh)
		transFunc(tanh)
		transFunc(asinh)
		transFunc(acosh)
		transFunc(atanh)

		// Standard ANSI-C (but not in <cmath>) transcendental functions

		transFunc(erf)
		transFunc(erfc)
		transFunc(lgamma)
		transFunc(tgamma)

		transFunc(_j0)
		transFunc(_j1)

		transFunc(_y0)
		transFunc(_y1)


		inline longDoubleScalar& setComponent(longDoubleScalar& s, const direction)
	{
		return s;
	}


	inline longDoubleScalar component(const longDoubleScalar s, const direction)
	{
		return s;
	}


	//- Return 1 if s is positive or 0 otherwise -1
	inline int sign(const longDoubleScalar s)
	{
		return (s >= 0) ? 1 : -1;
	}


	//- Return 1 if s is positive but not 0
	inline int pos(const longDoubleScalar s)
	{
		return (s > 0) ? 1 : 0;
	}


	//- Return 1 if s is positive or 0
	inline int pos0(const longDoubleScalar s)
	{
		return (s >= 0) ? 1 : 0;
	}


	//- Return 1 if s is negative but not 0
	inline int neg(const longDoubleScalar s)
	{
		return (s < 0) ? 1 : 0;
	}


	//- Return 1 if s is negative or 0
	inline int neg0(const longDoubleScalar s)
	{
		return (s <= 0) ? 1 : 0;
	}


	//- Return the positive part of s
	inline longDoubleScalar posPart(const longDoubleScalar s)
	{
		return (s > 0) ? s : 0;
	}


	//- Return the negative part of s.
	//  Note: this function returns the actual negative part of s as a
	//  negative number and does not change the sign
	inline longDoubleScalar negPart(const longDoubleScalar s)
	{
		return (s < 0) ? s : 0;
	}


	inline bool equal(const longDoubleScalar& s1, const longDoubleScalar& s2)
	{
		return mag(s1 - s2) <= ScalarVSmall;
	}


	inline bool notEqual(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return mag(s1 - s2) > ScalarVSmall;
	}


	inline longDoubleScalar limit(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : 0.0;
	}


	inline longDoubleScalar minMod(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : s2;
	}


	inline longDoubleScalar magSqr(const longDoubleScalar s)
	{
		return s * s;
	}


	inline longDoubleScalar sqr(const longDoubleScalar s)
	{
		return s * s;
	}


	inline longDoubleScalar pow3(const longDoubleScalar s)
	{
		return s * sqr(s);
	}


	inline longDoubleScalar pow4(const longDoubleScalar s)
	{
		return sqr(sqr(s));
	}


	inline longDoubleScalar pow5(const longDoubleScalar s)
	{
		return s * pow4(s);
	}


	inline longDoubleScalar pow6(const longDoubleScalar s)
	{
		return pow3(sqr(s));
	}


	inline longDoubleScalar pow025(const longDoubleScalar s)
	{
		return sqrt(sqrt(s));
	}


	inline longDoubleScalar inv(const longDoubleScalar s)
	{
		return 1.0 / s;
	}


	inline longDoubleScalar dot(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return s1 * s2;
	}


	inline longDoubleScalar cmptMultiply(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return s1 * s2;
	}


	inline longDoubleScalar cmptPow(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return pow(s1, s2);
	}


	inline longDoubleScalar cmptDivide(const longDoubleScalar s1, const longDoubleScalar s2)
	{
		return s1 / s2;
	}


	inline longDoubleScalar cmptMax(const longDoubleScalar s)
	{
		return s;
	}


	inline longDoubleScalar cmptMin(const longDoubleScalar s)
	{
		return s;
	}


	inline longDoubleScalar cmptAv(const longDoubleScalar s)
	{
		return s;
	}


	inline longDoubleScalar cmptSqr(const longDoubleScalar s)
	{
		return sqr(s);
	}


	inline longDoubleScalar cmptMag(const longDoubleScalar s)
	{
		return mag(s);
	}


	inline longDoubleScalar sqrtSumSqr(const longDoubleScalar a, const longDoubleScalar b)
	{
		longDoubleScalar maga = mag(a);
		longDoubleScalar magb = mag(b);

		if (maga > magb)
		{
			return maga * sqrt(1 + sqr(magb / maga));
		}
		else
		{
			return magb < ScalarVSmall ? 0 : magb * sqrt(1 + sqr(maga / magb));
		}
	}


	//- Stabilisation around zero for division
	inline longDoubleScalar stabilise(const longDoubleScalar s, const longDoubleScalar small)
	{
		if (s >= 0)
		{
			return s + small;
		}
		else
		{
			return s - small;
		}
	}


	// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

	longDoubleScalar readScalar(Istream&);

	void writeEntry(Ostream& os, const longDoubleScalar value);


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	Istream& operator>>(Istream&, longDoubleScalar&);
	Ostream& operator<<(Ostream&, const longDoubleScalar);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline longDoubleScalar hypot(const longDoubleScalar x, const longDoubleScalar y)
	{
		return ::hypotl(x, y);
	}

	inline longDoubleScalar atan2(const longDoubleScalar y, const longDoubleScalar x)
	{
		return ::atan2l(y, x);
	}

	inline longDoubleScalar jn(const int n, const longDoubleScalar s)
	{
		//return ::_jnl(n, s);
		return ::_jn(n, s);
	}

	inline longDoubleScalar yn(const int n, const longDoubleScalar s)
	{
		//return ::_ynl(n, s);
		return ::_yn(n, s);
	}

#undef ScalarVGreat
#undef ScalarVSmall
#undef ScalarRootVGreat
#undef ScalarRootVSmall
#undef readScalar
#undef transFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_longDoubleScalar_Header
