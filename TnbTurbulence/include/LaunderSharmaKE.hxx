#pragma once
#ifndef _LaunderSharmaKE_Header
#define _LaunderSharmaKE_Header

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
	tnbLib::RASModels::LaunderSharmaKE

Description
	Launder and Sharma low-Reynolds k-epsilon turbulence model for
	incompressible and compressible and combusting flows including
	rapid distortion theory (RDT) based compression term.

	References:
	\verbatim
		Launder, B. E., & Sharma, B. I. (1974).
		Application of the energy-dissipation model of turbulence to the
		calculation of flow near a spinning disc.
		Letters in heat and mass transfer, 1(2), 131-137.

		For the RDT-based compression term:
		El Tahry, S. H. (1983).
		k-epsilon equation for compressible reciprocating engine flows.
		Journal of Energy, 7(4), 345-353.
	\endverbatim

	The default model coefficients are
	\verbatim
		LaunderSharmaKECoeffs
		{
			Cmu         0.09;
			C1          1.44;
			C2          1.92;
			C3          -0.33;
			alphah      1.0;    // only for compressible
			alphahk     1.0;    // only for compressible
			alphaEps    0.76923;
		}
	\endverbatim

SourceFiles
	LaunderSharmaKE.C

\*---------------------------------------------------------------------------*/

#include <RASModel.hxx>
#include <eddyViscosity.hxx>

#ifdef FoamTurbulence_EXPORT_DEFINE
#define FoamLaunderSharmaKE_EXPORT __declspec(dllexport)
#else
#ifdef FoamLaunderSharmaKE_EXPORT_DEFINE
#define FoamLaunderSharmaKE_EXPORT __declspec(dllexport)
#else
#define FoamLaunderSharmaKE_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		/*---------------------------------------------------------------------------*\
								Class LaunderSharmaKE Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class LaunderSharmaKE
			:
			public eddyViscosity<RASModel<BasicTurbulenceModel>>
		{
		protected:

			// Protected data

				// Model coefficients

			dimensionedScalar Cmu_;
			dimensionedScalar C1_;
			dimensionedScalar C2_;
			dimensionedScalar C3_;
			dimensionedScalar sigmak_;
			dimensionedScalar sigmaEps_;


			// Fields

			volScalarField k_;
			volScalarField epsilon_;


			// Private Member Functions

			tmp<volScalarField> fMu() const;
			tmp<volScalarField> f2() const;

			virtual void correctNut();
			virtual tmp<fvScalarMatrix> kSource() const;
			virtual tmp<fvScalarMatrix> epsilonSource() const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("LaunderSharmaKE");
			static const char* typeName_() { return "LaunderSharmaKE"; }
			static FoamLaunderSharmaKE_EXPORT const ::tnbLib::word typeName;
			static FoamLaunderSharmaKE_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			LaunderSharmaKE
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
			LaunderSharmaKE(const LaunderSharmaKE&) = delete;


			//- Destructor
			virtual ~LaunderSharmaKE()
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


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const LaunderSharmaKE&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LaunderSharmaKEI.hxx>

//#ifdef NoRepository
//#include <LaunderSharmaKE.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LaunderSharmaKE_Header
