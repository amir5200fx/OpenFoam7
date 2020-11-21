#pragma once
#ifndef _fieldExpression_Header
#define _fieldExpression_Header

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
	tnbLib::functionObjects::fieldExpression

Description

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	fieldExpression.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class fieldExpression Declaration
		\*---------------------------------------------------------------------------*/

		class fieldExpression
			:
			public fvMeshFunctionObject
		{
		protected:

			// Protected member data

				//- Name of field to process
			word fieldName_;

			//- Name of result field
			word resultName_;


			// Protected member functions

			FoamFunctionObjects_EXPORT virtual bool calc() = 0;

			FoamFunctionObjects_EXPORT void setResultName(const word& typeName, const word& defaultArg);

			template<class Type>
			bool foundObject(const word& name);


		public:

			//- Runtime type information
			//TypeName("fieldExpression");
			static const char* typeName_() { return "fieldExpression"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT fieldExpression
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict,
				const word& fieldName = word::null,
				const word& resultName = word::null
			);

			//- Disallow default bitwise copy construction
			FoamFunctionObjects_EXPORT fieldExpression(const fieldExpression&) = delete;


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~fieldExpression();


			// Member Functions

				//- Read the fieldExpression data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Calculate the result field
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write the result field
			FoamFunctionObjects_EXPORT virtual bool write();

			//- Clear the result field from the objectRegistry
			FoamFunctionObjects_EXPORT virtual bool clear();


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFunctionObjects_EXPORT void operator=(const fieldExpression&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
//#include <fieldExpressionTemplates.cxx>
#endif

#include <fieldExpressionTemplates.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldExpression_Header
