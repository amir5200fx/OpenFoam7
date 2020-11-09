#pragma once
#ifndef _viscosityModelPowerLaw_Header
#define _viscosityModelPowerLaw_Header

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
	tnbLib::viscosityModels::powerLaw

Description
	 Standard power-law non-Newtonian viscosity model.

SourceFiles
	powerLaw.C

\*---------------------------------------------------------------------------*/

#include <viscosityModel.hxx>
#include <dimensionedScalar.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{

		/*---------------------------------------------------------------------------*\
								   Class powerLaw Declaration
		\*---------------------------------------------------------------------------*/

		class powerLaw
			:
			public viscosityModel
		{
			// Private Data

			dictionary powerLawCoeffs_;

			dimensionedScalar k_;
			dimensionedScalar n_;
			dimensionedScalar nuMin_;
			dimensionedScalar nuMax_;

			volScalarField nu_;


			// Private Member Functions

				//- Calculate and return the laminar viscosity
			FoamTransportModels_EXPORT tmp<volScalarField> calcNu() const;


		public:

			//- Runtime type information
			//TypeName("powerLaw");
			static const char* typeName_() { return "powerLaw"; }
			static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
			static FoamTransportModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamTransportModels_EXPORT powerLaw
			(
				const word& name,
				const dictionary& viscosityProperties,
				const volVectorField& U,
				const surfaceScalarField& phi
			);


			//- Destructor
			virtual ~powerLaw()
			{}


			// Member Functions

				//- Return the laminar viscosity
			virtual tmp<volScalarField> nu() const
			{
				return nu_;
			}

			//- Return the laminar viscosity for patch
			virtual tmp<scalarField> nu(const label patchi) const
			{
				return nu_.boundaryField()[patchi];
			}

			//- Correct the laminar viscosity
			virtual void correct()
			{
				nu_ = calcNu();
			}

			//- Read transportProperties dictionary
			FoamTransportModels_EXPORT virtual bool read(const dictionary& viscosityProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace viscosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_viscosityModelPowerLaw_Header
