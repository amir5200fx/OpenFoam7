#pragma once
#ifndef _wallHeatFlux_Header
#define _wallHeatFlux_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::wallHeatFlux

Description
	Calculates and write the heat-flux at wall patches as the
	volScalarField field 'wallHeatFlux'.

	All wall patches are included by default; to restrict the calculation to
	certain patches, use the optional 'patches' entry.

	Example of function object specification:
	\verbatim
	wallHeatFlux1
	{
		type        wallHeatFlux;
		libs        ("libfieldFunctionObjects.so");
		...
		region      fluid;
		patches     (".*Wall");
	}
	\endverbatim

Usage
	\table
		Property | Description                | Required   | Default value
		type     | type name: wallHeatFlux    | yes        |
		patches  | list of patches to process | no         | all wall patches
		region   | region to be evaluated     | no         | default region
	\endtable

Note
	Writing field 'wallHeatFlux' is done by default, but it can be overridden by
	defining an empty \c objects list. For details see writeLocalObjects.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::writeLocalObjects
	tnbLib::functionObjects::timeControl

SourceFiles
	wallHeatFlux.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <writeLocalObjects.hxx>
#include <HashSet.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class wallHeatFlux Declaration
		\*---------------------------------------------------------------------------*/

		class wallHeatFlux
			:
			public fvMeshFunctionObject,
			public logFiles,
			public writeLocalObjects
		{

		protected:

			// Protected data

				//- Optional list of patches to process
			labelHashSet patchSet_;


			// Protected Member Functions

				//- File header information
			FoamFunctionObjects_EXPORT virtual void writeFileHeader(const label i);

			//- Calculate the heat-flux
			FoamFunctionObjects_EXPORT tmp<volScalarField> calcWallHeatFlux
			(
				const volScalarField& alpha,
				const volScalarField& he
			);


		public:

			//- Runtime type information
			//TypeName("wallHeatFlux");
			static const char* typeName_() { return "wallHeatFlux"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT wallHeatFlux
			(
				const word& name,
				const Time& runTime,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT wallHeatFlux(const wallHeatFlux&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~wallHeatFlux();


			// Member Functions

				//- Read the wallHeatFlux data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the wall heat-flux
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the wall heat-flux
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const wallHeatFlux&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallHeatFlux_Header
