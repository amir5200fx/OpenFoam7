#pragma once
#ifndef _turbulentDispersionModel_Header
#define _turbulentDispersionModel_Header

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
    tnbLib::turbulentDispersionModel

Description

SourceFiles
    turbulentDispersionModel.C
    newTurbulentDispersionModel.C

\*---------------------------------------------------------------------------*/

#include <phaseCompressibleTurbulenceModelFwd.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

namespace tnbLib
{

    class phasePair;

    /*---------------------------------------------------------------------------*\
                        Class turbulentDispersionModel Declaration
    \*---------------------------------------------------------------------------*/

    class turbulentDispersionModel
    {
    protected:

        // Protected data

            //- Phase pair
        const phasePair& pair_;


    public:

        //- Runtime type information
        TypeName("turbulentDispersionModel");


        // Declare runtime construction

        FoamReactingEulerFoamLibs_EXPORT declareRunTimeSelectionTable
        (
            autoPtr,
            turbulentDispersionModel,
            dictionary,
            (
                const dictionary& dict,
                const phasePair& pair
                ),
            (dict, pair)
        );

        // Static Data Members

            //- Diffusivity dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimD;

        //- Force dimensions
        static FoamReactingEulerFoamLibs_EXPORT const dimensionSet dimF;


        // Constructors

            //- Construct from a dictionary and a phase pair
        FoamReactingEulerFoamLibs_EXPORT turbulentDispersionModel
        (
            const dictionary& dict,
            const phasePair& pair
        );


        //- Destructor
        FoamReactingEulerFoamLibs_EXPORT virtual ~turbulentDispersionModel();


        // Selectors

        static FoamReactingEulerFoamLibs_EXPORT autoPtr<turbulentDispersionModel> New
        (
            const dictionary& dict,
            const phasePair& pair
        );


        // Member Functions

            //- Return a reference to the turbulence model for the continuous phase
        FoamReactingEulerFoamLibs_EXPORT const phaseCompressibleTurbulenceModel& continuousTurbulence() const;

        //- Turbulent diffusivity
        //  multiplying the gradient of the phase-fraction
        virtual tmp<volScalarField> D() const = 0;

        //- Turbulent dispersion force
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<volVectorField> F() const;

        //- Turbulent dispersion force on faces
        FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Ff() const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_turbulentDispersionModel_Header
