#pragma once
#ifndef _fieldsExpression_Header
#define _fieldsExpression_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::fieldsExpression

Description

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	fieldsExpression.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class fieldsExpression Declaration
		\*---------------------------------------------------------------------------*/

		class fieldsExpression
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected member data

				//- Names of fields to process
			wordList fieldNames_;

			//- Name of result fields
			word resultName_;


			// Protected member functions

			FoamFunctionObjects_EXPORT void setResultName
			(
				const word& typeName,
				const wordList& defaultArg = wordList::null()
			);

			//- Call 'calcFieldType' for the given functionObject
			//  for 'volField' and 'surfaceField' field types
			template<class Type, class FOType>
			bool calcFieldTypes(FOType& fo);

			//- Call 'calcFieldTypes' for the given 'Type' and functionObject
			template<class Type, class FOType>
			bool calcType(FOType& fo);

			//- Call 'calcType' for the given functionObject
			//  for each primitive type
			template<class FOType>
			bool calcAllTypes(FOType& fo);

			FoamFunctionObjects_EXPORT virtual bool calc() = 0;


		public:

			//- Runtime type information
			//TypeName("fieldsExpression");
			static const char* typeName_() { return "fieldsExpression"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT fieldsExpression
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict,
				const wordList& fieldNames = wordList::null(),
				const word& resultName = word::null
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT fieldsExpression(const fieldsExpression&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~fieldsExpression();


			// Member Functions

				//- Read the fieldsExpression data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the result fields
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the result fields
			FoamFunctionObjects_EXPORT virtual bool write();

			//- Clear the result fields from the objectRegistry
			FoamFunctionObjects_EXPORT virtual bool clear();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const fieldsExpression&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <fieldsExpressionTemplates.cxx>
#endif

#include <fieldsExpressionTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldsExpression_Header
