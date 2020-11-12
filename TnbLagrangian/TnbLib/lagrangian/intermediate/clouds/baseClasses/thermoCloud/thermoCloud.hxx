#pragma once
#ifndef _thermoCloud_Header
#define _thermoCloud_Header

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
	tnbLib::thermoCloud

Description
	Virtual abstract base class for templated ThermoCloud

SourceFiles
	thermoCloud.C

\*---------------------------------------------------------------------------*/

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class thermoCloud Declaration
	\*---------------------------------------------------------------------------*/

	class thermoCloud
	{
	public:

		//- Runtime type information
		//TypeName("thermoCloud");
		static const char* typeName_() { return "thermoCloud"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT thermoCloud();

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT thermoCloud(const thermoCloud&) = delete;


		//- Destructor
		FoamLagrangian_EXPORT virtual ~thermoCloud();


		// Member Functions

			//- Return tmp equivalent particulate emission
		FoamLagrangian_EXPORT virtual tmp<volScalarField> Ep() const = 0;

		//- Return tmp equivalent particulate absorption
		FoamLagrangian_EXPORT virtual tmp<volScalarField> ap() const = 0;

		//- Return tmp equivalent particulate scattering factor
		FoamLagrangian_EXPORT virtual tmp<volScalarField> sigmap() const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const thermoCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_thermoCloud_Header
