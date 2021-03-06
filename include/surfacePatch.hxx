#pragma once
#ifndef _surfacePatch_Header
#define _surfacePatch_Header

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
	tnbLib::surfacePatch

Description
	'Patch' on surface as subset of triSurface.

SourceFiles
	surfacePatch.C

\*---------------------------------------------------------------------------*/

#include <geometricSurfacePatch.hxx>
#include <word.hxx>
#include <label.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class surfacePatch;

	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfacePatch&);


	/*---------------------------------------------------------------------------*\
							   Class surfacePatch Declaration
	\*---------------------------------------------------------------------------*/

	class surfacePatch
		:
		public geometricSurfacePatch
	{
		// Private Data

			//- Size of this patch in the triSurface face list
		label size_;

		//- Start label of this patch in the triSurface face list
		label start_;


	public:

		//- Runtime type information
		/*ClassName("surfacePatch");*/
		static const char* typeName_() { return "surfacePatch"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct null
		FoamFvMesh_EXPORT surfacePatch();

		//- Construct from components
		FoamFvMesh_EXPORT surfacePatch
		(
			const word& geometricType,
			const word& name,
			const label size,
			const label start,
			const label index
		);

		//- Construct from Istream
		FoamFvMesh_EXPORT surfacePatch(Istream& is, const label index);

		//- Construct from dictionary
		FoamFvMesh_EXPORT surfacePatch
		(
			const word& name,
			const dictionary& dict,
			const label index
		);


		// Member Functions

			//- Return start label of this patch in the polyMesh face list
		label start() const
		{
			return start_;
		}

		//- Return start label of this patch in the polyMesh face list
		label& start()
		{
			return start_;
		}

		//- Return size of this patch in the polyMesh face list
		label size() const
		{
			return size_;
		}

		//- Return size of this patch in the polyMesh face list
		label& size()
		{
			return size_;
		}

		//- Write
		FoamFvMesh_EXPORT void write(Ostream&) const;

		//- Write dictionary
		FoamFvMesh_EXPORT void writeDict(Ostream&) const;


		// Member Operators

		FoamFvMesh_EXPORT bool operator!=(const surfacePatch&) const;

		//- compare.
		FoamFvMesh_EXPORT bool operator==(const surfacePatch&) const;

		// IOstream Operators

		FoamFvMesh_EXPORT friend Ostream& operator<<(Ostream&, const surfacePatch&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfacePatch_Header
