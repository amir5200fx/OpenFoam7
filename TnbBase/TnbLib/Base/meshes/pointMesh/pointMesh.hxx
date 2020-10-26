#pragma once
#ifndef _pointMesh_Header
#define _pointMesh_Header

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
	tnbLib::pointMesh

Description
	Mesh representing a set of points created from polyMesh.

\*---------------------------------------------------------------------------*/

#include <GeoMesh.hxx>
#include <MeshObject.hxx>
#include <polyMesh.hxx>
#include <pointBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class pointMesh Declaration
	\*---------------------------------------------------------------------------*/

	class pointMesh
		:
		public MeshObject<polyMesh, PatchMeshObject, pointMesh>,
		public GeoMesh<polyMesh>
	{
		// Permanent data

			//- Boundary mesh
		pointBoundaryMesh boundary_;


		// Private Member Functions

			//- Map all fields
		FoamBase_EXPORT void mapFields(const mapPolyMesh&);


	public:

		// Declare name of the class and its debug switch
		//ClassName("pointMesh");
		static const char* typeName_() { return "pointMesh"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		typedef pointMesh Mesh;
		typedef pointBoundaryMesh BoundaryMesh;


		// Constructors

			//- Construct from polyMesh
		FoamBase_EXPORT explicit pointMesh(const polyMesh& pMesh);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT pointMesh(const pointMesh&) = delete;


		//- Destructor
		FoamBase_EXPORT ~pointMesh();


		// Member Functions

			//- Return number of points
		label size() const
		{
			return size(*this);
		}

		//- Return number of points
		static label size(const Mesh& mesh)
		{
			return mesh.GeoMesh<polyMesh>::mesh_.nPoints();
		}

		//- Return reference to boundary mesh
		const pointBoundaryMesh& boundary() const
		{
			return boundary_;
		}

		//- Return parallel info
		const globalMeshData& globalData() const
		{
			return GeoMesh<polyMesh>::mesh_.globalData();
		}

		//- Return database. For now is its polyMesh.
		const objectRegistry& thisDb() const
		{
			return GeoMesh<polyMesh>::mesh_.thisDb();
		}

		//- Reset for changed polyMesh
		FoamBase_EXPORT void reset(const bool validBoundary);


		// Mesh callbacks

			//- Move points
		FoamBase_EXPORT virtual bool movePoints();

		//- Update the mesh corresponding to given map
		FoamBase_EXPORT virtual void updateMesh(const mapPolyMesh& mpm);

		//- Reordered/removed trailing patches. If validBoundary call is
		//  parallel synced and all add the same patch with same settings
		FoamBase_EXPORT virtual void reorderPatches
		(
			const labelUList& newToOld,
			const bool validBoundary
		);

		//- Inserted patch at patchi
		FoamBase_EXPORT virtual void addPatch(const label patchi);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const pointMesh&) = delete;

		bool operator!=(const pointMesh& pm) const
		{
			return &pm != this;
		}

		bool operator==(const pointMesh& pm) const
		{
			return &pm == this;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointMesh_Header
