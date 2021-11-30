#pragma once
#ifndef _orderedPhasePair_Header
#define _orderedPhasePair_Header

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
    tnbLib::orderedPhasePair

Description

SourceFiles
    orderedPhasePair.C

\*---------------------------------------------------------------------------*/

#include <phasePair.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class orderedPhasePair Declaration
    \*---------------------------------------------------------------------------*/

    class orderedPhasePair
        :
        public phasePair
    {

    public:

        // Constructors

            //- Construct from two phases and gravity
        FoamReactingEulerFoamLibs_EXPORT orderedPhasePair
        (
            const phaseModel& dispersed,
            const phaseModel& continuous
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~orderedPhasePair();


        // Member Functions

            //- Dispersed phase
        FoamReactingEulerFoamLibs_EXPORT virtual const phaseModel& dispersed() const;

        //- Continuous phase
        FoamReactingEulerFoamLibs_EXPORT virtual const phaseModel& continuous() const;

        //- Pair name
        FoamReactingEulerFoamLibs_EXPORT virtual word name() const;

        //- Other pair name
        FoamReactingEulerFoamLibs_EXPORT virtual word otherName() const;

        //- Aspect ratio
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> E() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_orderedPhasePair_Header
