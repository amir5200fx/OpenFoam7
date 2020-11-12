#pragma once
#ifndef _age_Header
#define _age_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::functionObjects::age

Description
	Calculates and writes out the time taken for a particle to travel from an
	inlet to the location. Solves the following equation when incompressible:
	\f[
		\div (\phi t) = 1
	\f]
	where:
	\vartable
		t    | Age [s]
		\phi | Volumetric flux [m^3/s]
	\endvartable
	Boundary conditions are generated automatically as zeroGradient on all
	walls and inletOutlet everywhere else.

Usage
	\table
		Property | Description                   | Required | Default value
		phi      | The name of the flux field    | no       | phi
		rho      | The name of the density field | no       | rho
		nCorr    | The number of correctors      | no       | 0
		schemesField | The name of the field from which schemes are taken | \\
		no | age
	\endtable

	\verbatim
	age1
	{
		type            age;
		libs            ("libsolverFunctionObjects.so");

		writeControl    writeTime;
		writeInterval   1;

		phi             phi;
		rho             rho;
		nCorr           10;
		schemesField    k;
	}
	\endverbatim

SourceFiles
	age.C

\*---------------------------------------------------------------------------*/

#include <fvMeshFunctionObject.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{

		/*---------------------------------------------------------------------------*\
									   Class age Declaration
		\*---------------------------------------------------------------------------*/

		class age
			:
			public fvMeshFunctionObject
		{
			// Private Data

				//- The name of the flux field
			word phiName_;

			//- The name of the density field
			word rhoName_;

			//- Number of corrections
			label nCorr_;

			//- Name of field from which schemes are taken
			word schemesField_;


			// Private Member Functions

				//- The list of patch types for the age field
			FoamFunctionObjects_EXPORT wordList patchTypes() const;


		public:

			//- Runtime type information
			//TypeName("age");
			static const char* typeName_() { return "age"; }
			static FoamFunctionObjects_EXPORT const ::tnbLib::word typeName;
			static FoamFunctionObjects_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from Time and dictionary
			FoamFunctionObjects_EXPORT age
			(
				const word& name,
				const Time& runTime,
				const dictionary& dict
			);


			//- Destructor
			FoamFunctionObjects_EXPORT virtual ~age();


			// Member Functions

				//- Read the data
			FoamFunctionObjects_EXPORT virtual bool read(const dictionary&);

			//- Execute
			FoamFunctionObjects_EXPORT virtual bool execute();

			//- Write
			FoamFunctionObjects_EXPORT virtual bool write();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace functionObjects
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_age_Header
