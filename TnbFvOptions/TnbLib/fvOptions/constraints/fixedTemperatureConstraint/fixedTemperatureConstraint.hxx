#pragma once
#ifndef _fixedTemperatureConstraint_Header
#define _fixedTemperatureConstraint_Header

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
	tnbLib::fv::fixedTemperatureConstraint

Description
	Fixed temperature equation constraint

Usage
	\verbatim
	fixedTemperature
	{
		type            fixedTemperatureConstraint;
		active          yes;

		mode            uniform;      // uniform or lookup

		// For uniform option
		temperature     constant 500; // fixed temperature with time [K]

		// For lookup option
		// T            <Tname>;      // optional temperature field name
	}
	\endverbatim

Note:
	The 'uniform' option allows the use of a time-varying uniform temperature
	by means of the Function1 type.

See also
	tnbLib::fvOption

SourceFiles
	fixedTemperatureConstraint.C

\*---------------------------------------------------------------------------*/

#include <cellSetOption.hxx>
#include <NamedEnum.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		/*---------------------------------------------------------------------------*\
						 Class fixedTemperatureConstraint Declaration
		\*---------------------------------------------------------------------------*/

		class fixedTemperatureConstraint
			:
			public cellSetOption
		{
		public:

			//- Temperature mode
			enum temperatureMode
			{
				tmUniform,
				tmLookup
			};


			//- String representation of temperatureMode enums
			static FoamFvOptions_EXPORT const NamedEnum<temperatureMode, 2> temperatureModeNames_;


		protected:

			// Protected data

				//- Operation mode
			temperatureMode mode_;

			//- Uniform temperature [K]
			autoPtr<Function1<scalar>> Tuniform_;

			//- Temperature field name
			word TName_;


		public:

			//- Runtime type information
			//TypeName("fixedTemperatureConstraint");
			static const char* typeName_() { return "fixedTemperatureConstraint"; }
			static FoamFvOptions_EXPORT const ::tnbLib::word typeName;
			static FoamFvOptions_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamFvOptions_EXPORT fixedTemperatureConstraint
			(
				const word& name,
				const word& modelType,
				const dictionary& dict,
				const fvMesh& mesh
			);

			//- Disallow default bitwise copy construction
			FoamFvOptions_EXPORT fixedTemperatureConstraint(const fixedTemperatureConstraint&) = delete;


			//- Destructor
			virtual ~fixedTemperatureConstraint()
			{}


			// Member Functions

				//- Constrain energy equation to fix the temperature
			FoamFvOptions_EXPORT virtual void constrain(fvMatrix<scalar>& eqn, const label fieldi);

			//- Read dictionary
			FoamFvOptions_EXPORT virtual bool read(const dictionary& dict);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvOptions_EXPORT void operator=(const fixedTemperatureConstraint&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedTemperatureConstraint_Header
