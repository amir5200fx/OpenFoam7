#pragma once
#ifndef _general_Header
#define _general_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::relativeVelocityModels::general

Description
    General relative velocity model

SourceFiles
    general.C

\*---------------------------------------------------------------------------*/

#include "relativeVelocityModel.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace relativeVelocityModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class general Declaration
        \*---------------------------------------------------------------------------*/

        class general
            :
            public relativeVelocityModel
        {
            // Private Data

                //- A coefficient
            dimensionedScalar a_;

            //- a1 coefficient
            dimensionedScalar a1_;

            //- Drift velocity
            dimensionedVector V0_;

            //- Residual phase fraction
            dimensionedScalar residualAlpha_;


        public:

            //- Runtime type information
            TypeName("general");


            // Constructors

                //- Construct from components
            general
            (
                const dictionary& dict,
                const incompressibleTwoPhaseInteractingMixture& mixture
            );


            //- Destructor
            ~general();


            // Member Functions

                //- Update the diffusion velocity
            virtual void correct();
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace relativeVelocityModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_general_Header
