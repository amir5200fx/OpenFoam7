#pragma once
#ifndef _floatScalar_Header
#define _floatScalar_Header

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
	tnbLib::floatScalar

Description
	Float precision floating point scalar type.

SourceFiles
	floatScalar.C

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

	typedef float floatScalar;

	// Largest and smallest scalar values allowed in certain parts of the code
	static const floatScalar floatScalarVGreat = numeric_limits<float>::max() / 10;
	static const floatScalar floatScalarVSmall = numeric_limits<float>::min();

	static const floatScalar floatScalarSmall = numeric_limits<float>::epsilon();
	static const floatScalar floatScalarGreat = 1.0 / floatScalarSmall;

	static const floatScalar floatScalarRootVGreat = ::sqrt(floatScalarVGreat);
	static const floatScalar floatScalarRootVSmall = ::sqrt(floatScalarVSmall);

	static const floatScalar floatScalarRootGreat = ::sqrt(floatScalarGreat);
	static const floatScalar floatScalarRootSmall = ::sqrt(floatScalarSmall);

	//- Read whole of buf as a scalar. Return true if successful.
	inline bool readScalar(const char* buf, floatScalar& s)
	{
		char* endPtr;
		s = strtof(buf, &endPtr);

		return (*endPtr == '\0');
	}

#define ScalarVGreat floatScalarVGreat
#define ScalarVSmall floatScalarVSmall
#define ScalarRootVGreat floatScalarRootVGreat
#define ScalarRootVSmall floatScalarRootVSmall
#define readScalar readFloatScalar

	inline floatScalar mag(const floatScalar s)
	{
		return ::fabsf(s);
	}


#define MAXMINPOW(retType, type1, type2)          \
                                                  \
MAXMIN(retType, type1, type2)                     \
                                                  \
inline double pow(const type1 s, const type2 e)   \
{                                                 \
    return ::powf(s, e);                          \
}

	MAXMINPOW(floatScalar, floatScalar, floatScalar)
		MAXMINPOW(floatScalar, floatScalar, int)
		MAXMINPOW(floatScalar, int, floatScalar)
		MAXMINPOW(floatScalar, floatScalar, long)
		MAXMINPOW(floatScalar, long, floatScalar)

#undef MAXMINPOW


