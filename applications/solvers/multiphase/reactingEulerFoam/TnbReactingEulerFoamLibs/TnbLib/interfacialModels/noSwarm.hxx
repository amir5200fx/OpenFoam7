#pragma once
#ifndef _noSwarm_Header
#define _noSwarm_Header

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
    tnbLib::swarmCorrections::noSwarm

Description

SourceFiles
    noSwarm.C

\*---------------------------------------------------------------------------*/

#include <swarmCorrection.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace swarmCorrections
    {

        /*---------------------------------------------------------------------------*\
                                   Class noSwarm Declaration
        \*---------------------------------------------------------------------------*/

        class noSwarm
            :
            public swarmCorrection
        {
        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from a dictionary and a phase pair
            noSwarm
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~noSwarm();


            // Member Functions

                //- Swarm correction coefficient
            tmp<volScalarField> Cs() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace swarmCorrections
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noSwarm_Header
