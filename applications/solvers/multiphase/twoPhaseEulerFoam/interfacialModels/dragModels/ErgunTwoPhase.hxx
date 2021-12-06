#pragma once
#ifndef _ErgunTwoPhase_Header
#define _ErgunTwoPhase_Header

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
    tnbLib::dragModels::Ergun

Description
    H, Enwald, E. Peirano, A-E Almstedt
    'Eulerian Two-Phase Flow Theory Applied to Fluidization'
    Int. J. Multiphase Flow, Vol. 22, Suppl, pp. 21-66 (1996)
    Eq. 104, p. 42

SourceFiles
    Ergun.C

\*---------------------------------------------------------------------------*/

#include "dragModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class Ergun Declaration
        \*---------------------------------------------------------------------------*/

        class Ergun
            :
            public dragModel
        {
        public:

            //- Runtime type information
            TypeName("Ergun");


            // Constructors

                //- Construct from a dictionary and a phase pair
            Ergun
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            virtual ~Ergun();


            // Member Functions

                //- Drag coefficient
            virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ErgunTwoPhase_Header
