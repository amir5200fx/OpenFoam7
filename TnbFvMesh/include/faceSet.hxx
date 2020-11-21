#pragma once
#ifndef _faceSet_Header
#define _faceSet_Header

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
	tnbLib::faceSet

Description
	A list of face labels.

SourceFiles
	faceSet.C

\*---------------------------------------------------------------------------*/

#include <topoSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class faceSet Declaration
	\*---------------------------------------------------------------------------*/

	class faceSet
		:
		public topoSet
	{


	public:

		//- Runtime type information
		/*TypeName("faceSet");*/
		static const char* typeName_() { return "faceSet"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors


			//- Construct from IOobject
		FoamFvMesh_EXPORT faceSet(const IOobject& obj);

		//- Construct from objectRegistry and name
		FoamFvMesh_EXPORT faceSet
		(
			const polyMesh& mesh,
			const word& name,
			readOption r = MUST_READ,
			writeOption w = NO_WRITE
		);

		//- Construct from additional size of labelHashSet
		FoamFvMesh_EXPORT faceSet
		(
			const polyMesh& mesh,
			const word& name,
			const label,
			writeOption w = NO_WRITE
		);

		//- Construct from existing set
		FoamFvMesh_EXPORT faceSet
		(
			const polyMesh& mesh,
			const word& name,
			const topoSet&,
			writeOption w = NO_WRITE
		);

		//- Construct from additional labelHashSet
		FoamFvMesh_EXPORT faceSet
		(
			const polyMesh& mesh,
			const word& name,
			const labelHashSet&,
			writeOption w = NO_WRITE
		);


		//- Destructor
		FoamFvMesh_EXPORT virtual ~faceSet();


		// Member Functions

			//- Sync faceSet across coupled patches.
		FoamFvMesh_EXPORT virtual void sync(const polyMesh& mesh);

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

#endif // !_faceSet_Header
