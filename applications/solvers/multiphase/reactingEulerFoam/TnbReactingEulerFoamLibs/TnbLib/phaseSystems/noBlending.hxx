#pragma once
#ifndef _noBlending_Header
#define _noBlending_Header

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
    tnbLib::blendingMethods::noBlending

Description

SourceFiles
    noBlending.C

\*---------------------------------------------------------------------------*/

#include <blendingMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace blendingMethods
    {

        /*---------------------------------------------------------------------------*\
                                 Class noBlending Declaration
        \*---------------------------------------------------------------------------*/

        class noBlending
            :
            public blendingMethod
        {
            // Private Data

                //- Name of the continuous phase
            const word continuousPhase_;


        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from a dictionary and two phases
            noBlending
            (
                const dictionary& dict,
                const wordList& phaseNames
            );


            //- Destructor
            ~noBlending();


            // Member Functions

                //- Factor for primary phase
            virtual tmp<volScalarField> f1
            (
                const phaseModel& phase1,
                const phaseModel& phase2
            ) const;

            //- Factor for secondary phase
            virtual tmp<volScalarField> f2
            (
                const phaseModel& phase1,
                const phaseModel& phase2
            ) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace blendingMethods
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noBlending_Header
