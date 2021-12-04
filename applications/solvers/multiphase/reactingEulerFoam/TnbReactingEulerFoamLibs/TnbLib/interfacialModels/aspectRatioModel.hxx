#pragma once
#ifndef _aspectRatioModel_Header
#define _aspectRatioModel_Header

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
    tnbLib::aspectRatioModel

Description

SourceFiles
    aspectRatioModel.C
    newAspectRatioModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                               Class aspectRatioModel Declaration
    \*---------------------------------------------------------------------------*/

    class aspectRatioModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("aspectRatioModel");


        // Declare runtime construction
        declareRunTimeSelectionTable
        (
            autoPtr,
            aspectRatioModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Constructors

            //- Construct from a dictionary and an ordered phase pair
        FoamReactingEulerFoamLibs_EXPORT aspectRatioModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~aspectRatioModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<aspectRatioModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Aspect ratio
        virtual tmp<volScalarField> E() const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_aspectRatioModel_Header
