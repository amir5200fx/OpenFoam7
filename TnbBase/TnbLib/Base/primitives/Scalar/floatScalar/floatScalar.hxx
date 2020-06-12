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

	inline floatScalar max(const floatScalar s1, const floatScalar s2) { return (s1 > s2) ? s1 : s2; }
	inline floatScalar min(const floatScalar s1, const floatScalar s2) { return (s1 < s2) ? s1 : s2; }
	inline double pow(const floatScalar s, const floatScalar e) { return (double)::powf(s, e); }
		
	inline floatScalar max(const floatScalar s1, const int s2) { return (s1 > (floatScalar)s2) ? s1 : (floatScalar)s2; }
	inline floatScalar min(const floatScalar s1, const int s2) { return (s1 < (floatScalar)s2) ? s1 : (floatScalar)s2; }
	inline double pow(const floatScalar s, const int e) { return (double)::powf(s, (floatScalar)e); }
		
	inline floatScalar max(const int s1, const floatScalar s2) { return ((floatScalar)s1 > s2) ? (floatScalar)s1 : s2; }
	inline floatScalar min(const int s1, const floatScalar s2) { return ((floatScalar)s1 < s2) ? (floatScalar)s1 : s2; }
	inline double pow(const int s, const floatScalar e) { return (double)::powf((floatScalar)s, e); }
		
	inline floatScalar max(const floatScalar s1, const long s2) { return (s1 > (floatScalar)s2) ? s1 : (floatScalar)s2; }
	inline floatScalar min(const floatScalar s1, const long s2) { return (s1 < (floatScalar)s2) ? s1 : (floatScalar)s2; }
	inline double pow(const floatScalar s, const long e) { return (double)::powf(s, (floatScalar)e); }
		
	inline floatScalar max(const long s1, const floatScalar s2) { return ((floatScalar)s1 > s2) ? (floatScalar)s1 : s2; }
	inline floatScalar min(const long s1, const floatScalar s2) { return ((floatScalar)s1 < s2) ? (floatScalar)s1 : s2; }
	inline double pow(const long s, const floatScalar e) { return (double)::powf((floatScalar)s, e); }

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
	inline floatScalar sqrt(const floatScalar s) { return ::sqrtf(s); }

		
	inline floatScalar cbrt(const floatScalar s) { return ::cbrtf(s); }
		
	inline floatScalar exp(const floatScalar s) { return ::expf(s); }
		
	inline floatScalar log(const floatScalar s) { return ::logf(s); }
		
	inline floatScalar log10(const floatScalar s) { return ::log10f(s); }
		
	inline floatScalar sin(const floatScalar s) { return ::sinf(s); }
		
	inline floatScalar cos(const floatScalar s) { return ::cosf(s); }
		
	inline floatScalar tan(const floatScalar s) { return ::tanf(s); }
		
	inline floatScalar asin(const floatScalar s) { return ::asinf(s); }
		
	inline floatScalar acos(const floatScalar s) { return ::acosf(s); }
		
	inline floatScalar atan(const floatScalar s) { return ::atanf(s); }
		
	inline floatScalar sinh(const floatScalar s) { return ::sinhf(s); }
		
	inline floatScalar cosh(const floatScalar s) { return ::coshf(s); }
		
	inline floatScalar tanh(const floatScalar s) { return ::tanhf(s); }
		
	inline floatScalar asinh(const floatScalar s) { return ::asinhf(s); }
		
	inline floatScalar acosh(const floatScalar s) { return ::acoshf(s); }
		
	inline floatScalar atanh(const floatScalar s) { return ::atanhf(s); }

		// Standard ANSI-C (but not in <cmath>) transcendental functions

		
	inline floatScalar erf(const floatScalar s) { return ::erff(s); }
		
	inline floatScalar erfc(const floatScalar s) { return ::erfcf(s); }
		
	inline floatScalar lgamma(const floatScalar s) { return ::lgammaf(s); }
		
	inline floatScalar tgamma(const floatScalar s) { return ::tgammaf(s); }

		
	inline floatScalar j0(const floatScalar s) { return ::j0f(s); }
		
	inline floatScalar j1(const floatScalar s) { return ::j1f(s); }

		
	inline floatScalar y0(const floatScalar s) { return ::y0f(s); }
		
	inline floatScalar y1(const floatScalar s) { return ::y1f(s); }


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
		return (s > (floatScalar)0) ? s : (floatScalar)0;
	}


	//- Return the negative part of s.
	//  Note: this function returns the actual negative part of s as a
	//  negative number and does not change the sign
	inline floatScalar negPart(const floatScalar s)
	{
		return (s < (floatScalar)0) ? s : (floatScalar)0;
	}


	inline bool equal(const floatScalar& s1, const floatScalar& s2)
	{
		return mag(s1 - s2) <= floatScalarVSmall;
	}


	inline bool notEqual(const floatScalar s1, const floatScalar s2)
	{
		return mag(s1 - s2) > floatScalarVSmall;
	}


	inline floatScalar limit(const floatScalar s1, const floatScalar s2)
	{
		return (mag(s1) < mag(s2)) ? s1 : (floatScalar)0.0;
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
		return (floatScalar)1.0 / s;
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
		return (floatScalar)pow(s1, s2);
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
			return magb < floatScalarVSmall ? 0 : magb * sqrt(1 + sqr(maga / magb));
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

	floatScalar readFloatScalar(Istream&);

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
