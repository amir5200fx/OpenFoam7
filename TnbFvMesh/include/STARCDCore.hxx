#pragma once
#ifndef _STARCDCore_Header
#define _STARCDCore_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::fileFormats::STARCDCore

Description
	Core routines used when reading/writing pro-STAR vrt/cel/bnd files.

SourceFiles
	STARCDCore.C

\*---------------------------------------------------------------------------*/

#include <IFstream.hxx>
#include <pointField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
						   Class fileFormats::STARCDCore Declaration
		\*---------------------------------------------------------------------------*/

		class STARCDCore
		{
		protected:

			// Protected Member Functions

				//- Read header
			static FoamFvMesh_EXPORT bool readHeader(IFstream&, const word& fileSignature);

			//- Write header for fileType (CELL|VERTEX|BOUNDARY)
			static FoamFvMesh_EXPORT void writeHeader(Ostream&, const word& fileType);


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

			// Public Member Functions

				//- Read points from a (.vrt) file
				// The file format is as follows:
				// \verbatim
				// Line 1:
				//   PROSTAR_VERTEX  newline
				//
				// Line 2:
				//   {version} 0 0 0 0 0 0 0  newline
				//
				// Body:
				//   {vertexId}  {x}  {y}  {z}  newline
				// \endverbatim
			static FoamFvMesh_EXPORT bool readPoints(IFstream&, pointField&, labelList& ids);

			//- Write header and points to (.vrt) file
			static FoamFvMesh_EXPORT void writePoints(Ostream&, const pointField&);


			// Constructors

				//- Construct null
			FoamFvMesh_EXPORT STARCDCore();

		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDCore_Header
