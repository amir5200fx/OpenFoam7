#pragma once
#ifndef _doubleScalar_Header
#define _doubleScalar_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::doubleScalar

Description
	Double precision floating point scalar type.

SourceFiles
	doubleScalar.C

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

	typedef double doubleScalar;

	// Largest and smallest scalar values allowed in certain parts of the code.
	static const doubleScalar doubleScalarVGreat = numeric_limits<double>::max() / 10;
	static const doubleScalar doubleScalarVSmall = numeric_limits<double>::min();

	static const doubleScalar doubleScalarSmall = numeric_limits<double>::epsilon();
	static const doubleScalar doubleScalarGreat = 1.0 / doubleScalarSmall;

	static const doubleScalar doubleScalarRootVGreat = ::sqrt(doubleScalarVGreat);
	static const doubleScalar doubleScalarRootVSmall = ::sqrt(doubleScalarVSmall);

	static const doubleScalar doubleScalarRootGreat = ::sqrt(doubleScalarGreat);
	static const doubleScalar doubleScalarRootSmall = ::sqrt(doubleScalarSmall);

	//- Read whole of buf as a scalar. Return true if successful.
	inline bool readScalar(const char* buf, doubleScalar& s)
	{
		char* endPtr;
		s = strtod(buf, &endPtr);

		return (*endPtr == '\0');
	}

#define ScalarVGreat doubleScalarVGreat
#define ScalarVSmall doubleScalarVSmall
#define ScalarRootVGreat doubleScalarRootVGreat
#define ScalarRootVSmall doubleScalarRootVSmall
#define readScalar readDoubleScalar

	inline doubleScalar mag(const doubleScalar s)
	{
		return ::fabs(s);
	}


#define MAXMINPOW(retType, type1, type2)          \
                                                  \
MAXMIN(retType, type1, type2)                     \
                                                  \
inline double pow(const type1 s, const type2 e)   \
{                                                 \
    return ::pow(doubleScalar(s), doubleScalar(e));           \
}

	MAXMINPOW(doubleScalar, doubleScalar, doubleScalar)
		MAXMINPOW(doubleScalar, doubleScalar, int)
		MAXMINPOW(doubleScalar, int, doubleScalar)
		MAXMINPOW(doubleScalar, doubleScalar, long)
		MAXMINPOW(doubleScalar, long, doubleScalar)
		MAXMINPOW(doubleScalar, doubleScalar, float)
		MAXMINPOW(doubleScalar, float, doubleScalar)

#undef MAXMINPOW

