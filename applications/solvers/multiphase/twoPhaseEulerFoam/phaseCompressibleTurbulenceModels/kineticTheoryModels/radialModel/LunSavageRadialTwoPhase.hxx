#pragma once
#ifndef _LunSavageRadialTwoPhase_Header
#define _LunSavageRadialTwoPhase_Header

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
    tnbLib::kineticTheoryModels::radialModels::LunSavage

Description

SourceFiles
    LunSavageTwoPhase.cxx

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
                                       Class LunSavage Declaration
            \*---------------------------------------------------------------------------*/

            class LunSavage
                :
                public radialModel
            {

            public:

                //- Runtime type information
                TypeName("LunSavage");


                // Constructors

                    //- Construct from components
                LunSavage(const dictionary& dict);


                //- Destructor
                virtual ~LunSavage();


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

#endif // !_LunSavageRadialTwoPhase_Header
