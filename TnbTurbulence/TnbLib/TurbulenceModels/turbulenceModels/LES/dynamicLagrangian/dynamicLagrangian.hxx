#pragma once
#ifndef _dynamicLagrangian_Header
#define _dynamicLagrangian_Header

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
	tnbLib::LESModels::dynamicLagrangian

Description
	Dynamic SGS model with Lagrangian averaging

	Reference:
	\verbatim
		Meneveau, C., Lund, T. S., & Cabot, W. H. (1996).
		A Lagrangian dynamic subgrid-scale model of turbulence.
		Journal of Fluid Mechanics, 319, 353-385.
	\endverbatim

SourceFiles
	dynamicLagrangian.C

\*---------------------------------------------------------------------------*/

#include <LESeddyViscosity.hxx>
#include <simpleFilter.hxx>

#include <fvc.hxx>  // added by amir

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamdynamicLagrangian_EXPORT __declspec(dllexport)
#else
#ifdef FoamdynamicLagrangian_EXPORT_DEFINE
#define FoamdynamicLagrangian_EXPORT __declspec(dllexport)
#else
#define FoamdynamicLagrangian_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		/*---------------------------------------------------------------------------*\
							   Class dynamicLagrangian Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class dynamicLagrangian
			:
			public LESeddyViscosity<BasicTurbulenceModel>
		{
		protected:

			// Protected data

			volScalarField flm_;
			volScalarField fmm_;

			dimensionedScalar theta_;

			simpleFilter simpleFilter_;
			autoPtr<LESfilter> filterPtr_;
			LESfilter& filter_;

			dimensionedScalar flm0_;
			dimensionedScalar fmm0_;


			// Protected Member Functions

				//- Update sub-grid eddy-viscosity
			void correctNut(const tmp<volTensorField>& gradU);

			virtual void correctNut();


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;

			//- Runtime type information
			//TypeName("dynamicLagrangian");
			static const char* typeName_() { return "dynamicLagrangian"; }
			static FoamdynamicLagrangian_EXPORT const ::tnbLib::word typeName;
			static FoamdynamicLagrangian_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			dynamicLagrangian
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
			dynamicLagrangian(const dynamicLagrangian&) = delete;


			//- Destructor
			virtual ~dynamicLagrangian()
			{}


			// Member Functions

				//- Read model coefficients if they have changed
			virtual bool read();

			//- Return SGS kinetic energy
			tmp<volScalarField> k(const tmp<volTensorField>& gradU) const
			{
				return
					pow(2.0*flm_ / fmm_, 2.0 / 3.0)
					* pow(this->Ce_, -2.0 / 3.0)
					* sqr(this->delta())*magSqr(dev(symm(gradU)));
			}

			//- Return SGS kinetic energy
			virtual tmp<volScalarField> k() const
			{
				return k(fvc::grad(this->U_));
			}

			//- Return the effective diffusivity for k
			tmp<volScalarField> DkEff() const
			{
				return volScalarField::New
				(
					"DkEff",
					this->nut_ + this->nu()
				);
			}

			//- Correct Eddy-Viscosity and related properties
			virtual void correct();


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const dynamicLagrangian&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <dynamicLagrangianI.hxx>

//#ifdef NoRepository
//#include <dynamicLagrangian.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicLagrangian_Header
