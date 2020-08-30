#pragma once
#ifndef _EddyDiffusivity_Header
#define _EddyDiffusivity_Header

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
	tnbLib::EddyDiffusivity

Description
	Templated abstract base class for single-phase compressible
	turbulence models.

SourceFiles
	EddyDiffusivity.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>  // added by amir
#include <dimensionedScalar.hxx>  // added by amir
#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class EddyDiffusivity Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicTurbulenceModel>
	class EddyDiffusivity
		:
		public BasicTurbulenceModel
	{

	protected:

		// Protected data

			// Model coefficients

		dimensionedScalar Prt_;

		// Fields

		volScalarField alphat_;


		// Protected Member Functions

		virtual void correctNut();


	public:

		typedef typename BasicTurbulenceModel::alphaField alphaField;
		typedef typename BasicTurbulenceModel::rhoField rhoField;
		typedef typename BasicTurbulenceModel::transportModel transportModel;


		// Constructors

			//- Construct
		EddyDiffusivity
		(
			const word& type,
			const alphaField& alpha,
			const volScalarField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& trasport,
			const word& propertiesName
		);


		//- Destructor
		virtual ~EddyDiffusivity()
		{}


		// Member Functions

			//- Re-read model coefficients if they have changed
		virtual bool read();

		//- Turbulent thermal diffusivity for enthalpy [kg/m/s]
		virtual tmp<volScalarField> alphat() const
		{
			return alphat_;
		}

		//- Turbulent thermal diffusivity for enthalpy for a patch [kg/m/s]
		virtual tmp<scalarField> alphat(const label patchi) const
		{
			return alphat()().boundaryField()[patchi];
		}

		//- Effective thermal turbulent diffusivity for temperature
		//  of mixture [W/m/K]
		virtual tmp<volScalarField> kappaEff() const
		{
			return this->transport_.kappaEff(alphat());
		}

		//- Effective thermal turbulent diffusivity for temperature
		//  of mixture for patch [W/m/K]
		virtual tmp<scalarField> kappaEff(const label patchi) const
		{
			return this->transport_.kappaEff(alphat(patchi), patchi);
		}

		//- Effective thermal turbulent diffusivity of mixture [kg/m/s]
		virtual tmp<volScalarField> alphaEff() const
		{
			return this->transport_.alphaEff(alphat());
		}

		//- Effective thermal turbulent diffusivity of mixture
		//  for patch [kg/m/s]
		virtual tmp<scalarField> alphaEff(const label patchi) const
		{
			return this->transport_.alphaEff(alphat(patchi), patchi);
		}

		//- Correct the turbulence thermal diffusivity for energy transport
		virtual void correctEnergyTransport();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <EddyDiffusivity.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_EddyDiffusivity_Header