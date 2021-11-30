#pragma once
#ifndef _wallLubricationModel_Header
#define _wallLubricationModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::wallLubricationModel

Description

SourceFiles
    wallLubricationModel.C
    newWallLubricationModel.C

\*---------------------------------------------------------------------------*/

#include <wallDependentModel.hxx>
#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                          Class wallLubricationModel Declaration
    \*---------------------------------------------------------------------------*/

    class wallLubricationModel
        :
        public wallDependentModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


        // Protected member functions

            //- Zero-gradient wall-lubrication force at walls
        FoamReactingEulerFoamLibs_EXPORT tmp<volVectorField> zeroGradWalls(tmp<volVectorField>) const;


    public:

        //- Runtime type information
        TypeName("wallLubricationModel");


        // Declare runtime construction

        FoamReactingEulerFoamLibs_EXPORT declareRunTimeSelectionTable
        (
            autoPtr,
            wallLubricationModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Static Data Members

            //- Coefficient dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimF;


        // Constructors

            //- Construct from components
        FoamReactingEulerFoamLibs_EXPORT wallLubricationModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~wallLubricationModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<wallLubricationModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Return phase-intensive wall lubrication force
        virtual tmp<volVectorField> Fi() const = 0;

        //- Return wall lubrication force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> F() const;

        //- Return face wall lubrication force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Ff() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallLubricationModel_Header
