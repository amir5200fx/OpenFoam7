#pragma once
#ifndef _partialFaceAreaWeightAMI_Header
#define _partialFaceAreaWeightAMI_Header

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
	tnbLib::partialFaceAreaWeightAMI

Description
	Partial face area weighted Arbitrary Mesh Interface (AMI) method

SourceFiles
	partialFaceAreaWeightAMI.C

\*---------------------------------------------------------------------------*/

#include <faceAreaWeightAMI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class partialFaceAreaWeightAMI Declaration
	\*---------------------------------------------------------------------------*/

	class partialFaceAreaWeightAMI
		:
		public faceAreaWeightAMI
	{
		// Private Member Functions

			// Marching front

				//- Set the source and target seed faces
		FoamFvMesh_EXPORT virtual void setNextFaces
		(
			label& startSeedI,
			label& srcFacei,
			label& tgtFacei,
			const boolList& mapFlag,
			labelList& seedFaces,
			const DynamicList<label>& visitedFaces,
			bool errorOnNotFound = true
		) const;


	public:

		//- Runtime type information
		//TypeName("partialFaceAreaWeightAMI");
		static const char* typeName_() { return "partialFaceAreaWeightAMI"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		FoamFvMesh_EXPORT partialFaceAreaWeightAMI
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
		FoamFvMesh_EXPORT partialFaceAreaWeightAMI(const partialFaceAreaWeightAMI&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~partialFaceAreaWeightAMI();


		// Member Functions

			// Access

				//- Flag to indicate that interpolation patches are conformal
		FoamFvMesh_EXPORT virtual bool conformal() const;


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
		FoamFvMesh_EXPORT void operator=(const partialFaceAreaWeightAMI&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_partialFaceAreaWeightAMI_Header
