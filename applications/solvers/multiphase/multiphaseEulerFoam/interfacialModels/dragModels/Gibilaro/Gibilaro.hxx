#pragma once
#ifndef _Gibilaro_Header
#define _Gibilaro_Header

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
    tnbLib::dragModels::Gibilaro

Description
    H, Enwald, E. Peirano, A-E Almstedt
    'Eulerian Two-Phase Flow Theory Applied to Fluidization'
    Int. J. Multiphase Flow, Vol. 22, Suppl, pp. 21-66 (1996)
    Eq. 106, p. 43

SourceFiles
    Gibilaro.C

\*---------------------------------------------------------------------------*/

#include "dragModel.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class Gibilaro Declaration
        \*---------------------------------------------------------------------------*/

        class Gibilaro
            :
            public dragModel
        {

        public:

            //- Runtime type information
            TypeName("Gibilaro");


            // Constructors

                //- Construct from components
            Gibilaro
            (
                const dictionary& interfaceDict,
                const phaseModel& phase1,
                const phaseModel& phase2
            );


            //- Destructor
            virtual ~Gibilaro();


            // Member Functions

            tmp<volScalarField> K(const volScalarField& Ur) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Gibilaro_Header
