#pragma once
#ifndef _wallShearStress_Header
#define _wallShearStress_Header

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
	tnbLib::functionObjects::wallShearStress

Description
	Calculates and write the shear-stress at wall patches as
	the volVectorField field 'wallShearStress'.

		\f[
			Stress = R \dot n
		\f]

	where
	\vartable
		R       | stress tensor
		n       | patch normal vector (into the domain)
	\endvartable

	The shear-stress symmetric tensor field is retrieved from the turbulence
	model.  All wall patches are included by default; to restrict the
	calculation to certain patches, use the optional 'patches' entry.

	Example of function object specification:
	\verbatim
	wallShearStress1
	{
		type        wallShearStress;
		libs        ("libfieldFunctionObjects.so");
		...
		patches     (".*Wall");
	}
	\endverbatim

Usage
	\table
		Property | Description               | Required    | Default value
		type     | type name: wallShearStress | yes        |
		patches  | list of patches to process | no         | all wall patches
	\endtable

Note
	Writing field 'wallShearStress' is done by default, but it can be overridden
	by defining an empty \c objects list. For details see writeLocalObjects.

See also
	tnbLib::functionObject
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles
	tnbLib::functionObjects::writeLocalObjects
	tnbLib::functionObjects::timeControl

SourceFiles
	wallShearStress.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <writeLocalObjects.hxx>
#include <volFieldsFwd.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class wallShearStress Declaration
		\*---------------------------------------------------------------------------*/

		class wallShearStress
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

			//- Calculate the shear-stress
			FoamFunctionObjects_EXPORT tmp<volVectorField> calcShearStress
			(
				const volSymmTensorField& Reff
			);


		public:

			//- Runtime type information
			//TypeName("wallShearStress");
			static const char* typeName_() { return "wallShearStress"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT wallShearStress
			(
				const word& name,
				const Time& runTime,
				const dictionary&
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT wallShearStress(const wallShearStress&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~wallShearStress();


			// Member Functions

				//- Read the wallShearStress data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the wall shear-stress
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the wall shear-stress
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const wallShearStress&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallShearStress_Header
