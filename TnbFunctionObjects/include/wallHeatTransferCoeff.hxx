#pragma once
#ifndef _wallHeatTransferCoeff_Header
#define _wallHeatTransferCoeff_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::wallHeatTransferCoeff

Description
	Calculates and write the estimated incompressible flow heat transfer
	coefficient at wall patches as the volScalarField field
	'wallHeatTransferCoeff'.

	All wall patches are included by default; to restrict the calculation to
	certain patches, use the optional 'patches' entry.

	Example of function object specification:
	\verbatim
	wallHeatTransferCoeff1
	{
		type        wallHeatTransferCoeff;
		libs        ("libfieldFunctionObjects.so");
		...
		region      fluid;
		patches     (".*Wall");
		rho         1.225;
		Cp          1005;
		Prl         0.707;
		Prt         0.9;
	}
	\endverbatim

Usage
	\table
		Property | Description                   | Required | Default value
		type     | Type name: wallHeatTransferCoeff | yes   |
		patches  | List of patches to process    | no       | all wall patches
		region   | Region to be evaluated        | no       | default region
		rho      | Fluid density                 | yes      |
		Cp       | Fluid heat capacity           | yes      |
		Prl      | Fluid laminar Prandtl number  | yes      |
		Prt      | Fluid turbulent Prandtl number| yes      |
	\endtable

Note
	Writing field 'wallHeatTransferCoeff' is done by default, but it can be
	overridden by defining an empty \c objects list. For details see
	writeLocalObjects.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::writeLocalObjects
	tnbLib::functionObjects::timeControl

SourceFiles
	wallHeatTransferCoeff.C

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
							   Class wallHeatTransferCoeff Declaration
		\*---------------------------------------------------------------------------*/

		class wallHeatTransferCoeff
			:
			public fvMeshFunctionObject,
			public logFiles,
			public writeLocalObjects
		{

		protected:

			// Protected data

				//- Optional list of patches to process
			labelHashSet patchSet_;

			//- Fluid density
			scalar rho_;

			//- Fluid heat capacity
			scalar Cp_;

			//- Fluid laminar Prandtl number
			scalar Prl_;

			//- Fluid turbulent Prandtl number
			scalar Prt_;


			// Protected Member Functions

				//- File header information
			FoamFunctionObjects_EXPORT virtual void writeFileHeader(const label i);

			//- Calculate the heat transfer coefficient
			FoamFunctionObjects_EXPORT tmp<volScalarField> calcHeatTransferCoeff
			(
				const volScalarField& nu,
				const volScalarField& nut
			);


		public:

			//- Runtime type information
			//TypeName("wallHeatTransferCoeff");
			static const char* typeName_() { return "wallHeatTransferCoeff"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT wallHeatTransferCoeff
			(
				const word& name,
				const Time& runTime,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT wallHeatTransferCoeff(const wallHeatTransferCoeff&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~wallHeatTransferCoeff();


			// Member Functions

				//- Read the wallHeatTransferCoeff data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the wall heat transfer coefficient
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the wall heat transfer coefficient
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const wallHeatTransferCoeff&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallHeatTransferCoeff_Header
