#pragma once
#ifndef _tetMatcher_Header
#define _tetMatcher_Header

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
	tnbLib::tetMatcher

Description
	A cellMatcher for tet cells

See also
	cellMatcher

SourceFiles
	tetMatcher.C

\*---------------------------------------------------------------------------*/

#include <cellMatcher.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class tetMatcher Declaration
	\*---------------------------------------------------------------------------*/

	class tetMatcher
		:
		public cellMatcher
	{
		// Static Data Members

			//- Constants for this shape
		static FoamBase_EXPORT const label vertPerCell;
		static FoamBase_EXPORT const label facePerCell;
		static FoamBase_EXPORT const label maxVertPerFace;


	public:

		// Constructors

			//- Construct null
		FoamBase_EXPORT tetMatcher();

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT tetMatcher(const tetMatcher&) = delete;


		//- Destructor
		FoamBase_EXPORT ~tetMatcher();


		// Member Functions

		virtual label nVertPerCell() const
		{
			return vertPerCell;
		}

		virtual label nFacePerCell() const
		{
			return facePerCell;
		}

		virtual label nMaxVertPerFace() const
		{
			return maxVertPerFace;
		}

		FoamBase_EXPORT virtual label faceHashValue() const;

		FoamBase_EXPORT virtual bool faceSizeMatch(const faceList&, const labelList&) const;

		FoamBase_EXPORT virtual bool matchShape
		(
			const bool checkOnly,
			const faceList& faces,
			const labelList& faceOwner,
			const label celli,
			const labelList& myFaces
		);

		FoamBase_EXPORT virtual bool isA(const primitiveMesh& mesh, const label celli);

		FoamBase_EXPORT virtual bool isA(const faceList&);

		FoamBase_EXPORT virtual bool matches
		(
			const primitiveMesh& mesh,
			const label celli,
			cellShape& shape
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const tetMatcher&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tetMatcher_Header
