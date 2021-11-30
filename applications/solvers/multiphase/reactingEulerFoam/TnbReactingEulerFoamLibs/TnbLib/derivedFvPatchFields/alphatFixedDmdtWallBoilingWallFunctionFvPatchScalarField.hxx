#pragma once
#ifndef _alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField_Header
#define _alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField_Header

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
    tnbLib::compressible::
        alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField

Description
    A simple alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField with
    a fixed volumetric phase-change mass flux.

See also
    tnbLib::compressible::
        alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField

SourceFiles
    alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace compressible
    {

        /*---------------------------------------------------------------------------*\
           Class alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField Declaration
        \*---------------------------------------------------------------------------*/

        class alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            :
            public alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
        {
            // Private Data

                //- name on the phase
            word vaporPhaseName_;

            //- dmdt relaxationFactor
            scalar relax_;

            //- Volumetric phase-change mass flux in near wall cells
            scalar fixedDmdt_;

            //- Latent heat
            scalar L_;


        public:

            //- Runtime type information
            TypeName("compressible::alphatFixedDmdtWallBoilingWallFunction");


            // Constructors

                //- Construct from patch and internal field
            FoamReactingEulerFoamLibs_EXPORT alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&
            );

            //- Construct from patch, internal field and dictionary
            FoamReactingEulerFoamLibs_EXPORT alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const dictionary&
            );

            //- Construct by mapping given
            //  alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            //  onto a new patch
            FoamReactingEulerFoamLibs_EXPORT alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField&,
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const fvPatchFieldMapper&
            );

            //- Copy constructor
            FoamReactingEulerFoamLibs_EXPORT alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField&
            );

            //- Construct and return a clone
            virtual tmp<fvPatchScalarField> clone() const
            {
                return tmp<fvPatchScalarField>
                    (
                        new alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
                        (
                            *this
                        )
                        );
            }

            //- Copy constructor setting internal field reference
            FoamReactingEulerFoamLibs_EXPORT alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField&,
                const DimensionedField<scalar, volMesh>&
            );

            //- Construct and return a clone setting internal field reference
            virtual tmp<fvPatchScalarField> clone
            (
                const DimensionedField<scalar, volMesh>& iF
            ) const
            {
                return tmp<fvPatchScalarField>
                    (
                        new alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField
                        (
                            *this,
                            iF
                        )
                        );
            }


            // Member Functions

                //- Is there phase change mass transfer for this phasePair
            FoamReactingEulerFoamLibs_EXPORT virtual bool activePhasePair(const phasePairKey&) const;

            //- Return the rate of phase-change for specific phase pair
            FoamReactingEulerFoamLibs_EXPORT virtual const scalarField& dmdt(const phasePairKey&) const;

            //- Return the rate of phase-change for specific phase pair
            FoamReactingEulerFoamLibs_EXPORT virtual const scalarField& mDotL(const phasePairKey&) const;

            // Evaluation functions

                //- Update the coefficients associated with the patch field
            FoamReactingEulerFoamLibs_EXPORT virtual void updateCoeffs();


            // I-O

                //- Write
            FoamReactingEulerFoamLibs_EXPORT virtual void write(Ostream&) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace compressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_alphatFixedDmdtWallBoilingWallFunctionFvPatchScalarField_Header
