#pragma once
#ifndef _cellSet_Header
#define _cellSet_Header

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
	tnbLib::cellSet

Description
	A collection of cell labels.

SourceFiles
	cellSet.C

\*---------------------------------------------------------------------------*/

#include <topoSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class cellSet Declaration
	\*---------------------------------------------------------------------------*/

	class cellSet
		:
		public topoSet
	{
	public:

		//- Runtime type information
		/*TypeName("cellSet");*/
		static const char* typeName_() { return "cellSet"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject. No checking.
		FoamFvMesh_EXPORT cellSet(const IOobject& obj);

		//- Construct from polyMesh and name. Checks for valid cell ids.
		FoamFvMesh_EXPORT cellSet
		(
			const polyMesh& mesh,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Construct empty from size of labelHashSet
		FoamFvMesh_EXPORT cellSet
		(
			const polyMesh& mesh,
			const word& name,
			const label sizes,
			writeOption w = NO_WRITE
		);

		//- Construct from existing set
		FoamFvMesh_EXPORT cellSet
		(
			const polyMesh& mesh,
			const word& name,
			const topoSet&,
			writeOption w = NO_WRITE
		);

		//- Construct from labelHashSet
		FoamFvMesh_EXPORT cellSet
		(
			const polyMesh& mesh,
			const word& name,
			const labelHashSet&,
			writeOption w = NO_WRITE
		);


		// Used for tetMesh cellSet only.

			//- Construct from objectRegistry and name.
		FoamFvMesh_EXPORT cellSet
		(
			const Time&,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Construct empty from objectRegistry.
		FoamFvMesh_EXPORT cellSet
		(
			const Time&,
			const word& name,
			const label size,
			writeOption w = NO_WRITE
		);

		//- Construct from labelHashSet
		FoamFvMesh_EXPORT cellSet
		(
			const Time&,
			const word& name,
			const labelHashSet&,
			writeOption w = NO_WRITE
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT cellSet(const cellSet&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~cellSet();


		// Member Functions

			//- Sync cellSet across coupled patches.
		virtual void sync(const polyMesh& mesh)
		{}

		//- Return max index+1.
		FoamFvMesh_EXPORT virtual label maxSize(const polyMesh& mesh) const;

		//- Update any stored data for new labels
		FoamFvMesh_EXPORT virtual void updateMesh(const mapPolyMesh& morphMap);

		//- Write maxLen items with label and coordinates.
		FoamFvMesh_EXPORT virtual void writeDebug
		(
			Ostream& os,
			const primitiveMesh&,
			const label maxLen
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellSet_Header
