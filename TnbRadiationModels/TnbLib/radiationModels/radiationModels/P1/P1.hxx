#pragma once
#ifndef _P1_Header
#define _P1_Header

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
	tnbLib::radiationModels::P1

Description
	Works well for combustion applications where optical thickness, tau is
	large, i.e. tau = a*L > 3 (L = distance between objects)

	Assumes
	 - all surfaces are diffuse
	 - tends to over predict radiative fluxes from sources/sinks
	   *** SOURCES NOT CURRENTLY INCLUDED ***

SourceFiles
	P1.C

\*---------------------------------------------------------------------------*/

#include <radiationModel.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{

		/*---------------------------------------------------------------------------*\
								   Class P1 Declaration
		\*---------------------------------------------------------------------------*/

		class P1
			:
			public radiationModel
		{
			// Private Data

				//- Incident radiation / [W/m^2]
			volScalarField G_;

			//- Total radiative heat flux [W/m^2]
			volScalarField qr_;

			//- Absorption coefficient
			volScalarField a_;

			//- Emission coefficient
			volScalarField e_;

			//- Emission contribution
			volScalarField E_;


		public:

			//- Runtime type information
			//TypeName("P1");
			static const char* typeName_() { return "P1"; }
			static FoamRadiationModels_EXPORT const ::tnbLib::word typeName;
			static FoamRadiationModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamRadiationModels_EXPORT P1(const volScalarField& T);

			//- Construct from components
			FoamRadiationModels_EXPORT P1(const dictionary& dict, const volScalarField& T);

			//- Disallow default bitwise copy construction
			FoamRadiationModels_EXPORT P1(const P1&) = delete;


			//- Destructor
			FoamRadiationModels_EXPORT virtual ~P1();


			// Member Functions

				// Edit

					//- Solve radiation equation(s)
			FoamRadiationModels_EXPORT void calculate();

			//- Read radiation properties dictionary
			FoamRadiationModels_EXPORT bool read();


			// Access

				//- Source term component (for power of T^4)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField> Rp() const;

			//- Source term component (constant)
			FoamRadiationModels_EXPORT virtual tmp<volScalarField::Internal> Ru() const;


			// Member Operators

				//- Disallow default bitwise assignment
			FoamRadiationModels_EXPORT void operator=(const P1&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace radiationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_P1_Header
