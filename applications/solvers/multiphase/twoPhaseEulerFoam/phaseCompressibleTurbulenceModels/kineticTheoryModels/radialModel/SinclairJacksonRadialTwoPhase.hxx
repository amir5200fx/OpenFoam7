#pragma once
#ifndef _SinclairJacksonRadialTwoPhase_Header
#define _SinclairJacksonRadialTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
    tnbLib::kineticTheoryModels::radialModels::SinclairJackson

Description

SourceFiles
    SinclairJacksonRadialTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "radialModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace radialModels
        {

            /*---------------------------------------------------------------------------*\
                                       Class SinclairJackson Declaration
            \*---------------------------------------------------------------------------*/

            class SinclairJackson
                :
                public radialModel
            {

            public:

                //- Runtime type information
                TypeName("SinclairJackson");


                // Constructors

                    //- Construct from components
                SinclairJackson(const dictionary& dict);


                //- Destructor
                virtual ~SinclairJackson();


                // Member Functions

                tmp<volScalarField> g0
                (
                    const volScalarField& alpha,
                    const dimensionedScalar& alphaMinFriction,
                    const dimensionedScalar& alphaMax
                ) const;

                tmp<volScalarField> g0prime
                (
                    const volScalarField& alpha,
                    const dimensionedScalar& alphaMinFriction,
                    const dimensionedScalar& alphaMax
                ) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace radialModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SinclairJacksonRadialTwoPhase_Header