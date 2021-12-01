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

\*---------------------------------------------------------------------------*/

#include <alphatPhaseChangeWallFunctionFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace compressible
    {

        // * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

        defineTypeNameAndDebug(alphatPhaseChangeWallFunctionFvPatchScalarField, 0);

        // * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

        alphatPhaseChangeWallFunctionFvPatchScalarField::
            alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const fvPatch& p,
                const DimensionedField<scalar, volMesh>& iF
            )
            :
            fixedValueFvPatchScalarField(p, iF),
            dmdt_(p.size(), 0),
            mDotL_(p.size(), 0)
        {}


        alphatPhaseChangeWallFunctionFvPatchScalarField::
            alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const fvPatch& p,
                const DimensionedField<scalar, volMesh>& iF,
                const dictionary& dict
            )
            :
            fixedValueFvPatchScalarField(p, iF, dict),
            dmdt_(p.size(), 0),
            mDotL_(p.size(), 0)
        {
            if (dict.found("dmdt"))
            {
                dmdt_ = scalarField("dmdt", dict, p.size());
            }

            if (dict.found("mDotL"))
            {
                dmdt_ = scalarField("mDotL", dict, p.size());
            }
        }


        alphatPhaseChangeWallFunctionFvPatchScalarField::
            alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField& ptf,
                const fvPatch& p,
                const DimensionedField<scalar, volMesh>& iF,
                const fvPatchFieldMapper& mapper
            )
            :
            fixedValueFvPatchScalarField(ptf, p, iF, mapper),
            dmdt_(mapper(ptf.dmdt_)),
            mDotL_(mapper(ptf.mDotL_))
        {}


        alphatPhaseChangeWallFunctionFvPatchScalarField::
            alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField& awfpsf
            )
            :
            fixedValueFvPatchScalarField(awfpsf),
            dmdt_(awfpsf.dmdt_),
            mDotL_(awfpsf.mDotL_)
        {}


        alphatPhaseChangeWallFunctionFvPatchScalarField::
            alphatPhaseChangeWallFunctionFvPatchScalarField
            (
                const alphatPhaseChangeWallFunctionFvPatchScalarField& awfpsf,
                const DimensionedField<scalar, volMesh>& iF
            )
            :
            fixedValueFvPatchScalarField(awfpsf, iF),
            dmdt_(awfpsf.dmdt_),
            mDotL_(awfpsf.mDotL_)
        {}


        // * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

        void alphatPhaseChangeWallFunctionFvPatchScalarField::
            write(Ostream& os) const
        {
            fvPatchField<scalar>::write(os);
            writeEntry(os, "dmdt", dmdt_);
            writeEntry(os, "mDotL", mDotL_);
            writeEntry(os, "value", *this);
        }


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //
