#pragma once
#ifndef _WALE_Header
#define _WALE_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
	tnbLib::LESModels::WALE

Description
	The Wall-adapting local eddy-viscosity (WALE) SGS model.

	Reference:
	\verbatim
		Nicoud, F., & Ducros, F. (1999).
		Subgrid-scale stress modelling based on the square of the velocity
		gradient tensor.
		Flow, Turbulence and Combustion, 62(3), 183-200.
	\endverbatim

	The default model coefficients are
	\verbatim
		WALECoeffs
		{
			Ck                  0.094;
			Ce                  1.048;e
			Cw                  0.325;
		}
	\endverbatim

See also
	tnbLib::LESModels::Smagorinsky

SourceFiles
	WALE.C

\*---------------------------------------------------------------------------*/

#include <LESModel.hxx>
#include <LESeddyViscosity.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamWALE_EXPORT __declspec(dllexport)
#else
#ifdef FoamWALE_EXPORT_DEFINE
#define FoamWALE_EXPORT __declspec(dllexport)
#else
#define FoamWALE_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
								   Class WALE Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class WALE
			:
			public LESeddyViscosity<BasicTurbulenceModel>
		{
		protected:

			// Protected data

			dimensionedScalar Ck_;
			dimensionedScalar Cw_;


			// Protected Member Functions

				//- Return the deviatoric symmetric part of the square of the given
				//  velocity gradient field
			tmp<volSymmTensorField> Sd(const volTensorField& gradU) const;

			//- Return SGS kinetic energy
			//  calculated from the given velocity gradient
			tmp<volScalarField> k(const volTensorField& gradU) const;

			//- Update the SGS eddy-viscosity
			virtual void correctNut();


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("WALE");
			static const char* typeName_() { return "WALE"; }
			static FoamWALE_EXPORT const ::tnbLib::word typeName;
			static FoamWALE_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			WALE
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName,
				const word& type = typeName
			);

			//- Disallow default bitwise copy construction
			WALE(const WALE&) = delete;


			//- Destructor
			virtual ~WALE()
			{}


			// Member Functions

				//- Read model coefficients if they have changed
			virtual bool read();

			//- Return SGS kinetic energy
			virtual tmp<volScalarField> k() const
			{
				return k(fvc::grad(this->U_));
			}

			//- Return sub-grid disipation rate
			virtual tmp<volScalarField> epsilon() const;

			//- Correct Eddy-Viscosity and related properties
			virtual void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const WALE&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WALEI.hxx>

//#ifdef NoRepository
//#include <WALE.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WALE_Header
