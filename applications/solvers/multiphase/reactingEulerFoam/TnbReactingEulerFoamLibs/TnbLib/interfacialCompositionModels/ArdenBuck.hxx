#pragma once
#ifndef _ArdenBuck_Header
#define _ArdenBuck_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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
    tnbLib::saturationModels::ArdenBuck

Description
    ArdenBuck equation for the vapour pressure of moist air.

SourceFiles
    ArdenBuck.C

\*---------------------------------------------------------------------------*/

#include <saturationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class ArdenBuck Declaration
        \*---------------------------------------------------------------------------*/

        class ArdenBuck
            :
            public saturationModel
        {
            // Private Member Functions

                //- Exponent divided by the temperature
            tmp<volScalarField> xByTC(const volScalarField& TC) const;


        public:

            //- Runtime type information
            TypeName("ArdenBuck");

            // Constructors

                //- Construct from a dictionary
            FoamReactingEulerFoamLibs_EXPORT ArdenBuck(const dictionary& dict, const objectRegistry& db);


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~ArdenBuck();


            // Member Functions

                //- Saturation pressure
            FoamReactingEulerFoamLibs_EXPORT  virtual tmp<volScalarField> pSat(const volScalarField& T) const;

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

#endif // !_ArdenBuck_Header
