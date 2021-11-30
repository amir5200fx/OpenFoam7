#pragma once
#ifndef _interfaceCompositionModel_Header
#define _interfaceCompositionModel_Header

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
    tnbLib::interfaceCompositionModel

Description
    Generic base class for interface composition models. These models describe
    the composition in phase 1 of the supplied pair at the interface with phase
    2.

SourceFiles
    interfaceCompositionModel.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <hashedWordList.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phaseModel;
    class phasePair;

    /*---------------------------------------------------------------------------*\
                            Class interfaceCompositionModel Declaration
    \*---------------------------------------------------------------------------*/

    class interfaceCompositionModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;

        //- Names of the transferring species
        const hashedWordList speciesNames_;


    public:

        //- Runtime type information
        TypeName("interfaceCompositionModel");


        // Declare runtime construction

        FoamReactingEulerFoamLibs_EXPORT declareRunTimeSelectionTable
        (
            autoPtr,
            interfaceCompositionModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );


        // Constructors

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT interfaceCompositionModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~interfaceCompositionModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<interfaceCompositionModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Update the composition
        virtual void update(const volScalarField& Tf) = 0;

        //- Return the transferring species names
        FoamReactingEulerFoamLibs_EXPORT const hashedWordList& species() const;

        //- Returns whether the species is transported by the model and
        //  provides the name of the diffused species
        FoamReactingEulerFoamLibs_EXPORT bool transports
        (
            word& speciesName
        ) const;

        //- Interface mass fraction
        virtual tmp<volScalarField> Yf
        (
            const word& speciesName,
            const volScalarField& Tf
        ) const = 0;

        //- The interface mass fraction derivative w.r.t. temperature
        virtual tmp<volScalarField> YfPrime
        (
            const word& speciesName,
            const volScalarField& Tf
        ) const = 0;

        //- Mass fraction difference between the interface and the field
        virtual tmp<volScalarField> dY
        (
            const word& speciesName,
            const volScalarField& Tf
        ) const = 0;

        //- Mass diffusivity
        virtual tmp<volScalarField> D
        (
            const word& speciesName
        ) const = 0;

        //- Latent heat
        virtual tmp<volScalarField> L
        (
            const word& speciesName,
            const volScalarField& Tf
        ) const = 0;

        //- Add latent heat flow rate to total
        virtual void addMDotL
        (
            const volScalarField& K,
            const volScalarField& Tf,
            volScalarField& mDotL,
            volScalarField& mDotLPrime
        ) const = 0;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interfaceCompositionModel_Header
