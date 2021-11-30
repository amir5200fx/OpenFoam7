#pragma once
#ifndef _wallDampedLift_Header
#define _wallDampedLift_Header

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
    tnbLib::liftModels::wallDamped

Description

SourceFiles
    wallDamped.C

\*---------------------------------------------------------------------------*/

#include <liftModel.hxx>
#include <wallDampingModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace liftModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class wallDamped Declaration
        \*---------------------------------------------------------------------------*/

        class wallDamped
            :
            public liftModel
        {
            // Private Data

                //- The lift model to damp
            autoPtr<liftModel> liftModel_;

            //- The wall-damping model
            autoPtr<wallDampingModel> wallDampingModel_;


        public:

            //- Runtime type information
            TypeName("wallDamped");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT wallDamped
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~wallDamped();


            // Member Functions

                //- Return lift coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Cl() const;

            //- Return phase-intensive lift force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> Fi() const;

            //- Return lift force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> F() const;

            //- Return face lift force
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Ff() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace liftModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallDampedLift_Header
