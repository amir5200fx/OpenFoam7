#pragma once
#ifndef _nearWallFields_Header
#define _nearWallFields_Header

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
	tnbLib::functionObjects::nearWallFields

Description
	Samples near-patch volume fields.

	Fields are stored
	- every time step the field is updated with new values
	- at output it writes the fields

	This functionObject can either be used
	- to calculate a new field as a  post-processing step or
	- since the fields are registered, used in another functionObject

	Example of function object specification:
	\verbatim
	nearWallFields1
	{
		type        nearWallFields;
		libs        ("libfieldFunctionObjects.so");

		writeControl writeTime;

		fields
		(
			(p pNear)
			(U UNear)
		);

		patches     (movingWall);

		distance    0.13;
	}
	\endverbatim

Usage
	\table
		Property | Description               | Required    | Default value
		type     | type name: nearWallFields | yes         |
		fields   | list of fields with corresponding output field names | yes |
		patches  | list of patches to sample | yes         |
		distance | distance from patch to sample | yes     |
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	nearWallFields.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFields.hxx>
#include <Tuple2.hxx>
#include <interpolationCellPoint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class nearWallFields Declaration
		\*---------------------------------------------------------------------------*/

		class nearWallFields
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected member data

				// Read from dictionary

					//- Fields to process
			List<Tuple2<word, word>> fieldSet_;

			//- Patches to sample
			labelHashSet patchSet_;

			//- Distance away from wall
			scalar distance_;

			//- From original field to sampled result
			HashTable<word> fieldMap_;

			//- From resulting back to original field
			HashTable<word> reverseFieldMap_;


			// Calculated addressing

				//- From cell to seed patch faces
			labelListList cellToWalls_;

			//- From cell to tracked end point
			List<List<point>> cellToSamples_;

			//- Map from cell based data back to patch based data
			autoPtr<mapDistribute> getPatchDataMapPtr_;


			// Locally constructed fields

			PtrList<volScalarField> vsf_;
			PtrList<volVectorField> vvf_;
			PtrList<volSphericalTensorField> vSpheretf_;
			PtrList<volSymmTensorField> vSymmtf_;
			PtrList<volTensorField> vtf_;


			// Protected Member Functions

				//- Calculate addressing from cells back to patch faces
			FoamFunctionObjects_EXPORT void calcAddressing();

			template<class Type>
			void createFields
			(
				PtrList<GeometricField<Type, fvPatchField, volMesh>>&
			) const;

			//- Override boundary fields with sampled values
			template<class Type>
			void sampleBoundaryField
			(
				const interpolationCellPoint<Type>& interpolator,
				GeometricField<Type, fvPatchField, volMesh>& fld
			) const;

			template<class Type>
			void sampleFields
			(
				PtrList<GeometricField<Type, fvPatchField, volMesh>>&
			) const;


		public:

			//- Runtime type information
			//TypeName("nearWallFields");
			static const char* typeName_() { return "nearWallFields"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct for given objectRegistry and dictionary.
				//  Allow the possibility to load fields from files
			FoamFunctionObjects_EXPORT nearWallFields
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT nearWallFields(const nearWallFields&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~nearWallFields();


			// Member Functions

				//- Read the controls
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the near-wall fields
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the near-wall fields
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const nearWallFields&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <nearWallFieldsTemplates.cxx>
#endif

#include <nearWallFieldsTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_nearWallFields_Header
