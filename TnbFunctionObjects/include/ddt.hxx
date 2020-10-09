#pragma once
#ifndef _ddt_Header
#define _ddt_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
	tnbLib::functionObjects::ddt

Description
	Calculates the Eulerian time derivative of a field.

	The operation can be applied to any volume field generating a field of the
	same type.

See also
	tnbLib::functionObjects::fvMeshFunctionObject

SourceFiles
	ddt.C

\*---------------------------------------------------------------------------*/

#include <fieldExpression.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
								 Class ddt Declaration
		\*---------------------------------------------------------------------------*/

		class ddt
			:
			public fieldExpression
		{
			// Private Member Functions

				//- Calculate the magnitude of the field and register the result
			template<class Type>
			bool calcDdt();

			//- Calculate the time derivative of the field and return
			//  true if successful
			virtual bool calc();


		public:

			//- Runtime type information
			TypeName("ddt");


			// Constructors

				//- Construct from Time and dictionary
			ddt
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			virtual ~ddt();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <ddtTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ddt_Header
