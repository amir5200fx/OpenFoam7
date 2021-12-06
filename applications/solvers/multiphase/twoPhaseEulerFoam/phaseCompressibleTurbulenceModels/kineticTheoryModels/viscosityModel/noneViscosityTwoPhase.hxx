#pragma once
#ifndef _noneViscosityTwoPhase_Header
#define _noneViscosityTwoPhase_Header

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
    tnbLib::kineticTheoryModels::noneViscosity

Description

SourceFiles
    noneViscosityTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "viscosityModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class noneViscosity Declaration
        \*---------------------------------------------------------------------------*/

        class noneViscosity
            :
            public viscosityModel
        {

        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from components
            noneViscosity(const dictionary& dict);


            //- Destructor
            virtual ~noneViscosity();


            // Member Functions

            tmp<volScalarField> nu
            (
                const volScalarField& alpha1,
                const volScalarField& Theta,
                const volScalarField& g0,
                const volScalarField& rho1,
                const volScalarField& da,
                const dimensionedScalar& e
            ) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noneViscosityTwoPhase_Header
