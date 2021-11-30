#pragma once
#ifndef _noLift_Header
#define _noLift_Header

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
    tnbLib::liftModels::noLift

Description

SourceFiles
    noLift.C

\*---------------------------------------------------------------------------*/

#include <liftModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace liftModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class noLift Declaration
        \*---------------------------------------------------------------------------*/

        class noLift
            :
            public liftModel
        {
        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT noLift
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~noLift();


            // Member Functions

                //- Lift coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Cl() const;

            //- Lift force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> F() const;

            //- Lift force on faces
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Ff() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace liftModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_noLift_Header
