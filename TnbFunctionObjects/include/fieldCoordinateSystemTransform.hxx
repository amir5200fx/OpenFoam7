#pragma once
#ifndef _fieldCoordinateSystemTransform_Header
#define _fieldCoordinateSystemTransform_Header

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
	tnbLib::functionObjects::fieldCoordinateSystemTransform

Description
	Transforms a user-specified selection of fields from global Cartesian
	co-ordinates to a local co-ordinate system.  The fields are run-time
	modifiable.

	Example of function object specification:
	\verbatim
	fieldCoordinateSystemTransform1
	{
		type        fieldCoordinateSystemTransform;
		libs        ("libfieldFunctionObjects.so");
		...
		fields
		(
			U
			UMean
			UPrime2Mean
		);

		coordinateSystem
		{
			origin  (0.001 0 0);
			coordinateRotation
			{
				type        axesRotation;
				e1      (1      0.15    0);
				e3      (0      0      -1);
			}
		}
	}
	\endverbatim

Usage
	\table
		Property     | Description             | Required    | Default value
		type         | type name: fieldCoordinateSystemTransform | yes |
		fields       | list of fields to be transformed |yes |
		coordinateSystem | local co-ordinate system | yes    |
	\endtable

See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::coordinateSystem

SourceFiles
	fieldCoordinateSystemTransform.C
	fieldCoordinateSystemTransformTemplates.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <coordinateSystem.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
					   Class fieldCoordinateSystemTransform Declaration
		\*---------------------------------------------------------------------------*/

		class fieldCoordinateSystemTransform
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected data

				//- Fields to transform
			wordList fieldSet_;

			//- Co-ordinate system to transform to
			coordinateSystem coordSys_;


			// Protected Member Functions

				//- Return the name of the transformed field
			word transformFieldName(const word& fieldName) const;

			//- Transform the given field
			template<class FieldType>
			void transformField(const FieldType& field);

			//- Transform the given field if has the specified element type
			template<class Type>
			void transform(const word& fieldName);


		public:

			//- Runtime type information
			TypeName("fieldCoordinateSystemTransform");


			// Constructors

				//- Construct from Time and dictionary
			fieldCoordinateSystemTransform
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			virtual ~fieldCoordinateSystemTransform();


			// Member Functions

				//- Read the input data
			virtual bool read(const dictionary&);

			//- Calculate the transformed fields
			virtual bool execute();

			//- Write the transformed fields
			virtual bool write();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <fieldCoordinateSystemTransformTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldCoordinateSystemTransform_Header
