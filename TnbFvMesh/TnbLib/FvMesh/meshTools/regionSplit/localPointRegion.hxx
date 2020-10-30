#pragma once
#ifndef _localPointRegion_Header
#define _localPointRegion_Header

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
	tnbLib::localPointRegion

Description
	Takes mesh with 'baffles' (= boundary faces sharing points).
	Determines for selected points on boundary faces the 'point region' it is
	connected to. Each region can be visited by a cell-face-cell walk.
	Used in duplicating points after splitting baffles.

	Regions are not consecutive per processor. They will be -1..nRegions_.

	Note: coupled boundaries (cyclics, parallel) not fully tested.

SourceFiles
	localPointRegion.C

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>
#include <Map.hxx>
#include <labelList.hxx>
#include <HashSet.hxx>
#include <faceList.hxx>
#include <boolList.hxx>
#include <labelPair.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class primitiveMesh;
	class polyMesh;
	class face;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
							   Class localPointRegion Declaration
	\*---------------------------------------------------------------------------*/

	class localPointRegion
	{
		// Private Data

			////- (global) number of regions
			// label nRegions_;

			//- Per point that is to duplicated to the local index
		Map<label> meshPointMap_;

		//- Per local point the regions it is in
		labelListList pointRegions_;

		//- Per face that uses a duplicated point the local index
		Map<label> meshFaceMap_;

		//- Per face the region of its points
		faceList faceRegions_;


		// Private Member Functions

			//- Given minimum cell the points on a face are connected to
			//  determine the points to be duplicated.
		FoamFvMesh_EXPORT void countPointRegions
		(
			const polyMesh& mesh,
			const boolList& candidatePoint,
			const Map<label>& candidateFace,
			faceList& minRegion
		);

		//- Do all: calculate points that need to be duplicated.
		FoamFvMesh_EXPORT void calcPointRegions
		(
			const polyMesh& mesh,
			boolList& candidatePoint
		);


		//- Check if two faces are equal. If forward = false checks f1 in
		//  reverse order.
		static FoamFvMesh_EXPORT bool isDuplicate
		(
			const face& f0,
			const face& f1,
			const bool forward
		);

	public:

		//- Runtime type information
		/*ClassName("localPointRegion");*/
		static const char* typeName_() { return "localPointRegion"; } 
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName; 
		static FoamFvMesh_EXPORT int debug;


		// Constructors

			//- Construct from mesh. Assumes all non-coupled boundary points
			//  are candidates for duplication
		FoamFvMesh_EXPORT localPointRegion(const polyMesh& mesh);

		//- Construct from mesh and candidate points for duplication
		FoamFvMesh_EXPORT localPointRegion
		(
			const polyMesh& mesh,
			const labelList& candidatePoints
		);


		// Member Functions

			// Static Member Functions

				//- Helper routine to find baffles (two boundary faces using the
				//  same points but in reverse order)
				//  Gets list of (boundary!) faces to check. Returns labelList
				//  of same size as the input list
				//  with -1 or index of other face in the input list.
				//  Does not handle duplicate faces on both sides of processor patch
		static FoamFvMesh_EXPORT labelList findDuplicateFaces
		(
			const primitiveMesh&,
			const labelList&
		);

		//- Helper routine to find all baffles (two boundary faces
		//  using the same points but in reverse order)
		static FoamFvMesh_EXPORT labelPairList findDuplicateFacePairs(const polyMesh&);

		// Access

			////- Global number of regions. TBD. regions not compacted yet.
			// label nRegions() const
			//{
			//    return nRegions_;
			//}

			//- Per point that is to be duplicated the local index
		const Map<label>& meshPointMap() const
		{
			return meshPointMap_;
		}

		//- Per local point the regions it is in
		const labelListList& pointRegions() const
		{
			return pointRegions_;
		}

		//- Per face that uses a duplicated point the local index
		const Map<label>& meshFaceMap() const
		{
			return meshFaceMap_;
		}

		//- Per face the region of its points
		const faceList& faceRegions() const
		{
			return faceRegions_;
		}


		// Edit

			//- Force recalculation of locally stored data on topological change
		FoamFvMesh_EXPORT void updateMesh(const mapPolyMesh&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_localPointRegion_Header
