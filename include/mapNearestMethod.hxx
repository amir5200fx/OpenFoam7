#pragma once
#ifndef _mapNearestMethod_Header
#define _mapNearestMethod_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::mapNearestMethod

Description
	Map nearest mesh-to-mesh interpolation class

	Not volume conservative.
	- cells outside other meshes bounding box do not get mapped
	  (initial filtering)
	- all remaining cells will be mapped (with weight 1!)
	- so take care when mapping meshes with different bounding boxes!

SourceFiles
	mapNearestMethod.C

\*---------------------------------------------------------------------------*/

#include <meshToMeshMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class mapNearestMethod Declaration
	\*---------------------------------------------------------------------------*/

	class mapNearestMethod
		:
		public meshToMeshMethod
	{
	protected:

		// Protected Member Functions

			//- Find indices of overlapping cells in src and tgt meshes - returns
			//  true if found a matching pair
		FoamSampling_EXPORT virtual bool findInitialSeeds
		(
			const labelList& srcCellIDs,
			const boolList& mapFlag,
			const label startSeedI,
			label& srcSeedI,
			label& tgtSeedI
		) const;

		//- Calculate the mesh-to-mesh addressing and weights
		FoamSampling_EXPORT virtual void calculateAddressing
		(
			labelListList& srcToTgtCellAddr,
			scalarListList& srcToTgtCellWght,
			labelListList& tgtToSrcCellAddr,
			scalarListList& tgtToSrcCellWght,
			const label srcSeedI,
			const label tgtSeedI,
			const labelList& srcCellIDs,
			boolList& mapFlag,
			label& startSeedI
		);

		//- Find the nearest cell on mesh2 for cell1 on mesh1
		FoamSampling_EXPORT virtual void findNearestCell
		(
			const polyMesh& mesh1,
			const polyMesh& mesh2,
			const label cell1,
			label& cell2
		) const;

		//- Set the next cells for the marching front algorithm
		FoamSampling_EXPORT virtual void setNextNearestCells
		(
			label& startSeedI,
			label& srcCelli,
			label& tgtCelli,
			boolList& mapFlag,
			const labelList& srcCellIDs
		) const;

		//- Find a source cell mapped to target cell tgtCelli
		FoamSampling_EXPORT virtual label findMappedSrcCell
		(
			const label tgtCelli,
			const List<DynamicList<label>>& tgtToSrc
		) const;


	public:

		//- Run-time type information
		//TypeName("mapNearest");
		static const char* typeName_() { return "mapNearest"; }
		static FoamSampling_EXPORT const ::tnbLib::word typeName;
		static FoamSampling_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Construct from source and target meshes
		FoamSampling_EXPORT mapNearestMethod(const polyMesh& src, const polyMesh& tgt);

		//- Disallow default bitwise copy construction
		FoamSampling_EXPORT mapNearestMethod(const mapNearestMethod&) = delete;


		//- Destructor
		FoamSampling_EXPORT virtual ~mapNearestMethod();


		// Member Functions

			// Evaluate

				//- Calculate addressing and weights
		FoamSampling_EXPORT virtual void calculate
		(
			labelListList& srcToTgtAddr,
			scalarListList& srcToTgtWght,
			labelListList& tgtToTgtAddr,
			scalarListList& tgtToTgtWght
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamSampling_EXPORT void operator=(const mapNearestMethod&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mapNearestMethod_Header
