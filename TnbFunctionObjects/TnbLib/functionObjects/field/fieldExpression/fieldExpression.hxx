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

			virtual bool calc() = 0;

			void setResultName(const word& typeName, const word& defaultArg);

			template<class Type>
			bool foundObject(const word& name);


		public:

			//- Runtime type information
			TypeName("fieldExpression");


			// Constructors

				//- Construct from Time and dictionary
			fieldExpression
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict,
				const word& fieldName = word::null,
				const word& resultName = word::null
			);

			//- Disallow default bitwise copy construction
			fieldExpression(const fieldExpression&) = delete;


			//- Destructor
			virtual ~fieldExpression();


			// Member Functions

				//- Read the fieldExpression data
			virtual bool read(const dictionary&);

			//- Calculate the result field
			virtual bool execute();

			//- Write the result field
			virtual bool write();

			//- Clear the result field from the objectRegistry
			virtual bool clear();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const fieldExpression&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <fieldExpressionTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fieldExpression_Header
