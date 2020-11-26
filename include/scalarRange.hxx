#pragma once
#ifndef _scalarRange_Header
#define _scalarRange_Header

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
	tnbLib::scalarRange

Description
	A scalar range specifier.

	The range selector can be specified as an "LOWER:UPPER" range, as a
	"LOWER:" bound, as an ":UPPER" bound or simply as an "EXACT" value.
	The read constructor uses a colon (:) as a range marker and a comma (,)
	to delimit the next possible range selector.

SourceFiles
	scalarRange.C

\*---------------------------------------------------------------------------*/

#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Istream;
	class Ostream;

	// Forward declaration of friend functions and operators
	class scalarRange;
	FoamBase_EXPORT Istream& operator>>(Istream&, scalarRange&);
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const scalarRange&);


	/*---------------------------------------------------------------------------*\
							Class scalarRange Declaration
	\*---------------------------------------------------------------------------*/

	class scalarRange
	{
		//- Enumeration defining the types of token
		enum rangeType
		{
			EMPTY = 0,
			EXACT,
			LOWER,
			UPPER,
			RANGE
		};


		// Private Data

		enum rangeType type_;
		scalar value_;
		scalar value2_;


	public:

		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct an empty range
		FoamBase_EXPORT scalarRange();

		//- Construct a range from lower to upper
		FoamBase_EXPORT scalarRange(const scalar lower, const scalar upper);

		//- Construct from Istream.
		//  Since commas can be used as list delimiters,
		//  leading and trailing commas are ignored.
		FoamBase_EXPORT scalarRange(Istream&);


		// Member Functions

			//- Is the range empty?
		FoamBase_EXPORT bool empty() const;

		//- Is the range non-empty?
		FoamBase_EXPORT bool valid() const;

		//- Is the range 'EXACT'?
		FoamBase_EXPORT bool isExact() const;

		//- The value constituting an 'EXACT' match
		//  or the values for 'UPPER' or 'LOWER' limits
		FoamBase_EXPORT scalar value() const;

		//- The lower limit
		FoamBase_EXPORT scalar lower() const;

		//- The upper limit
		FoamBase_EXPORT scalar upper() const;

		//- Return true if the value is within the range
		FoamBase_EXPORT bool selected(const scalar) const;


		// Member Operators

		FoamBase_EXPORT bool operator==(const scalarRange&) const;
		FoamBase_EXPORT bool operator!=(const scalarRange&) const;


		// IOstream Operators

		friend FoamBase_EXPORT Istream& operator>>(Istream&, scalarRange&);
		friend FoamBase_EXPORT Ostream& operator<<(Ostream&, const scalarRange&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_scalarRange_Header
