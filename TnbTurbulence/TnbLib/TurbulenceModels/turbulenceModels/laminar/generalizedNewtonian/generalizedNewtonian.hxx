#pragma once
#ifndef _generalizedNewtonian_Header
#define _generalizedNewtonian_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018 OpenFOAM Foundation
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
	tnbLib::laminarModels::generalizedNewtonian

Description
	Turbulence model for shear-dependent Non-Newtonian flow.

SourceFiles
	generalizedNewtonian.C

\*---------------------------------------------------------------------------*/

#include <laminarModelTemplate.hxx>
#include <linearViscousStress.hxx>
#include <generalizedNewtonianViscosityModel.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamgeneralizedNewtonian_EXPORT __declspec(dllexport)
#else
#ifdef FoamgeneralizedNewtonian_EXPORT_DEFINE
#define FoamgeneralizedNewtonian_EXPORT __declspec(dllexport)
#else
#define FoamgeneralizedNewtonian_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		/*---------------------------------------------------------------------------*\
							Class generalizedNewtonian Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class generalizedNewtonian
			:
			public linearViscousStress<laminarModel<BasicTurbulenceModel>>
		{

		protected:

			// Protected data

				//- Run-time selectable non-Newtonian viscosity model
			autoPtr<generalizedNewtonianViscosityModel> viscosityModel_;

			//- The non-Newtonian viscosity field
			volScalarField nu_;


			// Protected Member Functions

			virtual tmp<volScalarField> strainRate() const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("generalizedNewtonian");
			static const char* typeName_() { return "generalizedNewtonian"; }
			static FoamgeneralizedNewtonian_EXPORT const ::tnbLib::word typeName;
			static FoamgeneralizedNewtonian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			generalizedNewtonian
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
			static autoPtr<generalizedNewtonian> New
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
			virtual ~generalizedNewtonian()
			{}


			// Member Functions

				//- Read turbulenceProperties dictionary
			virtual bool read();

			//- Return the turbulence viscosity,
			//  i.e. 0 for generalized Newtonian flow
			virtual tmp<volScalarField> nut() const;

			//- Return the turbulence viscosity on patch
			virtual tmp<scalarField> nut(const label patchi) const;

			//- Return the effective viscosity
			//  i.e. the generalizedNewtonian viscosity
			virtual tmp<volScalarField> nuEff() const;

			//- Return the effective viscosity on patch
			virtual tmp<scalarField> nuEff(const label patchi) const;

			//- Return the turbulence kinetic energy
			//  i.e. 0 for generalizedNewtonian flow
			virtual tmp<volScalarField> k() const;

			//- Return the turbulence kinetic energy dissipation rate,
			//  i.e. 0 for generalizedNewtonian flow
			virtual tmp<volScalarField> epsilon() const;

			//- Return the Reynolds stress tensor
			//  i.e. 0 for generalizedNewtonian flow
			virtual tmp<volSymmTensorField> R() const;

			//- Correct the generalizedNewtonian viscosity
			virtual void correct();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <generalizedNewtonianI.hxx>

//#ifdef NoRepository
//#include <generalizedNewtonian.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_generalizedNewtonian_Header
