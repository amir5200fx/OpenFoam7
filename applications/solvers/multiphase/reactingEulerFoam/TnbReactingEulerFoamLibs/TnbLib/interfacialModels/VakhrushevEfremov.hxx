#pragma once
#ifndef _VakhrushevEfremov_Header
#define _VakhrushevEfremov_Header

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
    tnbLib::aspectRatioModels::VakhrushevEfremov

Description
    Aspect ratio model of Vakhrushev and Efremov.

    Reference:
    \verbatim
        Vakhrushev, I. A., & Efremov, G. I. (1970).
        Interpolation formula for computing the velocities of single gas bubbles
        in liquids.
        Chemistry and Technology of Fuels and Oils, 6(5), 376-379.
    \endverbatim

SourceFiles
    VakhrushevEfremov.C

\*---------------------------------------------------------------------------*/

#include <aspectRatioModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace aspectRatioModels
    {

        /*---------------------------------------------------------------------------*\
                               Class VakhrushevEfremov Declaration
        \*---------------------------------------------------------------------------*/

        class VakhrushevEfremov
            :
            public aspectRatioModel
        {
        public:

            //- Runtime type information
            TypeName("VakhrushevEfremov");


            // Constructors

                //- Construct from a dictionary and an ordered phase pair
            VakhrushevEfremov
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~VakhrushevEfremov();


            // Member Functions

                //- Aspect ratio
            virtual tmp<volScalarField> E() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace aspectRatioModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_VakhrushevEfremov_Header
