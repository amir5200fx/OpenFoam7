#pragma once
#ifndef _liftModel_Header
#define _liftModel_Header

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
    tnbLib::liftModel

Description

SourceFiles
    liftModel.C
    newLiftModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                               Class liftModel Declaration
    \*---------------------------------------------------------------------------*/

    class liftModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("liftModel");


        // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            liftModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Static Data Members

            //- Force dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimF;


        // Constructors

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT liftModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~liftModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<liftModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Return lift coefficient
        virtual tmp<volScalarField> Cl() const = 0;

        //- Return phase-intensive lift force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> Fi() const;

        //- Return lift force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> F() const;

        //- Return face lift force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Ff() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_liftModel_Header
