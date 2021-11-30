#pragma once
#ifndef _alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField_Header
#define _alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField_Header

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
        alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField

Description
    This boundary condition provides a thermal wall function for turbulent
    thermal diffusivity (usually\c alphat) based on the Jayatilleke model for
    the Eulerian multiphase solvers.

Usage
    \table
        Property     | Description             | Required    | Default value
        Prt          | Turbulent Prandtl number | no         | 0.85
        Cmu          | Model coefficient       | no          | 0.09
        kappa        | von Karman constant     | no          | 0.41
        E            | Model coefficient       | no          | 9.8
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            alphatPhaseChangeJayatillekeWallFunction;
        Prt             0.85;
        kappa           0.41;
        E               9.8;
        value           uniform 0; // optional value entry
    }
    \endverbatim

See also
    tnbLib::compressible::alphatPhaseChangeWallFunctionFvPatchScalarField

SourceFiles
    alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <alphatPhaseChangeWallFunctionFvPatchScalarField.hxx>
#include <nutWallFunctionFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace compressible
    {

        /*---------------------------------------------------------------------------*\
         Class alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField Declaration
        \*---------------------------------------------------------------------------*/

        class alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            :
            public alphatPhaseChangeWallFunctionFvPatchScalarField
        {

        protected:

            // Protected data

                //- Turbulent Prandtl number
            scalar Prt_;

            // Solution parameters

            static FoamReactingEulerFoamLibs_EXPORT scalar maxExp_;
            static FoamReactingEulerFoamLibs_EXPORT scalar tolerance_;
            static FoamReactingEulerFoamLibs_EXPORT label maxIters_;


            // Protected Member Functions

                //- 'P' function
            FoamReactingEulerFoamLibs_EXPORT tmp<scalarField> Psmooth(const scalarField& Prat) const;

            //- Calculate y+ at the edge of the thermal laminar sublayer
            FoamReactingEulerFoamLibs_EXPORT tmp<scalarField> yPlusTherm
            (
                const nutWallFunctionFvPatchScalarField& nutw,
                const scalarField& P,
                const scalarField& Prat
            ) const;

            //- Update turbulent thermal diffusivity
            FoamReactingEulerFoamLibs_EXPORT tmp<scalarField> calcAlphat
            (
                const scalarField& prevAlphat
            ) const;


        public:

            //- Runtime type information
            TypeName("compressible::alphatPhaseChangeJayatillekeWallFunction");


            // Constructors

                //- Construct from patch and internal field
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&
            );

            //- Construct from patch, internal field and dictionary
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            (
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const dictionary&
            );

            //- Construct by mapping given
            //  alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            //  onto a new patch
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField&,
                const fvPatch&,
                const DimensionedField<scalar, volMesh>&,
                const fvPatchFieldMapper&
            );

            //- Copy constructor
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField&
            );

            //- Construct and return a clone
            virtual tmp<fvPatchScalarField> clone() const
            {
                return tmp<fvPatchScalarField>
                    (
                        new alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
                        (
                            *this
                        )
                        );
            }

            //- Copy constructor setting internal field reference
            FoamReactingEulerFoamLibs_EXPORT alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField&,
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
                        new alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField
                        (
                            *this,
                            iF
                        )
                        );
            }


            // Member Functions

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

#endif // !_alphatPhaseChangeJayatillekeWallFunctionFvPatchScalarField_Header
