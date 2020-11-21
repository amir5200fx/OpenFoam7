#pragma once
#ifndef _polyTopoChanger_Header
#define _polyTopoChanger_Header

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
	tnbLib::polyTopoChanger

Description
	List of mesh modifiers defining the mesh dynamics.

SourceFiles
	polyTopoChanger.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <PtrList.hxx>
#include <polyMeshModifier.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class polyMesh;
	class mapPolyMesh;
	class polyBoundaryMesh;


	// Forward declaration of friend functions and operators

	class polyTopoChanger;

	FoamDynamicMesh_EXPORT Ostream& operator<<(Ostream&, const polyTopoChanger&);


	/*---------------------------------------------------------------------------*\
						  Class polyTopoChanger Declaration
	\*---------------------------------------------------------------------------*/

	class polyTopoChanger
		:
		public PtrList<polyMeshModifier>,
		public regIOobject
	{
		// Private Member Functions

		FoamDynamicMesh_EXPORT void readModifiers();


	protected:

		// Protected data

			//- Reference to mesh
		polyMesh& mesh_;

	public:

		//- Runtime type information
		//TypeName("polyTopoChanger");
		static const char* typeName_() { return "polyTopoChanger"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Read constructor given IOobject and a polyMesh
		FoamDynamicMesh_EXPORT polyTopoChanger(const IOobject&, polyMesh&);

		//- Read constructor for given polyMesh
		explicit FoamDynamicMesh_EXPORT polyTopoChanger(polyMesh&);

		//- Disallow default bitwise copy construction
		polyTopoChanger(const polyTopoChanger&) = delete;


		//- Destructor
		virtual ~polyTopoChanger()
		{}


		// Member Functions

			//- Return the mesh reference
		const polyMesh& mesh() const
		{
			return mesh_;
		}

		//- Return a list of patch types
		FoamDynamicMesh_EXPORT wordList types() const;

		//- Return a list of patch names
		FoamDynamicMesh_EXPORT wordList names() const;

		//- Is topology change required
		FoamDynamicMesh_EXPORT bool changeTopology() const;

		//- Return topology change request
		FoamDynamicMesh_EXPORT autoPtr<polyTopoChange> topoChangeRequest() const;

		//- Modify point motion
		FoamDynamicMesh_EXPORT void modifyMotionPoints(pointField&) const;

		FoamDynamicMesh_EXPORT autoPtr<mapPolyMesh> changeMesh
		(
			const bool inflate,
			const bool syncParallel = true,
			const bool orderCells = false,
			const bool orderPoints = false
		);

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT void update(const mapPolyMesh& m);

		//- Add given set of topology modifiers to the topoChanger
		FoamDynamicMesh_EXPORT void addTopologyModifiers(const List<polyMeshModifier*>& tm);

		//- Find modifier given a name
		FoamDynamicMesh_EXPORT label findModifierID(const word& modName) const;


		//- writeData member function required by regIOobject
		FoamDynamicMesh_EXPORT bool writeData(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const polyTopoChanger&) = delete;

		bool operator!=(const polyTopoChanger&) const;
		bool operator==(const polyTopoChanger&) const;


		// Ostream operator

		FoamDynamicMesh_EXPORT friend Ostream& operator<<(Ostream&, const polyTopoChanger&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyTopoChanger_Header
