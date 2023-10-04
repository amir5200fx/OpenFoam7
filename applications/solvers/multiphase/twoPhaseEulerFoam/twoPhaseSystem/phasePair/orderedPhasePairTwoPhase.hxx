#pragma once
#ifndef _orderedPhasePairTwoPhase_Header
#define _orderedPhasePairTwoPhase_Header

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
    tnbLib::orderedPhasePair

Description

SourceFiles
    orderedPhasePairTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "phasePairTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class aspectRatioModel;

    /*---------------------------------------------------------------------------*\
                             Class orderedPhasePair Declaration
    \*---------------------------------------------------------------------------*/

    class orderedPhasePair
        :
        public phasePair
    {
        // Private Data

            //- Aspect ratio model
        autoPtr<aspectRatioModel> aspectRatio_;


    public:

        // Constructors

            //- Construct from two phases, gravity, surface tension and aspect
            //  ratio tables
        orderedPhasePair
        (
            const phaseModel& dispersed,
            const phaseModel& continuous,
            const dimensionedVector& g,
            const scalarTable& sigmaTable,
            const dictTable& aspectRatioTable
        );


        //- Destructor
        virtual ~orderedPhasePair();


        // Member Functions

            //- Dispersed phase
        virtual const phaseModel& dispersed() const;

        //- Continuous phase
        virtual const phaseModel& continuous() const;

        //- Pair name
        virtual word name() const;

        //- Aspect ratio
        virtual tmp<volScalarField> E() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_orderedPhasePairTwoPhase_Header