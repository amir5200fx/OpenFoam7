#pragma once
#ifndef _viscosityModelNewtonian_Header
#define _viscosityModelNewtonian_Header

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
	tnbLib::viscosityModels::Newtonian

Description
	An incompressible Newtonian viscosity model.

SourceFiles
	Newtonian.C

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
								   Class Newtonian Declaration
		\*---------------------------------------------------------------------------*/

		class Newtonian
			:
			public viscosityModel
		{
			// Private Data

			dimensionedScalar nu0_;

			volScalarField nu_;


		public:

			//- Runtime type information
			//TypeName("Newtonian");
			static const char* typeName_() { return "Newtonian"; }
			static FoamTransportModels_EXPORT const ::tnbLib::word typeName;
			static FoamTransportModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			FoamTransportModels_EXPORT Newtonian
			(
				const word& name,
				const dictionary& viscosityProperties,
				const volVectorField& U,
				const surfaceScalarField& phi
			);


			//- Destructor
			virtual ~Newtonian()
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

			//- Correct the laminar viscosity (not appropriate, viscosity constant)
			virtual void correct()
			{}

			//- Read transportProperties dictionary
			FoamTransportModels_EXPORT virtual bool read(const dictionary& viscosityProperties);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace viscosityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_viscosityModelNewtonian_Header
