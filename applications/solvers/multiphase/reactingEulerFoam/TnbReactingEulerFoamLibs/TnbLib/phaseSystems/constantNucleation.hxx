#pragma once
#ifndef _constantNucleation_Header
#define _constantNucleation_Header

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
    tnbLib::diameterModels::nucleationModels::constantNucleation

Description
    Constant nucleation rate within all classes. Used for verification and
    validation of the nucleation formulation implemented in the
    populationBalanceModel class. Rate is calculated from fvOptions mass source.

SourceFiles
    constant.C

\*---------------------------------------------------------------------------*/

#include <nucleationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace nucleationModels
        {

            /*---------------------------------------------------------------------------*\
                                 Class constantNucleation Declaration
            \*---------------------------------------------------------------------------*/

            class constantNucleation
                :
                public nucleationModel
            {
                // Private Data

                    //- Departure diameter
                dimensionedScalar d_;

                //- Velocity group in which the nucleation occurs
                const velocityGroup& velGroup_;


            public:

                //- Runtime type information
                TypeName("constant");

                // Constructor

                constantNucleation
                (
                    const populationBalanceModel& popBal,
                    const dictionary& dict
                );


                //- Destructor
                virtual ~constantNucleation()
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

#endif // !_constantNucleation_Header
