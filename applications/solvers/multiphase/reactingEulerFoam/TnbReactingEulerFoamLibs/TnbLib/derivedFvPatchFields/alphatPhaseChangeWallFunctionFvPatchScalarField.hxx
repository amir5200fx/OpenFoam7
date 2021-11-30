#pragma once
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
    tnbLib::compressible::alphatPhaseChangeWallFunctionFvPatchScalarField

Description
    Abstract base-class for all alphatWallFunctions supporting phase-change.

See also
    tnbLib::fixedValueFvPatchScalarField
    tnbLib::alphatWallFunctionFvPatchScalarField

SourceFiles
    alphatPhaseChangeWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <phasePairKey.hxx>

#include <fixedValueFvPatchFields.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace compressible
    {

        /*---------------------------------------------------------------------------*\
               Class alphatPhaseChangeWallFunctionFvPatchScalarField Declaration
        \*---------------------------------------------------------------------------*/

        class alphatPhaseChangeWallFunctionFvPatchScalarField
            :
            public fixedValueFvPatchScalarField
        {
        protected:

            // Protected data

                //- Rate of phase-change
            scalarField dmdt_;

            //- Latent heat of the phase-change
            scalarField mDotL_;


        public:

            //- Runtime type information
            TypeName("compressible::alphatPhaseChangeWallFunction");


            // Constructors

                //- Construct from patch and internal field
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&
            );

            //- Construct from patch, internal field and dictionary
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const dictionary&
            );

            //- Construct by mapping given
            //  alphatPhaseChangeWallFunctionFvPatchScalarField
            //  onto a new patch
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField&,
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const fvPatchFieldMapper&
            );

            //- Copy constructor
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField&
            );

            //- Copy constructor setting internal field reference
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField&,
                const DimensionedField<scalar, volMesh>&
            );


            // Member Functions

                //- Return the rate of phase-change
            virtual const scalarField& dmdt() const
            {
                return dmdt_;
            }

            //- Return the enthalpy source due to phase-change
            virtual const scalarField& mDotL() const
            {
                return mDotL_;
            }

            //- Is there phase change mass transfer for this phasePair
            virtual bool activePhasePair(const phasePairKey&) const
            {
                return false;
            }

            //- Return the rate of phase-change for specific phase pair
            virtual const scalarField& dmdt(const phasePairKey&) const
            {
                return dmdt_;
            }

            //- Return the rate of phase-change for specific phase pair
            virtual const scalarField& mDotL(const phasePairKey&) const
            {
                return mDotL_;
            }

            //- Return the rate of phase-change for specific phase
            virtual scalarField dmdt(const word&) const
            {
                return dmdt_;
            }

            //- Return the enthalpy source due to phase-change for specific phase
            virtual scalarField mDotL(const word&) const
            {
                return mDotL_;
            }

            // Evaluation functions

                //- Update the coefficients associated with the patch field
            virtual void updateCoeffs() = 0;


            // I-O

                //- Write
            FoamReactingEulerFoamLibs_EXPORT virtual void write(Ostream&) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace compressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //