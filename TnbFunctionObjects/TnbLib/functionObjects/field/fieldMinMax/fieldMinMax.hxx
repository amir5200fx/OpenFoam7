#pragma once
#ifndef _fieldMinMax_Header
#define _fieldMinMax_Header

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
	tnbLib::functionObjects::fieldMinMax

Description
	Calculates the value and location of scalar minimum and maximum for a list
	of user-specified fields.

	For variables with a rank greater than zero, either the min/max of a
	component value or the magnitude is reported.  When operating in parallel,
	the processor owning the value is also given.

	Example of function object specification:
	\verbatim
	fieldMinMax1
	{
		type        fieldMinMax;
		libs        ("libfieldFunctionObjects.so");
		...
		write       yes;
		log         yes;
		location    yes;
		mode        magnitude;
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
		type         | type name: fieldMinMax  | yes         |
		write        | write min/max data to file |  no      | yes
		log          | write min/max data to standard output | no | no
		location     | write location of the min/max value | no | yes
		mode         | calculation mode: magnitude or component | no | magnitude
	\endtable

	Output data is written to the file \<timeDir\>/fieldMinMax.dat

See also
	tnbLib::functionObjects::fvMeshFunctionObject
	tnbLib::functionObjects::logFiles

SourceFiles
	fieldMinMax.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <logFiles.hxx>
#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
							   Class fieldMinMax Declaration
		\*---------------------------------------------------------------------------*/

		class fieldMinMax
			:
			public fvMeshFunctionObject,
			public logFiles
		{
		public:

			enum class modeType
			{
				mag,
				cmpt
			};

		protected:

			// Protected data

				//- Mode type names
			static FoamFunctionObjects_EXPORT const NamedEnum<modeType, 2> modeTypeNames_;

			//- Switch to write location of min/max values
			Switch location_;

			//- Mode for min/max - only applicable for ranks > 0
			modeType mode_;

			//- Fields to assess min/max
			wordList fieldSet_;


			// Protected Member Functions

				//- Helper function to write the output
			template<class Type>
			void output
			(
				const word& fieldName,
				const word& outputName,
				const label minCell,
				const label maxCell,
				const vector& minC,
				const vector& maxC,
				const label minProci,
				const label maxProci,
				const Type& minValue,
				const Type& maxValue
			);

			//- Calculate the field min/max
			template<class Type>
			void calcMinMaxFields
			(
				const word& fieldName,
				const modeType& mode
			);

			//- Output file header information
			FoamFunctionObjects_EXPORT virtual void writeFileHeader(const label i);


		public:

			//- Runtime type information
			//TypeName("fieldMinMax");
			static const char* typeName_() { return "fieldMinMax"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT fieldMinMax
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT fieldMinMax(const fieldMinMax&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~fieldMinMax();


			// Member Functions

				//- Read the field min/max data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute, currently does nothing
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the fieldMinMax
			FoamFunctionObjects_EXPORT virtual bool write();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const fieldMinMax&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <fieldMinMaxTemplates.cxx>
#endif

#include <fieldMinMaxTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldMinMax_Header
