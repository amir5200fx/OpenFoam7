#pragma once
#ifndef _coordinateSystems_Header
#define _coordinateSystems_Header

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
	tnbLib::coordinateSystems

Description
	Provides a centralized coordinateSystem collection.

Note
	Mixing normal constructors and the coordinateSystems::New constructor
	may yield unexpected results.

	\verbatim
		1
		(
		cat1
		{
			coordinateSystem  system_10;
			porosity        0.781;
			Darcy
			{
				d   d [0 -2 0 0 0]  (-1000 -1000 0.50753e+08);
				f   f [0 -1 0 0 0]  (-1000 -1000 12.83);
			}
		}
		)
	\endverbatim

	For this to work correctly, the coordinateSystem constructor must be
	supplied with both a dictionary and an objectRegistry.

SourceFiles
	coordinateSystems.C

\*---------------------------------------------------------------------------*/

#include <coordinateSystem.hxx>
#include <IOPtrList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class coordinateSystems Declaration
	\*---------------------------------------------------------------------------*/

	class coordinateSystems
		:
		public IOPtrList<coordinateSystem>
	{
	public:

		//- Runtime type information
		/*TypeName("coordinateSystems");*/
		static const char* typeName_() { return "coordinateSystems"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Read construct from IOobject
		FoamFvMesh_EXPORT explicit coordinateSystems(const IOobject&);

		//- Construct from IOobject and a PtrList
		FoamFvMesh_EXPORT coordinateSystems
		(
			const IOobject&,
			const PtrList<coordinateSystem>&
		);

		//- Construct from IOobject and transferring the PtrList contents
		FoamFvMesh_EXPORT coordinateSystems
		(
			const IOobject&,
			PtrList<coordinateSystem>&&
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT coordinateSystems(const coordinateSystems&) = delete;


		// Selectors

			//- Return previously registered or read construct from "constant"
		static FoamFvMesh_EXPORT const coordinateSystems& New(const objectRegistry&);


		// Member Functions

			//- Find and return indices for all matches
		FoamFvMesh_EXPORT labelList findIndices(const keyType& key) const;

		//- Find and return index for the first match, return -1 if not found
		FoamFvMesh_EXPORT label findIndex(const keyType& key) const;

		//- Search for given key
		FoamFvMesh_EXPORT bool found(const keyType& key) const;

		//- Return the table of contents (list of all keywords)
		FoamFvMesh_EXPORT wordList toc() const;

		//- Write data
		FoamFvMesh_EXPORT bool writeData(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const coordinateSystems&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coordinateSystems_Header
