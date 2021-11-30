#pragma once
#ifndef _noWallDamping_Header
#define _noWallDamping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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
    tnbLib::wallDampingModels::noWallDamping

Description

SourceFiles
    noWallDamping.C

\*---------------------------------------------------------------------------*/

#include <wallDampingModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallDampingModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class noWallDamping Declaration
        \*---------------------------------------------------------------------------*/

        class noWallDamping
            :
            public wallDampingModel
        {
        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT noWallDamping
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~noWallDamping();


            // Member Functions

                //- Return damped coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> damp
            (
                const tmp<volScalarField>&
            ) const;

            //- Return damped force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> damp
            (
                const tmp<volVectorField>&
            ) const;

            //- Return damped face force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> damp
            (
                const tmp<surfaceScalarField>&
            ) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallDampingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noWallDamping_Header
