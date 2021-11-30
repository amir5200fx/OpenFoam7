#pragma once
#ifndef _blendingMethod_Header
#define _blendingMethod_Header

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
    tnbLib::blendingMethod

Description

SourceFiles
    blendingMethod.C

\*---------------------------------------------------------------------------*/

#include <phaseModel.hxx>

#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class blendingMethod Declaration
    \*---------------------------------------------------------------------------*/

    class blendingMethod
    {
    public:

        //- Runtime type information
        TypeName("blendingMethod");


        // Declare runtime construction
        FoamReactingEulerFoamLibs_EXPORT declareRunTimeSelectionTable
        (
            autoPtr,
            blendingMethod,
            dictionary,
            (
                const dictionary& dict,
                const wordList& phaseNames
                ),
            (dict, phaseNames)
        );


        // Constructors

            //- Construct from a dictionary
        FoamReactingEulerFoamLibs_EXPORT blendingMethod
        (
            const dictionary& dict
        );


        // Selector

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<blendingMethod> New
        (
            const word& modelName,
            const dictionary& dict,
            const wordList& phaseNames
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~blendingMethod();


        // Member Functions

            //- Factor for first phase
        virtual tmp<volScalarField> f1
        (
            const phaseModel& phase1,
            const phaseModel& phase2
        ) const = 0;

        //- Factor for second phase
        virtual tmp<volScalarField> f2
        (
            const phaseModel& phase1,
            const phaseModel& phase2
        ) const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blendingMethod_Header
