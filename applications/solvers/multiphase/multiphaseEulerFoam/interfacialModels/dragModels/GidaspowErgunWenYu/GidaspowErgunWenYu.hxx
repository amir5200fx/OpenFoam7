#pragma once
#ifndef _GidaspowErgunWenYu_Header
#define _GidaspowErgunWenYu_Header

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
    tnbLib::dragModels::GidaspowErgunWenYu

Description
    D. Gidaspow, Multiphase flow and fluidization,
        Academic Press, New York, 1994.

SourceFiles
    GidaspowErgunWenYu.C

\*---------------------------------------------------------------------------*/

#include "dragModel.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class GidaspowErgunWenYu Declaration
        \*---------------------------------------------------------------------------*/

        class GidaspowErgunWenYu
            :
            public dragModel
        {

        public:

            //- Runtime type information
            TypeName("GidaspowErgunWenYu");


            // Constructors

                //- Construct from components
            GidaspowErgunWenYu
            (
                const dictionary& interfaceDict,
                const phaseModel& phase1,
                const phaseModel& phase2
            );


            //- Destructor
            virtual ~GidaspowErgunWenYu();


            // Member Functions

            tmp<volScalarField> K(const volScalarField& Ur) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GidaspowErgunWenYu_Header
