#pragma once
#ifndef _enrichedPatch_Header
#define _enrichedPatch_Header

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
	tnbLib::enrichedPatch

Description
	The enriched patch contains a double set of faces from the two
	sides of the sliding interface before the cutting.

	The patch basically consists of two over-lapping sets of faces sitting
	on a common point support, where every edge may be shared by more than
	2 faces.  The patch points are collected in a map.  Additional
	information needed for cutting is the point insertion into every edge
	of master and slave.

	Note:
	If new points are created during master-slave edge cutting, they
	should be registered with the pointMap.


SourceFiles
	enrichedPatch.C
	enrichedPatchCutFaces.C
	enrichedPatchFaces.C
	enrichedPatchPointMap.C
	enrichedPatchPointMergeMap.C
	enrichedPatchPointPoints.C

\*---------------------------------------------------------------------------*/

#include <primitiveFacePatch.hxx>
#include <Map.hxx>
#include <point.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class enrichedPatch Declaration
	\*---------------------------------------------------------------------------*/

	class enrichedPatch
	{
		// Private Data

			//- Reference to master patch
		const primitiveFacePatch& masterPatch_;

		//- Reference to slave patch
		const primitiveFacePatch& slavePatch_;

		//- Map of points supporting patch faces
		mutable Map<point> pointMap_;

		//- Has the point map been completed?
		mutable bool pointMapComplete_;

		//- Map of point merges
		mutable Map<label> pointMergeMap_;

		//- Slave point point hits
		const labelList& slavePointPointHits_;

		//- Slave point edge hits
		const labelList& slavePointEdgeHits_;

		//- Slave point face hits
		const List<objectHit>& slavePointFaceHits_;


		// Demand-driven private data

			//- Enriched patch
		mutable faceList* enrichedFacesPtr_;

		//- Mesh points
		mutable labelList* meshPointsPtr_;

		//- Local faces
		mutable faceList* localFacesPtr_;

		//- Local points
		mutable pointField* localPointsPtr_;

		//- Point-point addressing
		mutable labelListList* pointPointsPtr_;

		// Master point addressing
		mutable Map<labelList>* masterPointFacesPtr_;


		// Cut faces and addressing

			//- Cut faces
		mutable faceList* cutFacesPtr_;

		//- Cut face master
		//  - the face on the master patch for internal faces
		//  - the creator face for boundary face
		mutable labelList* cutFaceMasterPtr_;

		//- Cut face slave
		//  - the face on the slave patch for internal faces
		//  - -1 for boundary face
		mutable labelList* cutFaceSlavePtr_;


		// Private Member Functions

			// Creation of demand-driven private data

				//- Calculate point merge map
		FoamDynamicMesh_EXPORT void calcPointMergeMap() const;

		//- Complete point map
		FoamDynamicMesh_EXPORT void completePointMap() const;

		//- Calculate mesh points
		FoamDynamicMesh_EXPORT void calcMeshPoints() const;

		//- Calculate local points
		FoamDynamicMesh_EXPORT void calcLocalPoints() const;

		//- Calculate local faces
		FoamDynamicMesh_EXPORT void calcLocalFaces() const;

		//- Calculate point-point addressing
		FoamDynamicMesh_EXPORT void calcPointPoints() const;

		//- Calculate master point addressing
		FoamDynamicMesh_EXPORT void calcMasterPointFaces() const;

		//- Calculate cut faces
		FoamDynamicMesh_EXPORT void calcCutFaces() const;

		//- Clear cut faces
		FoamDynamicMesh_EXPORT void clearCutFaces();

		//- Clear out demand-driven data
		FoamDynamicMesh_EXPORT void clearOut();


		// Static Data Members

			//- Estimated ratio of original-to-enriched face size
		static FoamDynamicMesh_EXPORT const label enrichedFaceRatio_;

		//- Estimated number of master face hits by slave points
		static FoamDynamicMesh_EXPORT const label nFaceHits_;

		//- Size of face on which the check is forced
		static FoamDynamicMesh_EXPORT const label maxFaceSizeDebug_;


	public:

		// Static Data Members
		//ClassName("enrichedPatch");
		static const char* typeName_() { return "enrichedPatch"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;

		// Constructors

			//- Construct from components
		FoamDynamicMesh_EXPORT enrichedPatch
		(
			const primitiveFacePatch& masterPatch,
			const primitiveFacePatch& slavePatch,
			const labelList& slavePointPointHits,
			// -1 or common point snapped to
			const labelList& slavePointEdgeHits,
			// -1 or common edge snapped to
			const List<objectHit>& slavePointFaceHits
			// master face snapped to
		);

		//- Disallow default bitwise copy construction
		enrichedPatch(const enrichedPatch&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~enrichedPatch();


		// Member Functions

			// Access

				//- Return non-const access to point map to add points
		FoamDynamicMesh_EXPORT Map<point>& pointMap();

		//- Return map of points
		FoamDynamicMesh_EXPORT const Map<point>& pointMap() const;

		//- Return map of point merges
		Map<label>& pointMergeMap()
		{
			return pointMergeMap_;
		}

		//- Return map of point merges
		const Map<label>& pointMergeMap() const
		{
			return pointMergeMap_;
		}


		// Topological data

			//- Calculate enriched faces
		FoamDynamicMesh_EXPORT void calcEnrichedFaces
		(
			const labelListList& pointsIntoMasterEdges,
			const labelListList& pointsIntoSlaveEdges,
			const pointField& projectedSlavePoints
		);

		//- Return enriched faces
		FoamDynamicMesh_EXPORT const faceList& enrichedFaces() const;

		//- Return mesh points
		FoamDynamicMesh_EXPORT const labelList& meshPoints() const;

		//- Return local faces
		FoamDynamicMesh_EXPORT const faceList& localFaces() const;

		//- Return local points
		FoamDynamicMesh_EXPORT const pointField& localPoints() const;

		//- Return point-point addressing
		FoamDynamicMesh_EXPORT const labelListList& pointPoints() const;

		//- Master point face addressing
		FoamDynamicMesh_EXPORT const Map<labelList>& masterPointFaces() const;


		// Cut faces

			//- Return list of cut faces
		FoamDynamicMesh_EXPORT const faceList& cutFaces() const;

		//- Return cut face master list
		FoamDynamicMesh_EXPORT const labelList& cutFaceMaster() const;

		//- Return cut face slave list
		FoamDynamicMesh_EXPORT const labelList& cutFaceSlave() const;


		//- Check if the patch is fully supported
		FoamDynamicMesh_EXPORT bool checkSupport() const;


		//- Debugging: dump graphical representation to obj format file
		FoamDynamicMesh_EXPORT void writeOBJ(const fileName&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const enrichedPatch&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_enrichedPatch_Header
