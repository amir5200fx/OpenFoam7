#pragma once
#ifndef _TomiyamaAspectRatioTwoPhase_Header
#define _TomiyamaAspectRatioTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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
    tnbLib::aspectRatioModels::TomiyamaAspectRatio

Description
    Aspect ratio model of Tomiyama.

    Reference:
    \verbatim
        "Implementation and Comparison of Correlations for interfacial Forces
        in a Gas-Liquid System within an Euler-Euler Framework"
        Otromke, M.,
        PhD Thesis, April 2013
    \endverbatim

SourceFiles
    TomiyamaAspectRatio.C

\*---------------------------------------------------------------------------*/

#include "VakhrushevEfremovTwoPhase.hxx"
#include "wallDependentModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace aspectRatioModels
    {

        /*---------------------------------------------------------------------------*\
                               Class TomiyamaAspectRatio Declaration
        \*---------------------------------------------------------------------------*/

        class TomiyamaAspectRatio
            :
            public VakhrushevEfremov,
            public wallDependentModel
        {
        public:

            //- Runtime type information
            TypeName("Tomiyama");


            // Constructors

                //- Construct from a dictionary and an ordered phase pair
            TomiyamaAspectRatio
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~TomiyamaAspectRatio();


            // Member Functions

                //- Aspect ratio
            virtual tmp<volScalarField> E() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace aspectRatioModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaAspectRatioTwoPhase_Header
