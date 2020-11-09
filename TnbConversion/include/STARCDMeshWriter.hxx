#pragma once
#ifndef _STARCDMeshWriter_Header
#define _STARCDMeshWriter_Header

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
	tnbLib::meshWriters::STARCD

Description
	Writes polyMesh in pro-STAR (v4) bnd/cel/vrt format

	The cellTableId and cellTable information are used (if available).
	Otherwise the cellZones are used (if available).

SourceFiles
	STARCDMeshWriter.C

\*---------------------------------------------------------------------------*/

#include <meshWriter.hxx>
#include <IOstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace meshWriters
	{

		/*---------------------------------------------------------------------------*\
							Class meshWriters::STARCD Declaration
		\*---------------------------------------------------------------------------*/

		class STARCD
			:
			public meshWriter
		{
			// Private Data

			static FoamConversion_EXPORT const char* defaultBoundaryName;


			// Private Member Functions

				//- Pro-STAR 4+ header format
			static FoamConversion_EXPORT void writeHeader(Ostream&, const char* filetype);

			//- Write points
			FoamConversion_EXPORT void writePoints(const fileName& baseName) const;

			//- Write cells
			FoamConversion_EXPORT void writeCells(const fileName& baseName) const;

			//- Write boundary
			FoamConversion_EXPORT void writeBoundary(const fileName& baseName) const;

			FoamConversion_EXPORT void getCellTable();

			FoamConversion_EXPORT label findDefaultBoundary() const;


		public:

			// Static Data Members

				//- Face addressing from OpenFOAM faces -> pro-STAR faces
			static FoamConversion_EXPORT const label foamToStarFaceAddr[4][6];


			// Constructors

				//- Open a file for writing
			FoamConversion_EXPORT STARCD
			(
				const polyMesh&,
				const scalar scaleFactor = 1.0
			);

			//- Disallow default bitwise copy construction
			FoamConversion_EXPORT STARCD(const STARCD&) = delete;


			//- Destructor
			FoamConversion_EXPORT virtual ~STARCD();


			// Member Functions

				// Edit

					//- Remove STAR-CD files for the baseName
			FoamConversion_EXPORT void rmFiles(const fileName& baseName) const;


			// Write

				//- Write volume mesh
			FoamConversion_EXPORT virtual bool write
			(
				const fileName& meshName = fileName::null
			) const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamConversion_EXPORT void operator=(const STARCD&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace meshWriters
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDMeshWriter_Header
