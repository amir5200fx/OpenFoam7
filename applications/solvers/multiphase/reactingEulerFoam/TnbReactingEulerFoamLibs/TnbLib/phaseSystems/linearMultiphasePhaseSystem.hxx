#pragma once
#ifndef _linearMultiphasePhaseSystem_Header
#define _linearMultiphasePhaseSystem_Header

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
    tnbLib::blendingMethods::linear

Description

SourceFiles
    linear.C

\*---------------------------------------------------------------------------*/

#include <blendingMethod.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace blendingMethods
    {

        /*---------------------------------------------------------------------------*\
                                 Class linear Declaration
        \*---------------------------------------------------------------------------*/

        class linear
            :
            public blendingMethod
        {
            // Private Data

                //- Minimum fraction of phases which can be considered fully continuous
            HashTable<dimensionedScalar, word, word::hash>
                minFullyContinuousAlpha_;

            //- Minimum fraction of phases which can be considered partly continuous
            HashTable<dimensionedScalar, word, word::hash>
                minPartlyContinuousAlpha_;


        public:

            //- Runtime type information
            TypeName("linear");


            // Constructors

                //- Construct from a dictionary and two phases
            FoamReactingEulerFoamLibs_EXPORT linear
            (
                const dictionary& dict,
                const wordList& phaseNames
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT ~linear();


            // Member Functions

                //- Factor for primary phase
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> f1
            (
                const phaseModel& phase1,
                const phaseModel& phase2
            ) const;

            //- Factor for secondary phase
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> f2
            (
                const phaseModel& phase1,
                const phaseModel& phase2
            ) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace blendingMethods
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearMultiphasePhaseSystem_Header