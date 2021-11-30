#pragma once
#ifndef _linearWallDamping_Header
#define _linearWallDamping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
    tnbLib::wallDampingModels::linear

Description

SourceFiles
    linearWallDamping.C

\*---------------------------------------------------------------------------*/

#include <interpolatedWallDamping.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallDampingModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class linear Declaration
        \*---------------------------------------------------------------------------*/

        class linear
            :
            public interpolated
        {
            // Private Data

                //- Diameter coefficient
            const dimensionedScalar Cd_;


        protected:

            // Protected member functions

                //- Return the force limiter field
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> limiter() const;


        public:

            //- Runtime type information
            TypeName("linear");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT linear
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~linear();
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallDampingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearWallDamping_Header
