#pragma once
#ifndef _powerLawUniformBinary_Header
#define _powerLawUniformBinary_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::binaryBreakupModels::powerLawUniformBinary

Description
    Powerlaw kernel with a uniform daughter size distribution. Used for
    verification and validation of the binary breakup formulation implemented
    in the populationBalanceModel class.

SourceFiles
    powerLawUniformBinary.C

\*---------------------------------------------------------------------------*/

#include <binaryBreakupModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace binaryBreakupModels
        {

            /*---------------------------------------------------------------------------*\
                                Class powerLawUniformBinary Declaration
            \*---------------------------------------------------------------------------*/

            class powerLawUniformBinary
                :
                public binaryBreakupModel
            {
                // Private Data

                    //- Power
                scalar power_;


            public:

                //- Runtime type information
                TypeName("powerLawUniformBinary");

                // Constructor

                FoamReactingEulerFoamLibs_EXPORT powerLawUniformBinary
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~powerLawUniformBinary()
                {}


                // Member Functions

                    //- Add to binary breakupRate
                FoamReactingEulerFoamLibs_EXPORT virtual void addToBinaryBreakupRate
                (
                    volScalarField& binaryBreakupRate,
                    const label i,
                    const label j
                );
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace binaryBreakupModels
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_powerLawUniformBinary_Header
