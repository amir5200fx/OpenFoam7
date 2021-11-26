#pragma once
#ifndef _twoPhaseMixtureThermo_Header
#define _twoPhaseMixtureThermo_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
    tnbLib::twoPhaseMixtureThermo

Description

SourceFiles
    twoPhaseMixtureThermoI.H
    twoPhaseMixtureThermo.C
    twoPhaseMixtureThermoIO.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <rhoThermo.hxx>
#include <psiThermo.hxx>
#include <twoPhaseMixture.hxx>
#include <interfaceProperties.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class twoPhaseMixtureThermo Declaration
    \*---------------------------------------------------------------------------*/

    class twoPhaseMixtureThermo
        :
        public psiThermo,
        public twoPhaseMixture,
        public interfaceProperties
    {
        // Private Data

            //- Thermo-package of phase 1
        autoPtr<rhoThermo> thermo1_;

        //- Thermo-package of phase 2
        autoPtr<rhoThermo> thermo2_;


    public:

        //- Runtime type information
        TypeName("twoPhaseMixtureThermo");


        // Constructors

            //- Construct from components
        twoPhaseMixtureThermo
        (
            const volVectorField& U,
            const surfaceScalarField& phi
        );


        //- Destructor
        virtual ~twoPhaseMixtureThermo();


        // Member Functions

        const rhoThermo& thermo1() const
        {
            return thermo1_();
        }

        const rhoThermo& thermo2() const
        {
            return thermo2_();
        }

        rhoThermo& thermo1()
        {
            return thermo1_();
        }

        rhoThermo& thermo2()
        {
            return thermo2_();
        }

        //- Correct the thermodynamics of each phase
        virtual void correctThermo();

        //- Update mixture properties
        virtual void correct();

        //- Return the name of the thermo physics
        virtual word thermoName() const;

        //- Return true if the equation of state is incompressible
        //  i.e. rho != f(p)
        virtual bool incompressible() const;

        //- Return true if the equation of state is isochoric
        //  i.e. rho = const
        virtual bool isochoric() const;


        // Access to thermodynamic state variables

            //- Enthalpy/Internal energy [J/kg]
            //  Non-const access allowed for transport equations
        virtual volScalarField& he()
        {
            NotImplemented;
            return thermo1_->he();
        }

        //- Enthalpy/Internal energy [J/kg]
        virtual const volScalarField& he() const
        {
            NotImplemented;
            return thermo1_->he();
        }

        //- Enthalpy/Internal energy
        //  for given pressure and temperature [J/kg]
        virtual tmp<volScalarField> he
        (
            const volScalarField& p,
            const volScalarField& T
        ) const;

        //- Enthalpy/Internal energy for cell-set [J/kg]
        virtual tmp<scalarField> he
        (
            const scalarField& p,
            const scalarField& T,
            const labelList& cells
        ) const;

        //- Enthalpy/Internal energy for patch [J/kg]
        virtual tmp<scalarField> he
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Chemical enthalpy [J/kg]
        virtual tmp<volScalarField> hc() const;

        //- Temperature from enthalpy/internal energy for cell-set
        virtual tmp<scalarField> THE
        (
            const scalarField& h,
            const scalarField& p,
            const scalarField& T0,      // starting temperature
            const labelList& cells
        ) const;

        //- Temperature from enthalpy/internal energy for patch
        virtual tmp<scalarField> THE
        (
            const scalarField& h,
            const scalarField& p,
            const scalarField& T0,      // starting temperature
            const label patchi
        ) const;


        // Fields derived from thermodynamic state variables

            //- Heat capacity at constant pressure [J/kg/K]
        virtual tmp<volScalarField> Cp() const;

        //- Heat capacity at constant pressure for patch [J/kg/K]
        virtual tmp<scalarField> Cp
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Heat capacity at constant volume [J/kg/K]
        virtual tmp<volScalarField> Cv() const;

        //- Heat capacity at constant volume for patch [J/kg/K]
        virtual tmp<scalarField> Cv
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Gamma = Cp/Cv []
        virtual tmp<volScalarField> gamma() const;

        //- Gamma = Cp/Cv for patch []
        virtual tmp<scalarField> gamma
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Heat capacity at constant pressure/volume [J/kg/K]
        virtual tmp<volScalarField> Cpv() const;

        //- Heat capacity at constant pressure/volume for patch [J/kg/K]
        virtual tmp<scalarField> Cpv
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Heat capacity ratio []
        virtual tmp<volScalarField> CpByCpv() const;

        //- Heat capacity ratio for patch []
        virtual tmp<scalarField> CpByCpv
        (
            const scalarField& p,
            const scalarField& T,
            const label patchi
        ) const;

        //- Molecular weight [kg/kmol]
        virtual tmp<volScalarField> W() const;

        //- Molecular weight for patch [kg/kmol]
        virtual tmp<scalarField> W(const label patchi) const;


        // Fields derived from transport state variables

            //- Kinematic viscosity of mixture [m^2/s]
        virtual tmp<volScalarField> nu() const;

        //- Kinematic viscosity of mixture for patch [m^2/s]
        virtual tmp<scalarField> nu(const label patchi) const;

        //- Thermal diffusivity for temperature of mixture [W/m/K]
        virtual tmp<volScalarField> kappa() const;

        //- Thermal diffusivity of mixture for patch [W/m/K]
        virtual tmp<scalarField> kappa
        (
            const label patchi
        ) const;

        //- Thermal diffusivity for energy of mixture [kg/m/s]
        virtual tmp<volScalarField> alphahe() const;

        //- Thermal diffusivity for energy of mixture for patch [kg/m/s]
        virtual tmp<scalarField> alphahe(const label patchi) const;

        //- Effective thermal diffusivity of mixture [W/m/K]
        virtual tmp<volScalarField> kappaEff
        (
            const volScalarField& alphat
        ) const;

        //- Effective thermal diffusivity of mixture for patch [W/m/K]
        virtual tmp<scalarField> kappaEff
        (
            const scalarField& alphat,
            const label patchi
        ) const;

        //- Effective thermal diffusivity of mixture [W/m/K]
        virtual tmp<volScalarField> alphaEff
        (
            const volScalarField& alphat
        ) const;

        //- Effective thermal diffusivity of mixture for patch [W/m/K]
        virtual tmp<scalarField> alphaEff
        (
            const scalarField& alphat,
            const label patchi
        ) const;


        // IO

            //- Read base transportProperties dictionary
        virtual bool read();
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_twoPhaseMixtureThermo_Header
