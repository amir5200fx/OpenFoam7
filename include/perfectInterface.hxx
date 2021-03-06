#pragma once
#ifndef _perfectInterface_Header
#define _perfectInterface_Header

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
	tnbLib::perfectInterface

Description
	Hack of attachDetach to couple patches when they perfectly align.
	Does not decouple. Used by stitchMesh app. Does geometric matching.

SourceFiles
	perfectInterface.C

\*---------------------------------------------------------------------------*/

#include <polyMeshModifier.hxx>
#include <polyPatchID.hxx>
#include <ZoneIDs.hxx>
#include <indirectPrimitivePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class Time;

	/*---------------------------------------------------------------------------*\
						   Class perfectInterface Declaration
	\*---------------------------------------------------------------------------*/

	class perfectInterface
		:
		public polyMeshModifier
	{
		// Private Data

			//- Master face zone ID
		faceZoneID faceZoneID_;

		//- Master patch ID
		polyPatchID masterPatchID_;

		//- Slave patch ID
		polyPatchID slavePatchID_;

		//- Tolerance used for distance comparison (fraction of minimum edge
		//  length)
		static FoamDynamicMesh_EXPORT const scalar tol_;

		// Private Member Functions

			//- Calculate face centres on patch
		static FoamDynamicMesh_EXPORT pointField calcFaceCentres(const indirectPrimitivePatch&);


	public:

		//- Runtime type information
		//TypeName("perfectInterface");
		static const char* typeName_() { return "perfectInterface"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamDynamicMesh_EXPORT perfectInterface
		(
			const word& name,
			const label index,
			const polyTopoChanger& mme,
			const word& faceZoneName,
			const word& masterPatchName,
			const word& slavePatchName
		);

		//- Construct from dictionary
		FoamDynamicMesh_EXPORT perfectInterface
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyTopoChanger& mme
		);

		//- Disallow default bitwise copy construction
		perfectInterface(const perfectInterface&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT virtual ~perfectInterface();


		// Member Functions

			//- Check for topology change
		FoamDynamicMesh_EXPORT virtual bool changeTopology() const;

		//- Insert the layer addition/removal instructions
		//  into the topological change
		FoamDynamicMesh_EXPORT virtual void setRefinement(polyTopoChange&) const;

		//- Insert the layer addition/removal instructions
		//  into the topological change. Uses only mesh, not any of the
		//  patch and zone indices. Bit of a workaround - used in extruding
		//  a mesh.
		FoamDynamicMesh_EXPORT virtual void setRefinement
		(
			const indirectPrimitivePatch& pp0,
			const indirectPrimitivePatch& pp1,
			polyTopoChange&
		) const;

		//- Modify motion points to comply with the topological change
		FoamDynamicMesh_EXPORT virtual void modifyMotionPoints(pointField& motionPoints) const;

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT virtual void updateMesh(const mapPolyMesh&);

		//- Write
		FoamDynamicMesh_EXPORT virtual void write(Ostream&) const;

		//- Write dictionary
		FoamDynamicMesh_EXPORT virtual void writeDict(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const perfectInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_perfectInterface_Header
