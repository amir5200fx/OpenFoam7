#pragma once
#ifndef _kEpsilonLopesdaCosta_Header
#define _kEpsilonLopesdaCosta_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::RASModels::kEpsilonLopesdaCosta

Description
	Variant of the standard k-epsilon turbulence model with additional source
	terms to handle the changes in turbulence in porous regions represented by
	the powerLawLopesdaCosta porosity model.

	Reference:
	\verbatim
		Costa, J. C. P. L. D. (2007).
		Atmospheric flow over forested and non-forested complex terrain.
	\endverbatim

	The default model coefficients are
	\verbatim
		kEpsilonLopesdaCostaCoeffs
		{
			Cmu         0.09;
			C1          1.44;
			C2          1.92;
			sigmak      1.0;
			sigmaEps    1.3;
		}
	\endverbatim

See also
	tnbLib::RASModels::kEpsilon
	tnbLib::porosityModels::powerLawLopesdaCosta

SourceFiles
	kEpsilonLopesdaCosta.C

\*---------------------------------------------------------------------------*/

#include <AtmosphericModels_Module.hxx>
#include <RASModel.hxx>
#include <eddyViscosity.hxx>
#include <powerLawLopesdaCosta.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		/*---------------------------------------------------------------------------*\
								   Class kEpsilonLopesdaCosta Declaration
		\*---------------------------------------------------------------------------*/

		template<class BasicTurbulenceModel>
		class kEpsilonLopesdaCosta
			:
			public eddyViscosity<RASModel<BasicTurbulenceModel>>
		{
		protected:

			// Protected data

				// Standard model coefficients

			volScalarField Cmu_;
			volScalarField::Internal C1_;
			volScalarField::Internal C2_;
			volScalarField sigmak_;
			volScalarField sigmaEps_;

			// Lopes da Costa porosity coefficients

			volScalarField::Internal CdSigma_;
			volScalarField::Internal betap_;
			volScalarField::Internal betad_;
			volScalarField::Internal C4_;
			volScalarField::Internal C5_;


			// Fields

			volScalarField k_;
			volScalarField epsilon_;


			// Protected Member Functions

			void setPorosityCoefficient
			(
				volScalarField::Internal& C,
				const porosityModels::powerLawLopesdaCosta& pm
			);

			void setCdSigma
			(
				volScalarField::Internal& C,
				const porosityModels::powerLawLopesdaCosta& pm
			);

			void setPorosityCoefficients();

			virtual void correctNut();

			virtual tmp<fvScalarMatrix> kSource
			(
				const volScalarField::Internal& magU,
				const volScalarField::Internal& magU3
			) const;

			virtual tmp<fvScalarMatrix> epsilonSource
			(
				const volScalarField::Internal& magU,
				const volScalarField::Internal& magU3
			) const;


		public:

			typedef typename BasicTurbulenceModel::alphaField alphaField;
			typedef typename BasicTurbulenceModel::rhoField rhoField;
			typedef typename BasicTurbulenceModel::transportModel transportModel;


			//- Runtime type information
			//TypeName("kEpsilonLopesdaCosta");
			static const char* typeName_() { return "kEpsilonLopesdaCosta"; }
			static FoamAtmosphericModels_EXPORT const ::tnbLib::word typeName;
			static FoamAtmosphericModels_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from components
			kEpsilonLopesdaCosta
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
			kEpsilonLopesdaCosta(const kEpsilonLopesdaCosta&) = delete;


			//- Destructor
			virtual ~kEpsilonLopesdaCosta()
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
			void operator=(const kEpsilonLopesdaCosta&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <kEpsilonLopesdaCosta.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_kEpsilonLopesdaCosta_Header
