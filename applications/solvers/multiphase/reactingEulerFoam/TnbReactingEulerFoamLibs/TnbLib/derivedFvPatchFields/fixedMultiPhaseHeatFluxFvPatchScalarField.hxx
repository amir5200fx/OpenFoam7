#pragma once
#ifndef _fixedMultiPhaseHeatFluxFvPatchScalarField_Header
#define _fixedMultiPhaseHeatFluxFvPatchScalarField_Header

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
    tnbLib::fixedMultiPhaseHeatFluxFvPatchScalarField

Description
    Calculates a wall temperature that produces the specified overall wall heat
    flux across all the phases in an Eulerian multi-phase simulation.

    Intended to be used with copiedFixedValue to ensure that phase wall
    temperature are consistent:
        - Set 'fixedMultiPhaseHeatFlux' boundary for one of the phases
        - Use 'copiedFixedValue' for all the other phases.

See also
    tnbLib::fixedValueFvPatchField

SourceFiles
    fixedMultiPhaseHeatFluxFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                Class fixedMultiPhaseHeatFluxFvPatchScalarField Declaration
    \*---------------------------------------------------------------------------*/

    class fixedMultiPhaseHeatFluxFvPatchScalarField
        :
        public fixedValueFvPatchScalarField
    {
        // Private Data

            //- Heat power [W] or flux [W/m^2]
        scalarField q_;

        //- Relaxation factor
        scalar relax_;

        //- Minimum temperature limit [K]
        scalar Tmin_;


    public:

        //- Runtime type information
        TypeName("fixedMultiPhaseHeatFlux");


        // Constructors

            //- Construct from patch and internal field
        FoamReactingEulerFoamLibs_EXPORT fixedMultiPhaseHeatFluxFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        FoamReactingEulerFoamLibs_EXPORT fixedMultiPhaseHeatFluxFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  fixedMultiPhaseHeatFluxFvPatchScalarField
        //  onto a new patch
        FoamReactingEulerFoamLibs_EXPORT fixedMultiPhaseHeatFluxFvPatchScalarField
        (
            const fixedMultiPhaseHeatFluxFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Copy constructor
        FoamReactingEulerFoamLibs_EXPORT fixedMultiPhaseHeatFluxFvPatchScalarField
        (
            const fixedMultiPhaseHeatFluxFvPatchScalarField&
        );

        //- Copy constructor setting internal field reference
        FoamReactingEulerFoamLibs_EXPORT fixedMultiPhaseHeatFluxFvPatchScalarField
        (
            const fixedMultiPhaseHeatFluxFvPatchScalarField&,
            const DimensionedField<scalar, volMesh>&
        );


        // Member Functions

            // Evaluation functions

                //- Update the coefficients associated with the patch field
        FoamReactingEulerFoamLibs_EXPORT virtual void updateCoeffs();


        // I-O

            //- Write
        FoamReactingEulerFoamLibs_EXPORT virtual void write(Ostream&) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedMultiPhaseHeatFluxFvPatchScalarField_Header
