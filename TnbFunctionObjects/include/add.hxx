#pragma once
#ifndef _add_Header
#define _add_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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
	tnbLib::functionObjects::add

Description
	Add a list of fields.

	The operation can be applied to any volume or surface fields generating a
	volume or surface scalar field.

	Example of function object specification:
	\verbatim
	Ttot
	{
		type            add;
		libs            ("libfieldFunctionObjects.so");
		fields          (T Tdelta);
		result          Ttot;
		executeControl  writeTime;
		writeControl    writeTime;
	}
	\endverbatim

See also
	tnbLib::functionObjects::fieldsExpression
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	add.C

\*---------------------------------------------------------------------------*/

#include <fieldsExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								   Class add Declaration
		\*---------------------------------------------------------------------------*/

		class add
			:
			public fieldsExpression
		{
			// Private Member Functions

				//- Add the list of fields of the specified type
				//  and return the result
			template<class GeoFieldType>
			tmp<GeoFieldType> calcFieldType() const;

			//- Add the list of fields and return true if successful
			virtual bool calc();


		public:

			friend class fieldsExpression;


			//- Runtime type information
			TypeName("add");


			// Constructors

				//- Construct from Time and dictionary
			add
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			virtual ~add();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <addTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_add_Header
