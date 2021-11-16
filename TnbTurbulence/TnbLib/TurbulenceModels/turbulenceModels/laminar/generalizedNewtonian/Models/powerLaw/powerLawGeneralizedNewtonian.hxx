#pragma once
#ifndef _powerLawGeneralizedNewtonian_Header
#define _powerLawGeneralizedNewtonian_Header

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
	tnbLib::laminarModels::generalizedNewtonianViscosityModels::powerLaw

Description
	Standard power-law generalized Newtonian viscosity model

SourceFiles
	powerLaw.C

\*---------------------------------------------------------------------------*/

#include <generalizedNewtonianViscosityModel.hxx>
#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{

			/*---------------------------------------------------------------------------*\
									   Class powerLaw Declaration
			\*---------------------------------------------------------------------------*/

			class powerLaw
				:
				public generalizedNewtonianViscosityModel
			{
				// Private Data

				dimensionedScalar k_;
				dimensionedScalar n_;
				dimensionedScalar nuMin_;
				dimensionedScalar nuMax_;


			public:

				//- Runtime type information
				//TypeName("powerLaw");
				static const char* typeName_() { return "powerLaw"; }
				static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
				static FoamTurbulence_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamTurbulence_EXPORT powerLaw(const dictionary& viscosityProperties);


				//- Destructor
				virtual ~powerLaw()
				{}


				// Member Functions

					//- Read transportProperties dictionary
				FoamTurbulence_EXPORT virtual bool read(const dictionary& viscosityProperties);

				//- Return the laminar viscosity
				FoamTurbulence_EXPORT virtual tmp<volScalarField> nu
				(
					const volScalarField& nu0,
					const volScalarField& strainRate
				) const;
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace generalizedNewtonianViscosityModels
	} // End namespace laminarModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_powerLawGeneralizedNewtonian_Header