#define transFunc(func)            \
inline doubleScalar func(const doubleScalar s) \
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

	// template specialisation for pTraits<doubleScalar>
	template<>
	class pTraits<doubleScalar>
	{
		doubleScalar p_;

	public:

		//- Component type
		typedef doubleScalar cmptType;

		//- Equivalent type of labels used for valid component indexing
		typedef label labelType;


		// Member constants

			//- Dimensionality of space
		static const direction dim = 3;

		//- Rank of doubleScalar is 0
		static const direction rank = 0;

		//- Number of components in doubleScalar is 1
		static const direction nComponents = 1;


		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;
		static FoamBase_EXPORT const char* const componentNames[];
		static FoamBase_EXPORT const doubleScalar zero;
		static FoamBase_EXPORT const doubleScalar one;
		static FoamBase_EXPORT const doubleScalar max;
		static FoamBase_EXPORT const doubleScalar min;
		static FoamBase_EXPORT const doubleScalar rootMax;
		static FoamBase_EXPORT const doubleScalar rootMin;


		// Constructors

			//- Construct from primitive
		FoamBase_EXPORT explicit pTraits(const doubleScalar&);

		//- Construct from Istream
		FoamBase_EXPORT pTraits(Istream&);


		// Member Functions

			//- Access to the doubleScalar value
		operator doubleScalar() const
		{
			return p_;
		}

		//- Access to the doubleScalar value
		operator doubleScalar&()
		{
			return p_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Return a string representation of a doubleScalar
	FoamBase_EXPORT word name(const doubleScalar);


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


		inline doubleScalar& setComponent(doubleScalar& s, const direction)
	{
		return s;
	}


	inline doubleScalar component(const doubleScalar s, const direction)
	{
		return s;
	}


	//- Return 1 if s is positive or 0 otherwise -1
	inline int sign(const doubleScalar s)
	{
		return (s >= 0) ? 1 : -1;
	}


	//- Return 1 if s is positive but not 0
	inline int pos(const doubleScalar s)
	{
		return (s > 0) ? 1 : 0;
	}


	//- Return 1 if s is positive or 0
	inline int pos0(const doubleScalar s)
	{
		return (s >= 0) ? 1 : 0;
	}


	//- Return 1 if s is negative but not 0
	inline int neg(const doubleScalar s)
	{
		return (s < 0) ? 1 : 0;
	}


	//- Return 1 if s is negative or 0
	inline int neg0(const doubleScalar s)
	{
		return (s <= 0) ? 1 : 0;
	}


	//- Return the positive part of s
	inline doubleScalar posPart(const doubleScalar s)
	{
		return (s > 0) ? s : 0;
	}


	//- Return the negative part of s.
	//  Note: this function returns the actual negative part of s as a
	//  negative number and does not change the sign
	inline doubleScalar negPart(const doubleScalar s)
	{
		return (s < 0) ? s : 0;
	}


	inline bool equal(const doubleScalar& s1, const doubleScalar& s2)
	{
		return mag(s1 - s2) <= ScalarVSmall;
	}


	inline bool notEqual(const doubleScalar s1, const doubleScalar s2)
	{
		return mag(s1 - s2) > ScalarVSmall;
	}


	inline doubleScalar limit(const doubleScalar s1, const doubleScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : 0.0;
	}


	inline doubleScalar minMod(const doubleScalar s1, const doubleScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : s2;
	}


	inline doubleScalar magSqr(const doubleScalar s)
	{
		return s * s;
	}


	inline doubleScalar sqr(const doubleScalar s)
	{
		return s * s;
	}


	inline doubleScalar pow3(const doubleScalar s)
	{
		return s * sqr(s);
	}


	inline doubleScalar pow4(const doubleScalar s)
	{
		return sqr(sqr(s));
	}


	inline doubleScalar pow5(const doubleScalar s)
	{
		return s * pow4(s);
	}


	inline doubleScalar pow6(const doubleScalar s)
	{
		return pow3(sqr(s));
	}


	inline doubleScalar pow025(const doubleScalar s)
	{
		return sqrt(sqrt(s));
	}


	inline doubleScalar inv(const doubleScalar s)
	{
		return 1.0 / s;
	}


	inline doubleScalar dot(const doubleScalar s1, const doubleScalar s2)
	{
		return s1 * s2;
	}


	inline doubleScalar cmptMultiply(const doubleScalar s1, const doubleScalar s2)
	{
		return s1 * s2;
	}


	inline doubleScalar cmptPow(const doubleScalar s1, const doubleScalar s2)
	{
		return pow(s1, s2);
	}


	inline doubleScalar cmptDivide(const doubleScalar s1, const doubleScalar s2)
	{
		return s1 / s2;
	}


	inline doubleScalar cmptMax(const doubleScalar s)
	{
		return s;
	}


	inline doubleScalar cmptMin(const doubleScalar s)
	{
		return s;
	}


	inline doubleScalar cmptAv(const doubleScalar s)
	{
		return s;
	}


	inline doubleScalar cmptSqr(const doubleScalar s)
	{
		return sqr(s);
	}


	inline doubleScalar cmptMag(const doubleScalar s)
	{
		return mag(s);
	}


	inline doubleScalar sqrtSumSqr(const doubleScalar a, const doubleScalar b)
	{
		doubleScalar maga = mag(a);
		doubleScalar magb = mag(b);

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
	inline doubleScalar stabilise(const doubleScalar s, const doubleScalar small)
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

	doubleScalar readScalar(Istream&);

	FoamBase_EXPORT void writeEntry(Ostream& os, const doubleScalar value);


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	FoamBase_EXPORT Istream& operator>>(Istream&, doubleScalar&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const doubleScalar);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline doubleScalar hypot(const doubleScalar x, const doubleScalar y)
	{
		return ::hypot(x, y);
	}

	inline doubleScalar atan2(const doubleScalar y, const doubleScalar x)
	{
		return ::atan2(y, x);
	}

	inline doubleScalar jn(const int n, const doubleScalar s)
	{
		return ::_jn(n, s);
	}

	inline doubleScalar yn(const int n, const doubleScalar s)
	{
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

#endif // !_doubleScalar_Header
