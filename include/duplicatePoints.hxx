#pragma once
#ifndef _duplicatePoints_Header
#define _duplicatePoints_Header

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
	tnbLib::duplicatePoints

Description
	Duplicate points

SourceFiles
	duplicatePoints.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>
#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class polyTopoChange;
	class edge;
	class face;
	class mapPolyMesh;
	class localPointRegion;

	/*---------------------------------------------------------------------------*\
							   Class duplicatePoints Declaration
	\*---------------------------------------------------------------------------*/

	class duplicatePoints
	{
		// Private Data

			//- Reference to mesh
		const polyMesh& mesh_;

		//- Per regionSide.pointRegion() the points created.
		//  element 0 is the original point.
		//  Can have empty entries if a point only has one region.
		labelListList duplicates_;


	public:

		//- Runtime type information
		//ClassName("duplicatePoints");
		static const char* typeName_() { return "duplicatePoints"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;


		// Constructors

			//- Construct from mesh
		FoamDynamicMesh_EXPORT duplicatePoints(const polyMesh& mesh);

		//- Disallow default bitwise copy construction
		duplicatePoints(const duplicatePoints&) = delete;


		// Member Functions

			// Access

				//- Per point in regionSide.pointRegions() the points created.
		const labelListList& duplicates() const
		{
			return duplicates_;
		}


		// Topology changes

			//- Play commands into polyTopoChange to duplicate points. Gets
			//  localPointRegion structure which is per non-manifold point
			//  the regions per point.
		FoamDynamicMesh_EXPORT void setRefinement
		(
			const localPointRegion& regionSide,
			polyTopoChange&
		);

		//- Force recalculation of locally stored data on topological change
		FoamDynamicMesh_EXPORT void updateMesh(const mapPolyMesh&);


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const duplicatePoints&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_duplicatePoints_Header
