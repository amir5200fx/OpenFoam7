#pragma once
#ifndef _constantDiameterTwoPhase_Header
#define _constantDiameterTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
    tnbLib::diameterModels::constant

Description
    Constant dispersed-phase particle diameter model.

SourceFiles
    constantTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "diameterModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class constant Declaration
        \*---------------------------------------------------------------------------*/

        class constant
            :
            public diameterModel
        {
            // Private Data

                //- The constant diameter of the phase
            dimensionedScalar d_;


        public:

            //- Runtime type information
            TypeName("constant");


            // Constructors

                //- Construct from components
            constant
            (
                const dictionary& diameterProperties,
                const phaseModel& phase
            );


            //- Destructor
            virtual ~constant();


            // Member Functions

                //- Return the diameter as a field
            virtual tmp<volScalarField> d() const;

            //- Read diameterProperties dictionary
            virtual bool read(const dictionary& diameterProperties);
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace diameterModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantDiameterTwoPhase_Header
