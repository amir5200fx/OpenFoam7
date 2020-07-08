#pragma once
#ifndef _ops_Header
#define _ops_Header

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

InClass
	tnbLib::Pstream

Description
	Combination-Reduction operation for a parallel run.

	The information from all nodes is collected on the master node,
	combined using the given combination function and the result is
	broadcast to all nodes

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define EqOp(opName, op)                                                       \
                                                                               \
template<class T1, class T2>                                                   \
class opName##Op2                                                              \
{                                                                              \
public:                                                                        \
                                                                               \
    void operator()(T1& x, const T2& y) const                                  \
    {                                                                          \
        op;                                                                    \
    }                                                                          \
};                                                                             \
                                                                               \
template<class T>                                                              \
class opName##Op                                                               \
{                                                                              \
public:                                                                        \
                                                                               \
    void operator()(T& x, const T& y) const                                    \
    {                                                                          \
        op;                                                                    \
    }                                                                          \
};

	EqOp(eq, x = y)
		EqOp(plusEq, x += y)
		EqOp(minusEq, x -= y)
		EqOp(multiplyEq, x *= y)
		EqOp(divideEq, x /= y)
		EqOp(eqSqr, x = sqr(y))
		EqOp(eqMag, x = mag(y))
		EqOp(plusEqMagSqr, x += magSqr(y))
		EqOp(maxEq, x = max(x, y))
		EqOp(minEq, x = min(x, y))
		EqOp(minMagSqrEq, x = (magSqr(x) <= magSqr(y) ? x : y))
		EqOp(maxMagSqrEq, x = (magSqr(x) >= magSqr(y) ? x : y))
		EqOp(andEq, x = (x && y))
		EqOp(orEq, x = (x || y))

		EqOp(eqMinus, x = -y)

		EqOp(nopEq, (void)x)

#undef EqOp


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#if __GNUC__
#define WARNRETURN __attribute__((warn_unused_result))
#else
#define WARNRETURN
#endif

#define Op(opName, op)                                                         \
                                                                               \
    template<class T, class T1, class T2>                                      \
    class opName##Op3                                                          \
    {                                                                          \
    public:                                                                    \
                                                                               \
        T operator()(const T1& x, const T2& y) const WARNRETURN                \
        {                                                                      \
            return op;                                                         \
        }                                                                      \
    };                                                                         \
                                                                               \
    template<class T1, class T2>                                               \
    class opName##Op2                                                          \
    {                                                                          \
    public:                                                                    \
                                                                               \
        T1 operator()(const T1& x, const T2& y) const WARNRETURN               \
        {                                                                      \
            return op;                                                         \
        }                                                                      \
    };                                                                         \
                                                                               \
    template<class T>                                                          \
    class opName##Op                                                           \
    {                                                                          \
    public:                                                                    \
                                                                               \
        T operator()(const T& x, const T& y) const WARNRETURN                  \
        {                                                                      \
            return op;                                                         \
        }                                                                      \
    };


#define weightedOp(opName, op)                                                 \
                                                                               \
    template<class Type, class CombineOp>                                      \
    class opName##WeightedOp                                                   \
    {                                                                          \
        const CombineOp& cop_;                                                 \
                                                                               \
        public:                                                                \
                                                                               \
            opName##WeightedOp(const CombineOp& cop)                           \
            :                                                                  \
                cop_(cop)                                                      \
            {}                                                                 \
                                                                               \
            void operator()                                                    \
            (                                                                  \
                Type& x,                                                       \
                const label index,                                             \
                const Type& y,                                                 \
                const scalar weight                                            \
            ) const                                                            \
            {                                                                  \
                cop_(x, op);                                                   \
            }                                                                  \
    };                                                                         \


		Op(sum, x + y)

		Op(plus, x + y)
		Op(minus, x - y)
		Op(multiply, x * y)
		Op(divide, x / y)
		Op(cmptMultiply, cmptMultiply(x, y))
		Op(cmptPow, cmptPow(x, y))
		Op(cmptDivide, cmptDivide(x, y))
		Op(stabilise, stabilise(x, y))
		Op(max, max(x, y))
		Op(min, min(x, y))
		Op(minMagSqr, (magSqr(x) <= magSqr(y) ? x : y))
		Op(maxMagSqr, (magSqr(x) >= magSqr(y) ? x : y))
		Op(minMod, minMod(x, y))
		Op(and, x && y)
		Op(or , x || y)
		Op(eqEq, x == y)
		Op(less, x < y)
		Op(lessEq, x <= y)
		Op(greater, x > y)
		Op(greaterEq, x >= y)

		weightedOp(multiply, (weight*y))

#undef Op
#undef weightedOp
#undef WARNRETURN

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ops_Header
