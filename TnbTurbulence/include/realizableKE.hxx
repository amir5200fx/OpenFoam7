#pragma once
#ifndef _realizableKE_Header
#define _realizableKE_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::RASModels::realizableKE

Description
	Realizable k-epsilon turbulence model for incompressible and compressible
	flows.

	References:
	\verbatim
		Shih, T. H., Liou, W. W., Shabbir, A., Yang, Z., & Zhu, J. (1994).
		A new k-epsilon eddy viscosity model for high Reynolds number
		turbulent flows: Model development and validation.
		NASA STI/Recon Technical Report N, 95, 11442.

		Shih, T. H., Liou, W. W., Shabbir, A., Yang, Z., & Zhu, J. (1995).
		A New k-epsilon Eddy Viscosity Model for High Reynolds Number
		Turbulent Flows.
		Computers and Fluids, 24(3), 227-238.
	\endverbatim

	The default model coefficients are
	\verbatim
		realizableKECoeffs
		{
			A0          4.0;
			C2          1.9;
			sigmak      1.0;
			sigmaEps    1.2;
		}
	\endverbatim

SourceFiles
	realizableKE.C

\*---------------------------------------------------------------------------*/

#include <RASModel.hxx>
#include <eddyViscosity.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamrealizableKE_EXPORT __declspec(dllexport)
#else
#ifdef FoamrealizableKE_EXPORT_DEFINE
#define FoamrealizableKE_EXPORT __declspec(dllexport)
#else
#define FoamrealizableKE_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		/*---------------------------------------------------------------------------*\
								Class realizableKE Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class realizableKE
			:
			public eddyViscosity<RASModel<BasicTurbulenceModel>>
		{

		protected:

			// Protected data

				// Model coefficients

			dimensionedScalar A0_;
			dimensionedScalar C2_;
			dimensionedScalar sigmak_;
			dimensionedScalar sigmaEps_;


			// Fields

			volScalarField k_;
			volScalarField epsilon_;


			// Protected Member Functions

			tmp<volScalarField> rCmu
			(
				const volTensorField& gradU,
				const volScalarField& S2,
				const volScalarField& magS
			);

			virtual void correctNut
			(
				const volTensorField& gradU,
				const volScalarField& S2,
				const volScalarField& magS
			);

			virtual void correctNut();
			virtual tmp<fvScalarMatrix> kSource() const;
			virtual tmp<fvScalarMatrix> epsilonSource() const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("realizableKE");
			static const char* typeName_() { return "realizableKE"; }
			static FoamrealizableKE_EXPORT const ::tnbLib::word typeName;
			static FoamrealizableKE_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			// Constructors

				//- Construct from components
			realizableKE
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


			//- Destructor
			virtual ~realizableKE()
			{}


			// Member Functions

				//- Re-read model coefficients if they have changed
			virtual bool read();

			//- Return the effective diffusivity for k
			tmp<volScalarField> DkEff() const
			{
				return volScalarField::New
				(
					"DkEff",
					(this->nut_ / sigmak_ + this->nu())
				);
			}

			//- Return the effective diffusivity for epsilon
			tmp<volScalarField> DepsilonEff() const
			{
				return volScalarField::New
				(
					"DepsilonEff",
					(this->nut_ / sigmaEps_ + this->nu())
				);
			}

			//- Return the turbulence kinetic energy
			virtual tmp<volScalarField> k() const
			{
				return k_;
			}

			//- Return the turbulence kinetic energy dissipation rate
			virtual tmp<volScalarField> epsilon() const
			{
				return epsilon_;
			}

			//- Solve the turbulence equations and correct the turbulence viscosity
			virtual void correct();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <realizableKEI.hxx>

//#ifdef NoRepository
//#include <realizableKE.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_realizableKE_Header
