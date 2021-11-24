#pragma once
#ifndef _readFields_Header
#define _readFields_Header

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
	tnbLib::functionObjects::readFields

Description
	Reads fields from the time directories and adds them to the mesh database
	for further post-processing.

	Example of function object specification:
	\verbatim
	readFields1
	{
		type        readFields;
		libs        ("libfieldFunctionObjects.so");
		...
		fields
		(
			U
			p
		);
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required    | Default value
		type         | type name: readFields   | yes         |
		fields       | list of fields to read  |  no         |
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	readFields.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>

#include <PtrList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class readFields Declaration
		\*---------------------------------------------------------------------------*/

		class readFields
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected data

				//- Fields to load
			wordList fieldSet_;

			//- Loaded fields
			PtrList<volScalarField> vsf_;
			PtrList<volVectorField> vvf_;
			PtrList<volSphericalTensorField> vSpheretf_;
			PtrList<volSymmTensorField> vSymmtf_;
			PtrList<volTensorField> vtf_;

			PtrList<surfaceScalarField> ssf_;
			PtrList<surfaceVectorField> svf_;
			PtrList<surfaceSphericalTensorField> sSpheretf_;
			PtrList<surfaceSymmTensorField> sSymmtf_;
			PtrList<surfaceTensorField> stf_;


			// Protected Member Functions

			template<class Type>
			void loadField
			(
				const word&,
				PtrList<GeometricField<Type, fvPatchField, volMesh>>&,
				PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>>&
			) const;


		public:

			//- Runtime type information
			//TypeName("readFields");
			static const char* typeName_() { return "readFields"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct for given objectRegistry and dictionary.
				//  Allow the possibility to load fields from files
			FoamFunctionObjects_EXPORT readFields
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT readFields(const readFields&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~readFields();


			// Member Functions

				//- Read the set of fields from dictionary
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Read the fields
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Do nothing
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const readFields&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <readFieldsI.hxx>

#ifdef NoRepository
//#include <readFieldsTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_readFields_Header
