#pragma once
#ifndef _viscosityModelBirdCarreau_Header
#define _viscosityModelBirdCarreau_Header

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
	tnbLib::viscosityModels::BirdCarreau

Description
	An incompressible Bird-Carreau non-Newtonian viscosity model.

	The Bird-Carreau-Yasuda form is also supported if the optional "a"
	coefficient is specified.  "a" defaults to 2 for the Bird-Carreau model.

SourceFiles
	BirdCarreau.C

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
								   Class BirdCarreau Declaration
		\*---------------------------------------------------------------------------*/

		class BirdCarreau
			:
			public viscosityModel
		{
			// Private Data

			dictionary BirdCarreauCoeffs_;

			dimensionedScalar nu0_;
			dimensionedScalar nuInf_;
			dimensionedScalar k_;
			dimensionedScalar n_;
			dimensionedScalar a_;

			volScalarField nu_;


			// Private Member Functions

				//- Calculate and return the laminar viscosity
			tmp<volScalarField> calcNu() const;


		public:

			//- Runtime type information
			TypeName("BirdCarreau");


			// Constructors

				//- Construct from components
			BirdCarreau
			(
				const word& name,
				const dictionary& viscosityProperties,
				const volVectorField& U,
				const surfaceScalarField& phi
			);


			//- Destructor
			virtual ~BirdCarreau()
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
			virtual bool read(const dictionary& viscosityProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace viscosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_viscosityModelBirdCarreau_Header
