#pragma once
#ifndef _polynomialMultiphase_Header
#define _polynomialMultiphase_Header

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
    tnbLib::saturationModels::polynomial

Description
    Polynomial equation for the saturation vapour temperature in terms of
    the vapour pressure (in Pa).

    \f[
        T_sat = \sum_i C_i p^i
    \f]

    where \f$p\f$ is the pressure in Pa and \f$C\f$ are the coefficients.

    Currently this class only provides \f$T_sat\f$, the inverse function to
    return the vapour pressure for a given temperature are not implemented.

SourceFiles
    polynomial.C

\*---------------------------------------------------------------------------*/

#include <saturationModel.hxx>
#include <Polynomial.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class polynomial Declaration
        \*---------------------------------------------------------------------------*/

        class polynomial
            :
            public saturationModel
        {
            // Private Data

                //- Polynomial coefficients
            Polynomial<8> C_;


        public:

            //- Runtime type information
            TypeName("polynomial");

            // Constructors

                //- Construct from a dictionary
            FoamReactingEulerFoamLibs_EXPORT polynomial(const dictionary& dict, const objectRegistry& db);


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~polynomial();


            // Member Functions

                //- Saturation pressure
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> pSat(const volScalarField& T) const;

            //- Saturation pressure derivetive w.r.t. temperature
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> pSatPrime(const volScalarField& T) const;

            //- Natural log of the saturation pressure
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> lnPSat(const volScalarField& T) const;

            //- Saturation temperature
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Tsat(const volScalarField& p) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace saturationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polynomialMultiphase_Header
