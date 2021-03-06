#pragma once
#ifndef _ShihQuadraticKE_Header
#define _ShihQuadraticKE_Header

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
	tnbLib::incompressible::RASModels::ShihQuadraticKE

Description
	Shih's quadratic algebraic Reynolds stress k-epsilon turbulence model for
	incompressible flows

	This turbulence model is described in:
	\verbatim
		Shih, T. H., Zhu, J., & Lumley, J. L. (1993).
		A realizable Reynolds stress algebraic equation model.
		NASA technical memorandum 105993.
	\endverbatim

	Implemented according to the specification in:
	<a href=
	"https://personalpages.manchester.ac.uk/staff/david.d.apsley/turbmod.pdf"
	>Apsley: Turbulence Models 2002</a>

SourceFiles
	ShihQuadraticKE.C

\*---------------------------------------------------------------------------*/

#include <turbulentTransportModel.hxx>
#include <nonlinearEddyViscosity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{
		namespace RASModels
		{

			/*---------------------------------------------------------------------------*\
								  Class ShihQuadraticKE Declaration
			\*---------------------------------------------------------------------------*/

			class ShihQuadraticKE
				:
				public nonlinearEddyViscosity<incompressible::RASModel>
			{

			protected:

				// Protected data

					// Model coefficients

				dimensionedScalar Ceps1_;
				dimensionedScalar Ceps2_;
				dimensionedScalar sigmak_;
				dimensionedScalar sigmaEps_;
				dimensionedScalar Cmu1_;
				dimensionedScalar Cmu2_;
				dimensionedScalar Cbeta_;
				dimensionedScalar Cbeta1_;
				dimensionedScalar Cbeta2_;
				dimensionedScalar Cbeta3_;


				// Fields

				volScalarField k_;
				volScalarField epsilon_;


				// Protected Member Functions

				FoamTurbulence_EXPORT virtual void correctNut();
				FoamTurbulence_EXPORT virtual void correctNonlinearStress(const volTensorField& gradU);


			public:

				//- Runtime type information
				//TypeName("ShihQuadraticKE");
				static const char* typeName_() { return "ShihQuadraticKE"; }
				static FoamTurbulence_EXPORT const ::tnbLib::word typeName;
				static FoamTurbulence_EXPORT int debug;
				virtual const word& type() const { return typeName; };


				// Constructors

					//- Construct from components
				FoamTurbulence_EXPORT ShihQuadraticKE
				(
					const geometricOneField& alpha,
					const geometricOneField& rho,
					const volVectorField& U,
					const surfaceScalarField& alphaRhoPhi,
					const surfaceScalarField& phi,
					const transportModel& transport,
					const word& propertiesName = turbulenceModel::propertiesName,
					const word& type = typeName
				);


				//- Destructor
				virtual ~ShihQuadraticKE()
				{}


				// Member Functions

					//- Read RASProperties dictionary
				FoamTurbulence_EXPORT virtual bool read();

				//- Return the effective diffusivity for k
				tmp<volScalarField> DkEff() const
				{
					return volScalarField::New
					(
						"DkEff",
						nut_ / sigmak_ + nu()
					);
				}

				//- Return the effective diffusivity for epsilon
				tmp<volScalarField> DepsilonEff() const
				{
					return volScalarField::New
					(
						"DepsilonEff",
						nut_ / sigmaEps_ + nu()
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
				FoamTurbulence_EXPORT virtual void correct();
			};


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace incompressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ShihQuadraticKE_header