#define transFunc(func)            \
inline floatScalar func(const floatScalar s) \
{                                  \
    return ::func##f(s);           \
}

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// template specialisation for pTraits<floatScalar>
	template<>
	class pTraits<floatScalar>
	{
		floatScalar p_;

	public:

		//- Component type
		typedef floatScalar cmptType;

		//- Equivalent type of labels used for valid component indexing
		typedef label labelType;


		// Member constants

			//- Dimensionality of space
		static const direction dim = 3;

		//- Rank of floatScalar is 0
		static const direction rank = 0;

		//- Number of components in floatScalar is 1
		static const direction nComponents = 1;


		// Static Data Members

		static const char* const typeName;
		static const char* const componentNames[];
		static const floatScalar zero;
		static const floatScalar one;
		static const floatScalar max;
		static const floatScalar min;
		static const floatScalar rootMax;
		static const floatScalar rootMin;


		// Constructors

			//- Construct from primitive
		explicit pTraits(const floatScalar&);

		//- Construct from Istream
		pTraits(Istream&);


		// Member Functions

			//- Access to the floatScalar value
		operator floatScalar() const
		{
			return p_;
		}

		//- Access to the floatScalar value
		operator floatScalar&()
		{
			return p_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Return a string representation of a floatScalar
	word name(const floatScalar);


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

		transFunc(j0)
		transFunc(j1)

		transFunc(y0)
		transFunc(y1)


		inline floatScalar& setComponent(floatScalar& s, const direction)
	{
		return s;
	}


	inline floatScalar component(const floatScalar s, const direction)
	{
		return s;
	}


	//- Return 1 if s is positive or 0 otherwise -1
	inline int sign(const floatScalar s)
	{
		return (s >= 0) ? 1 : -1;
	}


	//- Return 1 if s is positive but not 0
	inline int pos(const floatScalar s)
	{
		return (s > 0) ? 1 : 0;
	}


	//- Return 1 if s is positive or 0
	inline int pos0(const floatScalar s)
	{
		return (s >= 0) ? 1 : 0;
	}


	//- Return 1 if s is negative but not 0
	inline int neg(const floatScalar s)
	{
		return (s < 0) ? 1 : 0;
	}


	//- Return 1 if s is negative or 0
	inline int neg0(const floatScalar s)
	{
		return (s <= 0) ? 1 : 0;
	}


	//- Return the positive part of s
	inline floatScalar posPart(const floatScalar s)
	{
		return (s > 0) ? s : 0;
	}


	//- Return the negative part of s.
	//  Note: this function returns the actual negative part of s as a
	//  negative number and does not change the sign
	inline floatScalar negPart(const floatScalar s)
	{
		return (s < 0) ? s : 0;
	}


	inline bool equal(const floatScalar& s1, const floatScalar& s2)
	{
		return mag(s1 - s2) <= ScalarVSmall;
	}


	inline bool notEqual(const floatScalar s1, const floatScalar s2)
	{
		return mag(s1 - s2) > ScalarVSmall;
	}


	inline floatScalar limit(const floatScalar s1, const floatScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : 0.0;
	}


	inline floatScalar minMod(const floatScalar s1, const floatScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : s2;
	}


	inline floatScalar magSqr(const floatScalar s)
	{
		return s * s;
	}


	inline floatScalar sqr(const floatScalar s)
	{
		return s * s;
	}


	inline floatScalar pow3(const floatScalar s)
	{
		return s * sqr(s);
	}


	inline floatScalar pow4(const floatScalar s)
	{
		return sqr(sqr(s));
	}


	inline floatScalar pow5(const floatScalar s)
	{
		return s * pow4(s);
	}


	inline floatScalar pow6(const floatScalar s)
	{
		return pow3(sqr(s));
	}


	inline floatScalar pow025(const floatScalar s)
	{
		return sqrt(sqrt(s));
	}


	inline floatScalar inv(const floatScalar s)
	{
		return 1.0 / s;
	}


	inline floatScalar dot(const floatScalar s1, const floatScalar s2)
	{
		return s1 * s2;
	}


	inline floatScalar cmptMultiply(const floatScalar s1, const floatScalar s2)
	{
		return s1 * s2;
	}


	inline floatScalar cmptPow(const floatScalar s1, const floatScalar s2)
	{
		return pow(s1, s2);
	}


	inline floatScalar cmptDivide(const floatScalar s1, const floatScalar s2)
	{
		return s1 / s2;
	}


	inline floatScalar cmptMax(const floatScalar s)
	{
		return s;
	}


	inline floatScalar cmptMin(const floatScalar s)
	{
		return s;
	}


	inline floatScalar cmptAv(const floatScalar s)
	{
		return s;
	}


	inline floatScalar cmptSqr(const floatScalar s)
	{
		return sqr(s);
	}


	inline floatScalar cmptMag(const floatScalar s)
	{
		return mag(s);
	}


	inline floatScalar sqrtSumSqr(const floatScalar a, const floatScalar b)
	{
		floatScalar maga = mag(a);
		floatScalar magb = mag(b);

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
	inline floatScalar stabilise(const floatScalar s, const floatScalar small)
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

	floatScalar readScalar(Istream&);

	void writeEntry(Ostream& os, const floatScalar value);


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	Istream& operator>>(Istream&, floatScalar&);
	Ostream& operator<<(Ostream&, const floatScalar);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline floatScalar hypot(const floatScalar x, const floatScalar y)
	{
		return ::hypotf(x, y);
	}

	inline floatScalar atan2(const floatScalar y, const floatScalar x)
	{
		return ::atan2f(y, x);
	}

	inline floatScalar jn(const int n, const floatScalar s)
	{
		return ::jnf(n, s);
	}

	inline floatScalar yn(const int n, const floatScalar s)
	{
		return ::ynf(n, s);
	}

#undef ScalarVGreat
#undef ScalarVSmall
#undef ScalarRootVGreat
#undef ScalarRootVSmall
#undef readScalar
#undef transFunc


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

#endif // !_floatScalar_Header
