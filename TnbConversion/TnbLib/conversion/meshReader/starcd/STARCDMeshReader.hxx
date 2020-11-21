#pragma once
#ifndef _STARCDMeshReader_Header
#define _STARCDMeshReader_Header

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
	tnbLib::meshReaders::STARCD

Description
	Read pro-STAR vrt/cel/bnd files.
	The protected data in meshReader are filled.

	Starting with pro-STAR version 4, the files have become easier to read.
	- vertices are space-delimited.
	- the cell format is logical.
	- trimmed and degenerate cells are saved as polyhedral.
	- the boundaries corresponds to cells and their faces.

SourceFiles
	STARCDMeshReader.C

\*---------------------------------------------------------------------------*/

#include <meshReader.hxx>
#include <boundaryRegion.hxx>
#include <cellShape.hxx>
#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace meshReaders
	{

		/*---------------------------------------------------------------------------*\
							Class meshReaders::STARCD Declaration
		\*---------------------------------------------------------------------------*/

		class STARCD
			:
			public meshReader
		{

		protected:

			// Protected Data

			static FoamConversion_EXPORT const char* const defaultBoundaryName;
			static FoamConversion_EXPORT const char* const defaultSolidBoundaryName;

			//- Face addressing from pro-STAR faces -> OpenFOAM faces
			static FoamConversion_EXPORT const int starToFoamFaceAddr[4][6];

			//- Cell shapes
			cellShapeList cellShapes_;

			//- Point labels (imported Point numbering not necessarily contiguous)
			labelList mapToFoamPointId_;

			//- Cell labels (imported Cell numbering not necessarily contiguous)
			labelList mapToFoamCellId_;

			//- Boundary region data
			boundaryRegion boundaryRegion_;


			// Protected Member Functions

				//- Read the mesh from the file(s)
			FoamConversion_EXPORT virtual bool readGeometry(const scalar scaleFactor = 1.0);

			//- Read points from file
			FoamConversion_EXPORT void readPoints(const fileName&, const scalar scaleFactor);

			//- Read cell connectivities from file
			FoamConversion_EXPORT virtual void readCells(const fileName&);

			//- Remove unused points
			FoamConversion_EXPORT void cullPoints();

			//- Read boundary (cell/face) definitions
			FoamConversion_EXPORT void readBoundary(const fileName&);

			//- Read auxiliary data from constant/{boundaryRegion,cellTable}
			FoamConversion_EXPORT void readAux(const objectRegistry&);

			//- Read and discard to newline
			static FoamConversion_EXPORT void readToNewline(IFstream&);

			//- Read header
			static FoamConversion_EXPORT bool readHeader(IFstream&, word fileSignature);


		protected:

			enum cellType
			{
				starcdFluidType = 1,
				starcdSolidType = 2,
				starcdBaffleType = 3,
				starcdShellType = 4,
				starcdLineType = 5,
				starcdPointType = 6
			};

			enum shapeType
			{
				starcdPoint = 1,
				starcdLine = 2,
				starcdShell = 3,
				starcdHex = 11,
				starcdPrism = 12,
				starcdTet = 13,
				starcdPyr = 14,
				starcdPoly = 255
			};


		public:

			// Static data

				//- Keep solids (default false)
			static FoamConversion_EXPORT bool keepSolids;


			// Constructors

				//- Construct from case name
			FoamConversion_EXPORT STARCD
			(
				const fileName& prefix,
				const objectRegistry&,
				const scalar scaleFactor = 1.0
			);

			//- Disallow default bitwise copy construction
			FoamConversion_EXPORT STARCD(const STARCD&) = delete;


			//- Destructor
			FoamConversion_EXPORT virtual ~STARCD();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamConversion_EXPORT void operator=(const STARCD&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace meshReaders
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDMeshReader_Header
