#pragma once
#ifndef _massTransferModel_Header
#define _massTransferModel_Header

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
    tnbLib::massTransferModel

Description

SourceFiles
    massTransferModel.C

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                            Class massTransferModel Declaration
    \*---------------------------------------------------------------------------*/

    class massTransferModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("massTransferModel");


        // Declare runtime construction

        declareRunTimeSelectionTable
        (
            autoPtr,
            massTransferModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Static Data Members

            //- Coefficient dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimK;


        // Constructors

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT massTransferModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~massTransferModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<massTransferModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- The implicit mass transfer coefficient
            //  Note: this has had the species mass diffusivity factored out
        virtual tmp<volScalarField> K() const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_massTransferModel_Header