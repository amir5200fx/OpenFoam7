#pragma once
#ifndef _mapNearestAMI_Header
#define _mapNearestAMI_Header

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
	tnbLib::mapNearestAMI

Description
	Nearest-mapping Arbitrary Mesh Interface (AMI) method

SourceFiles
	mapNearestAMI.C

\*---------------------------------------------------------------------------*/

#include <AMIMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class mapNearestAMI Declaration
	\*---------------------------------------------------------------------------*/

	class mapNearestAMI
		:
		public AMIMethod
	{
		// Private Member Functions

			// Marching front

				//- Find nearest target face for source face srcFacei
		FoamFvMesh_EXPORT void findNearestFace
		(
			const primitivePatch& srcPatch,
			const primitivePatch& tgtPatch,
			const label& srcFacei,
			label& tgtFacei
		) const;

		//- Determine next source-target face pair
		FoamFvMesh_EXPORT void setNextNearestFaces
		(
			boolList& mapFlag,
			label& startSeedI,
			label& srcFacei,
			label& tgtFacei
		) const;

		//- Find mapped source face
		FoamFvMesh_EXPORT label findMappedSrcFace
		(
			const label tgtFacei,
			const List<DynamicList<label>>& tgtToSrc
		) const;


		// Evaluation

			//- Area of intersection between source and target faces
		FoamFvMesh_EXPORT scalar interArea
		(
			const label srcFacei,
			const label tgtFacei
		) const;


	public:

		//- Runtime type information
		//TypeName("mapNearestAMI");
		static const char* typeName_() { return "mapNearestAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT mapNearestAMI
		(
			const primitivePatch& srcPatch,
			const primitivePatch& tgtPatch,
			const scalarField& srcMagSf,
			const scalarField& tgtMagSf,
			const faceAreaIntersect::triangulationMode& triMode,
			const bool reverseTarget = false,
			const bool requireMatch = true
		);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT mapNearestAMI(const mapNearestAMI&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~mapNearestAMI();


		// Member Functions

			// Manipulation

				//- Update addressing and weights
		FoamFvMesh_EXPORT virtual void calculate
		(
			labelListList& srcAddress,
			scalarListList& srcWeights,
			labelListList& tgtAddress,
			scalarListList& tgtWeights,
			label srcFacei = -1,
			label tgtFacei = -1
		);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const mapNearestAMI&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_mapNearestAMI_Header
