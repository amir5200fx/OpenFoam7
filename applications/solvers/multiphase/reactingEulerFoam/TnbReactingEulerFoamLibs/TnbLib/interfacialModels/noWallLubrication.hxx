#pragma once
#ifndef _noWallLubrication_Header
#define _noWallLubrication_Header

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
    tnbLib::wallLubricationModels::noWallLubrication

Description

SourceFiles
    noWallLubrication.C

\*---------------------------------------------------------------------------*/

#include <wallLubricationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallLubricationModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class noWallLubrication Declaration
        \*---------------------------------------------------------------------------*/

        class noWallLubrication
            :
            public wallLubricationModel
        {
        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT noWallLubrication
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~noWallLubrication();


            // Member Functions

                //- Return phase-intensive wall lubrication force
            FoamReactingEulerFoamLibs_EXPORT tmp<volVectorField> Fi() const;

            //- Wall lubrication force
            FoamReactingEulerFoamLibs_EXPORT tmp<volVectorField> F() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallLubricationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noWallLubrication_Header
