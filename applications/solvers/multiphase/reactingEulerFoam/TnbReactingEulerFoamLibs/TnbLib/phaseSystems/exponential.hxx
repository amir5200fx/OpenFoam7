#pragma once
#ifndef _exponential_Header
#define _exponential_Header

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
    tnbLib::diameterModels::breakupModels::exponential

Description
    Exponential kernel. Used for verification and validation of the breakup
    formulation implemented in the populationBalanceModel class.

SourceFiles
    exponential.C

\*---------------------------------------------------------------------------*/

#include <breakupModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace breakupModels
        {

            /*---------------------------------------------------------------------------*\
                                     Class exponential Declaration
            \*---------------------------------------------------------------------------*/

            class exponential
                :
                public breakupModel
            {
                // Private Data

                    //- Exponent
                scalar exponent_;

                //- Coefficient
                scalar C_;


            public:

                //- Runtime type information
                TypeName("exponential");

                // Constructor

                exponential
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~exponential()
                {}


                // Member Functions

                    //- Set total breakupRate
                virtual void setBreakupRate
                (
                    volScalarField& breakupRate,
                    const label i
                );
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace breakupModels
    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_exponential_Header
