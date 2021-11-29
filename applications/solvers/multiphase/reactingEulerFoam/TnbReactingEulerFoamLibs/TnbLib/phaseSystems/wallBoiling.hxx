#pragma once
#ifndef _wallBoiling_Header
#define _wallBoiling_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::nucleationModels::wallBoiling

Description
    Wall-boiling model which requires a velocityGroup (i.e. phase) to be
    specified in which the nucleation occurs. This setting must be consistent
    with the specifications in the alphatWallBoilingWallFunction. If the
    departure-diameter lies outside the diameter-range given by the sizeGroups
    of the corresponding velocityGroup, the solver will give a warning and the
    nucleation rate will be set to zero.

SourceFiles
    wallBoiling.C

\*---------------------------------------------------------------------------*/

#include <nucleationModel.hxx>
#include <phaseCompressibleTurbulenceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace nucleationModels
        {

            /*---------------------------------------------------------------------------*\
                                     Class wallBoiling Declaration
            \*---------------------------------------------------------------------------*/

            class wallBoiling
                :
                public nucleationModel
            {
                // Private Data

                    //- Velocity group in which the nucleation occurs
                const velocityGroup& velGroup_;

                //- Pointer to turbulence model
                const phaseCompressibleTurbulenceModel& turbulence_;


            public:

                //- Runtime type information
                TypeName("wallBoiling");

                // Constructor

                wallBoiling
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~wallBoiling()
                {}


                // Member Functions

                    //- Correct diameter independent expressions
                virtual void correct();

                //- Add to nucleationRate
                virtual void addToNucleationRate
                (
                    volScalarField& nucleationRate,
                    const label i
                );
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace nucleationModels
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallBoiling_Header
