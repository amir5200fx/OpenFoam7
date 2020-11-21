#pragma once
#ifndef _curve_Header
#define _curve_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

Class
	tnbLib::curve

Description
	A single curve in a graph.

SourceFiles
	curve.C

\*---------------------------------------------------------------------------*/

#include <tnbString.hxx>
#include <primitiveFields.hxx>
#include <autoPtr.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class curve;
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const curve&);


	/*---------------------------------------------------------------------------*\
							   Class curve Declaration
	\*---------------------------------------------------------------------------*/

	class curve
		:
		public scalarField
	{

	public:

		//- The style (line, symbol, etc) of a curve
		class curveStyle
		{

		public:

			//- Enumeration definitions
			enum curveStyleNo
			{
				CONTINUOUS,
				SYMBOL,
				SYMBOL_CURVE,
				SYMBOL_WITH_ERROR_BARS,
				SYMBOL_WITH_VARIABLE_SIZE
			};


		private:

			// Private Data

			curveStyleNo CurveStyleNo;


		public:


			// Constructors

				//- Construct given a curveStyleNo
			curveStyle(const curveStyleNo csn)
				:
				CurveStyleNo(csn)
			{}

			//- Construct from Istream
			curveStyle(Istream& is)
				:
				CurveStyleNo(curveStyleNo(readInt(is)))
			{}


			// Ostream operator

			friend Ostream& operator<<(Ostream& os, const curveStyle& cs)
			{
				os << int(cs.CurveStyleNo);
				return os;
			}
		};


	private:

		// Private Data

		string name_;
		curveStyle style_;


	public:

		// Constructors

			//- Construct as interpolation of an existing curve
			// curve(const curve&, const label);

			//- Construct from name, style and size
		FoamBase_EXPORT curve
		(
			const string& name,
			const curveStyle& style,
			const label l
		);

		//- Construct from the components
		FoamBase_EXPORT curve
		(
			const string&,
			const curveStyle&,
			const scalarField& y
		);

		autoPtr<curve> clone() const
		{
			return autoPtr<curve>(new curve(*this));
		}


		// Member Functions

			// Access

		const string& name() const
		{
			return name_;
		}

		const curveStyle& style() const
		{
			return style_;
		}


		// Friend Functions

			//- Gradient of the curve
			// friend curve grad(const curve&);


		// Ostream operator

		friend Ostream& operator<<(Ostream&, const curve&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_curve_Header
