#pragma once
#ifndef _volRegion_Header
#define _volRegion_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::functionObjects::volRegion

Description
	Volume (cell) region selection class.

	Examples of function object specification:
	\verbatim
	volRegion0
	{
		.
		.
		regionType      cellZone;
		name            c0;
		.
		.
	}

	volRegionAll
	{
		.
		.
		regionType      all;
		.
		.
	}
	\endverbatim

Usage
	\table
		Property     | Description                | Required     | Default value
		regionType   | cellZone or all              | no | all
		name         | Name of cellZone if required | no |
	\endtable

See also
	tnbLib::functionObject

SourceFiles
	volRegion.C

\*---------------------------------------------------------------------------*/

#include <writeFile.hxx>
#include <NamedEnum.hxx>
#include <typeInfo.hxx>  // added by amir
#include <labelList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class volRegion Declaration
		\*---------------------------------------------------------------------------*/

		class volRegion
		{
			// Private member data

			const fvMesh& mesh_;

			// Cache integral properties of the region for writeFileHeader
			label nCells_;
			scalar V_;


		public:

			// Public data types

				//- Region type enumeration
			enum regionTypes
			{
				vrtCellZone,
				vrtAll
			};

			//- Region type names
			static FoamFiniteVolume_EXPORT const NamedEnum<regionTypes, 2> regionTypeNames_;


		protected:

			// Protected data

				//- Region type
			regionTypes regionType_;

			//- Region name (patch, zone, etc.)
			word regionName_;

			//- Region ID (patch ID, zone ID, etc.)
			label regionID_;


			// Protected Member Functions

				//- Output file header information
			FoamFiniteVolume_EXPORT void writeFileHeader(const writeFile& wf, Ostream& file);


		public:

			//- Run-time type information
			/*TypeName("volRegion");*/
			static const char* typeName_() { return "volRegion"; }
			static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
			static FoamFiniteVolume_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from fvMesh and dictionary
			FoamFiniteVolume_EXPORT volRegion
			(
				const fvMesh& mesh,
				const dictionary& dict
			);


			//- Destructor
			FoamFiniteVolume_EXPORT virtual ~volRegion();


			// Public Member Functions

				//- Read from dictionary
			FoamFiniteVolume_EXPORT bool read(const dictionary&);

			//- Return the region type
			inline const regionTypes& regionType() const;

			//- Return the local list of cell IDs
			FoamFiniteVolume_EXPORT const labelList& cellIDs() const;

			//- Return the number of cells in the region
			FoamFiniteVolume_EXPORT label nCells() const;

			//- Return total volume of the region
			FoamFiniteVolume_EXPORT scalar V() const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <volRegionI.hxx>

#endif // !_volRegion_Header
