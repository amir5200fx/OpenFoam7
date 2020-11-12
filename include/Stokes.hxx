#pragma once
#ifndef _Stokes_Header
#define _Stokes_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
	tnbLib::laminarModels::Stokes

Description
	Turbulence model for Stokes flow.

SourceFiles
	Stokes.C

\*---------------------------------------------------------------------------*/

#include <laminarModelTemplate.hxx>
#include <linearViscousStress.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamStokes_EXPORT __declspec(dllexport)
#else
#ifdef FoamStokes_EXPORT_DEFINE
#define FoamStokes_EXPORT __declspec(dllexport)
#else
#define FoamStokes_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		/*---------------------------------------------------------------------------* \
								   Class Stokes Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class Stokes
			:
			public linearViscousStress<laminarModel<BasicTurbulenceModel>>
		{

		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("Stokes");
			static const char* typeName_() { return "Stokes"; }
			static FoamStokes_EXPORT const ::tnbLib::word typeName;
			static FoamStokes_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			Stokes
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName
			);


			// Selectors

				//- Return a reference to the selected turbulence model
			static autoPtr<Stokes> New
			(
				const alphaField& alpha,
				const rhoField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName = turbulenceModel::propertiesName
			);


			//- Destructor
			virtual ~Stokes()
			{}


			// Member Functions

				//- Const access to the coefficients dictionary
			virtual const dictionary& coeffDict() const;

			//- Read turbulenceProperties dictionary
			virtual bool read();

			//- Return the turbulence viscosity, i.e. 0 for Stokes flow
			virtual tmp<volScalarField> nut() const;

			//- Return the turbulence viscosity on patch
			virtual tmp<scalarField> nut(const label patchi) const;

			//- Return the effective viscosity, i.e. the Stokes viscosity
			virtual tmp<volScalarField> nuEff() const;

			//- Return the effective viscosity on patch
			virtual tmp<scalarField> nuEff(const label patchi) const;

			//- Return the turbulence kinetic energy, i.e. 0 for Stokes flow
			virtual tmp<volScalarField> k() const;

			//- Return the turbulence kinetic energy dissipation rate,
			//  i.e. 0 for Stokes flow
			virtual tmp<volScalarField> epsilon() const;

			//- Return the Reynolds stress tensor, i.e. 0 for Stokes flow
			virtual tmp<volSymmTensorField> R() const;

			//- Correct the Stokes viscosity
			virtual void correct();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <StokesI.hxx>

//#ifdef NoRepository
//#include <Stokes.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Stokes_Header
