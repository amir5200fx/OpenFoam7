#pragma once
#ifndef _kineticTheoryModelTwoPhase_Header
#define _kineticTheoryModelTwoPhase_Header

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
    tnbLib::RASModels::kineticTheoryModel

Description
    Kinetic theory particle phase RAS model

    Reference:
    \verbatim
        "Derivation, implementation, and validation of computer simulation
         models for gas-solid fluidized beds",
        van Wachem, B.G.M.,
        Ph.D. Thesis, Delft University of Technology, Amsterdam, 2000.
    \endverbatim

    There are no default model coefficients.

SourceFiles
    kineticTheoryModelTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <RASModel.hxx>
#include <eddyViscosity.hxx>

#include "phaseCompressibleTurbulenceModelTwoPhase.hxx"

#include <EddyDiffusivity.hxx>

#include "phaseModelTwoPhase.hxx"
#include "dragModelTwoPhase.hxx"
#include "viscosityModelTwoPhase.hxx"
#include "conductivityModelTwoPhase.hxx"
#include "radialModelTwoPhase.hxx"
#include "granularPressureModelTwoPhase.hxx"
#include "frictionalStressModelTwoPhase.hxx"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace RASModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class kineticTheoryModel Declaration
        \*---------------------------------------------------------------------------*/

        class kineticTheoryModel
            :
            public eddyViscosity
            <
            RASModel<EddyDiffusivity<phaseCompressibleTurbulenceModel>>
            >
        {
            // Private Data

                // Input Fields

            const phaseModel& phase_;


            // Sub-models

                //- Run-time selected viscosity model
            autoPtr<kineticTheoryModels::viscosityModel> viscosityModel_;

            //- Run-time selected conductivity model
            autoPtr<kineticTheoryModels::conductivityModel> conductivityModel_;

            //- Run-time selected radial distribution model
            autoPtr<kineticTheoryModels::radialModel> radialModel_;

            //- Run-time selected granular pressure model
            autoPtr<kineticTheoryModels::granularPressureModel>
                granularPressureModel_;

            //- Run-time selected frictional stress model
            autoPtr<kineticTheoryModels::frictionalStressModel>
                frictionalStressModel_;


            // Kinetic Theory Model coefficients

                //- Use equilibrium approximation: generation == dissipation
            Switch equilibrium_;

            //- Coefficient of restitution
            dimensionedScalar e_;

            //- Maximum packing phase-fraction
            dimensionedScalar alphaMax_;

            //- Min value for which the frictional stresses are zero
            dimensionedScalar alphaMinFriction_;

            //- Residual phase fraction
            dimensionedScalar residualAlpha_;

            //- Maximum turbulent viscosity
            dimensionedScalar maxNut_;


            // Kinetic Theory Model Fields

                //- The granular energy/temperature
            volScalarField Theta_;

            //- The granular bulk viscosity
            volScalarField lambda_;

            //- The granular radial distribution
            volScalarField gs0_;

            //- The granular "thermal" conductivity
            volScalarField kappa_;

            //- The frictional viscosity
            volScalarField nuFric_;


            // Private Member Functions

            void correctNut()
            {}


        public:

            //- Runtime type information
            TypeName("kineticTheory");


            // Constructors

                //- Construct from components
            kineticTheoryModel
            (
                const volScalarField& alpha,
                const volScalarField& rho,
                const volVectorField& U,
                const surfaceScalarField& alphaRhoPhi,
                const surfaceScalarField& phi,
                const phaseModel& transport,
                const word& propertiesName = turbulenceModel::propertiesName,
                const word& type = typeName
            );

            //- Disallow default bitwise copy construction
            kineticTheoryModel(const kineticTheoryModel&) = delete;


            //- Destructor
            virtual ~kineticTheoryModel();


            // Member Functions

                //- Re-read model coefficients if they have changed
            virtual bool read();

            //- Return the effective viscosity
            virtual tmp<volScalarField> nuEff() const
            {
                return this->nut();
            }

            //- Return the effective viscosity on patch
            virtual tmp<scalarField> nuEff(const label patchi) const
            {
                return this->nut(patchi);
            }

            //- Return the turbulence kinetic energy
            virtual tmp<volScalarField> k() const;

            //- Return the turbulence kinetic energy dissipation rate
            virtual tmp<volScalarField> epsilon() const;

            //- Return the Reynolds stress tensor
            virtual tmp<volSymmTensorField> R() const;

            //- Return the phase-pressure'
            // (derivative of phase-pressure w.r.t. phase-fraction)
            virtual tmp<volScalarField> pPrime() const;

            //- Return the face-phase-pressure'
            // (derivative of phase-pressure w.r.t. phase-fraction)
            virtual tmp<surfaceScalarField> pPrimef() const;

            //- Return the effective stress tensor
            virtual tmp<volSymmTensorField> devRhoReff() const;

            //- Return the source term for the momentum equation
            virtual tmp<fvVectorMatrix> divDevRhoReff(volVectorField& U) const;

            //- Solve the kinetic theory equations and correct the viscosity
            virtual void correct();


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const kineticTheoryModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace RASModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_kineticTheoryModelTwoPhase_Header
