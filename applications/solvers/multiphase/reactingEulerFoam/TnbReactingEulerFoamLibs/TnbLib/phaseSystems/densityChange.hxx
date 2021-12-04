#pragma once
#ifndef _densityChange_Header
#define _densityChange_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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
    tnbLib::diameterModels::driftModels::densityChangeDrift

Description
    Drift rate induced by changes in density.

SourceFiles
    densityChange.C

\*---------------------------------------------------------------------------*/

#include <driftModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace driftModels
        {

            /*---------------------------------------------------------------------------*\
                                 Class densityChangeDrift Declaration
            \*---------------------------------------------------------------------------*/

            class densityChangeDrift
                :
                public driftModel
            {
            public:

                //- Runtime type information
                TypeName("densityChange");

                // Constructor

                FoamReactingEulerFoamLibs_EXPORT densityChangeDrift
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~densityChangeDrift()
                {}


                // Member Functions

                    //- Add to driftRate
                FoamReactingEulerFoamLibs_EXPORT virtual void addToDriftRate
                (
                    volScalarField& driftRate,
                    const label i
                );
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace driftModels
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_densityChange_Header