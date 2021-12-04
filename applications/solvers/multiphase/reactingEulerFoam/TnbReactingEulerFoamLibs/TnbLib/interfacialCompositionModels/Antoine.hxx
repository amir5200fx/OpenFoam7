#pragma once
#ifndef _Antoine_Header
#define _Antoine_Header

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
    tnbLib::saturationModels::Antoine

Description
    Antoine equation for the vapour pressure.

    \f[
        \log p = A + \frac{B}{C + T}
    \f]

    Coefficients \f$A\f$, \f$B\f$ and \f$C\f$ are to be supplied and should be
    suitable for natural logarithms and temperatures in Kelvin.

SourceFiles
    Antoine.C

\*---------------------------------------------------------------------------*/

#include <saturationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace saturationModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class Antoine Declaration
        \*---------------------------------------------------------------------------*/

        class Antoine
            :
            public saturationModel
        {
        protected:

            // Protected data

                //- Constant A
            dimensionedScalar A_;

            //- Constant B
            dimensionedScalar B_;

            //- Constant C
            dimensionedScalar C_;


        public:

            //- Runtime type information
            TypeName("Antoine");

            // Constructors

                //- Construct from a dictionary
            FoamReactingEulerFoamLibs_EXPORT Antoine(const dictionary& dict, const objectRegistry& db);


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~Antoine();


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

#endif // !_Antoine_Header