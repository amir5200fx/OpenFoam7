#pragma once
#ifndef _surfaceInterpolate_Header
#define _surfaceInterpolate_Header

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
	tnbLib::functionObjects::surfaceInterpolate

Description
	Linearly interpolates volume fields to generate surface fields.

	Fields are stored
	- every time step the field is updated with new values
	- at output it writes the fields

	This functionObject can either be used
	- to calculate a new field as a  post-processing step or
	- since the fields are registered, used in another functionObject

	Example of function object specification:
	\verbatim
	surfaceInterpolate1
	{
		type        surfaceInterpolate;
		libs        ("libfieldFunctionObjects.so");
		...
		fields      ((p pNear)(U UNear));
	}
	\endverbatim

Usage
	\table
		Property | Description               | Required    | Default value
		type     | type name: nearWallFields | yes         |
		fields   | list of fields with corresponding output field names | yes |
	\endtable


See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::timeControl

SourceFiles
	surfaceInterpolate.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <surfaceFieldsFwd.hxx>
#include <Tuple2.hxx>

#include <PtrList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class objectRegistry;
	class dictionary;
	class mapPolyMesh;

	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
						  Class surfaceInterpolate Declaration
		\*---------------------------------------------------------------------------*/

		class surfaceInterpolate
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected data

				//- Fields to process
			List<Tuple2<word, word>> fieldSet_;

			//- Locally constructed fields
			PtrList<surfaceScalarField> ssf_;
			PtrList<surfaceVectorField> svf_;
			PtrList<surfaceSphericalTensorField> sSpheretf_;
			PtrList<surfaceSymmTensorField> sSymmtf_;
			PtrList<surfaceTensorField> stf_;


			// Protected Member Functions

			template<class Type>
			void interpolateFields
			(
				PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>>&
			) const;


		public:

			//- Runtime type information
			TypeName("surfaceInterpolate");


			// Constructors

				//- Construct for given objectRegistry and dictionary.
				//  Allow the possibility to load fields from files
			surfaceInterpolate
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			surfaceInterpolate(const surfaceInterpolate&) = delete;


			//- Destructor
			virtual ~surfaceInterpolate();


			// Member Functions

				//- Read the controls
			virtual bool read(const dictionary&);

			//- Calculate the interpolated fields
			virtual bool execute();

			//- Write the interpolated fields
			virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const surfaceInterpolate&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <surfaceInterpolateFunObjTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolate_Header
