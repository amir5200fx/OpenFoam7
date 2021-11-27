#pragma once
#ifndef _alphatWallBoilingWallFunctionFvPatchScalarField_Header
#define _alphatWallBoilingWallFunctionFvPatchScalarField_Header

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
    tnbLib::compressible::alphatWallBoilingWallFunctionFvPatchScalarField

Description
    A thermal wall function for simulation of subcooled nucleate wall boiling
    with runtime selctable submodels for:
      - wall heat flux partitioning model
      - nucleation site density
      - bubble departure frequency
      - bubble departure diameter

    Implements a version of the well-known RPI wall boiling model
    (Kurul & Podowski, 1991). The model implementation is similar to the model
    described by Peltola & P�ttikangas (2012) but has been extended with the
    wall heat flux partitioning models.

    References:
    \verbatim
        Kurul, N., & Podowski, M.Z. (1991).
        On the modeling of multidimensional effects in boiling channels.
        ANS. Proc. National Heat Transfer Con. Minneapolis, Minnesota, USA,
        1991.
        ISBN: 0-89448-162-1, pp. 30-40.
    \endverbatim

    \verbatim
        Peltola, J., & P�ttikangas, T.J.H. (2012).
        Development and validation of a boiling model for OpenFOAM multiphase
        solver.
        CFD4NRS-4 Conference Proceedings, Daejeon, Korea, 2012.
        paper 59.
    \endverbatim

Usage
    \table
        Property     | Description             | Required    | Default value
        phaseType    | 'vapor' or 'liquid'     | yes         |
        relax        |wall boiling model relaxation| yes     |
        Prt          | inherited from alphatPhaseChangeJayatillekeWallFunction
        Cmu          | inherited from alphatPhaseChangeJayatillekeWallFunction
        kappa        | inherited from alphatPhaseChangeJayatillekeWallFunction
        E            | inherited from alphatPhaseChangeJayatillekeWallFunction
        dmdt         | phase change mass flux  | yes         |
        value        | initial alphat value    | yes         |

        if phaseType 'vapor':

        partitioningModel|                     | yes         |

        if phaseType 'liquid':

        partitioningModel|                     | yes         |
        nucleationSiteModel|                     | yes         |
        departureDiamModel|                     | yes         |
        departureFreqModel|                     | yes         |
    \endtable

    NOTE: Runtime selectabale submodels may require model specific entries

    Example usage:
    \verbatim
    hotWall
    {
        type            compressible::alphatWallBoiling2WallFunction;
        phaseType       liquid;
        Prt             0.85;
        Cmu             0.09;
        kappa           0.41;
        E               9.8;
        relax           0.001;
        dmdt            uniform 0;
        partitioningModel
        {
            type        Lavieville;
            alphaCrit   0.2;
        }
        nucleationSiteModel
        {
            type        LemmertChawla;
        }
        departureDiamModel
        {
            type        TolubinskiKostanchuk;
        }
        departureFreqModel
        {
            type        Cole;
        }
        value           uniform 0.01;
    \endverbatim

See also
    tnbLib::alphatPhaseChangeJayatillekeWallFunctionFvPatchField

SourceFiles
    alphatWallBoilingWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField.hxx>
#include <partitioningModel.hxx>
#include <nucleationSiteModel.hxx>
#include <departureDiameterModel.hxx>
#include <departureFrequencyModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace compressible
    {

        /*---------------------------------------------------------------------------*\
                    Class alphatWallBoilingWallFunctionFvPatchScalarField Declaration
        \*---------------------------------------------------------------------------*/

        class alphatWallBoilingWallFunctionFvPatchScalarField
            :
            public alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
        {
        public:

            // Data types

                //- Enumeration listing the possible operational modes
            enum phaseType
            {
                vaporPhase,
                liquidPhase
            };


        private:

            // Private Data

                //- name of the other phase (vapor/liquid phase)
            word otherPhaseName_;

            //- Heat source type names
            static const NamedEnum<phaseType, 2> phaseTypeNames_;

            //- Heat source type
            phaseType phaseType_;

            //- dmdt relaxationFactor
            scalar relax_;

            //- Patch face area by cell volume
            scalarField AbyV_;

            //- Convective turbulent thermal diffusivity
            scalarField alphatConv_;

            //- Departure diameter field
            scalarField dDep_;

            //- Quenching surface heat flux
            scalarField qq_;

            //- Run-time selected heat flux partitioning model
            autoPtr<wallBoilingModels::partitioningModel>
                partitioningModel_;

            //- Run-time selected nucleation site density model
            autoPtr<wallBoilingModels::nucleationSiteModel>
                nucleationSiteModel_;

            //- Run-time selected bubble departure diameter model
            autoPtr<wallBoilingModels::departureDiameterModel>
                departureDiamModel_;

            //- Run-time selected bubble departure frequency model
            autoPtr<wallBoilingModels::departureFrequencyModel>
                departureFreqModel_;


        public:

            //- Runtime type information
            TypeName("compressible::alphatWallBoilingWallFunction");


            // Constructors

                //- Construct from patch and internal field
            alphatWallBoilingWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&
            );

            //- Construct from patch, internal field and dictionary
            alphatWallBoilingWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const dictionary&
            );

            //- Construct by mapping given
            //  alphatWallBoilingWallFunctionFvPatchScalarField
            //  onto a new patch
            alphatWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatWallBoilingWallFunctionFvPatchScalarField&,
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const fvPatchFieldMapper&
            );

            //- Copy constructor
            alphatWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatWallBoilingWallFunctionFvPatchScalarField&
            );

            //- Construct and return a clone
            virtual tmp<fvPatchScalarField> clone() const
            {
                return tmp<fvPatchScalarField>
                    (
                        new alphatWallBoilingWallFunctionFvPatchScalarField(*this)
                        );
            }

            //- Copy constructor setting internal field reference
            alphatWallBoilingWallFunctionFvPatchScalarField
            (
                const alphatWallBoilingWallFunctionFvPatchScalarField&,
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
                        new alphatWallBoilingWallFunctionFvPatchScalarField(*this, iF)
                        );
            }


            // Member Functions

            using alphatPhaseChangeWallFunctionFvPatchScalarField::dmdt;

            //- Is there phase change mass transfer for this phasePair
            virtual bool activePhasePair(const phasePairKey&) const;

            //- Return the rate of phase-change for specific phase pair
            virtual const scalarField& dmdt(const phasePairKey&) const;

            //- Return the rate of phase-change for specific phase pair
            virtual const scalarField& mDotL(const phasePairKey&) const;

            //- Return the departure diameter field
            const scalarField& dDeparture() const
            {
                return dDep_;
            }

            //- Return the quenching surface heat flux [W/m^2]
            const scalarField& qq() const
            {
                return qq_;
            }

            //- Return the evaporation surface heat flux [W/m^2]
            tmp<scalarField> qe() const
            {
                return mDotL_ / AbyV_;
            }

            // Evaluation functions

                //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


            // I-O

                //- Write
            virtual void write(Ostream&) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace compressible
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_alphatWallBoilingWallFunctionFvPatchScalarField_Header
