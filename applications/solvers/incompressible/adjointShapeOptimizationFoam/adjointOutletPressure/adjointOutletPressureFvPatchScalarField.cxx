/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

#include "adjointOutletPressureFvPatchScalarField.hxx"

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchMapper.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::adjointOutletPressureFvPatchScalarField::
adjointOutletPressureFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
    :
    fixedValueFvPatchScalarField(p, iF)
{}


tnbLib::adjointOutletPressureFvPatchScalarField::
adjointOutletPressureFvPatchScalarField
(
    const adjointOutletPressureFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
    :
    fixedValueFvPatchScalarField(ptf, p, iF, mapper)
{}


tnbLib::adjointOutletPressureFvPatchScalarField::
adjointOutletPressureFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
    :
    fixedValueFvPatchScalarField(p, iF, dict)
{}


tnbLib::adjointOutletPressureFvPatchScalarField::
adjointOutletPressureFvPatchScalarField
(
    const adjointOutletPressureFvPatchScalarField& tppsf,
    const DimensionedField<scalar, volMesh>& iF
)
    :
    fixedValueFvPatchScalarField(tppsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::adjointOutletPressureFvPatchScalarField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const fvsPatchField<scalar>& phip =
        patch().lookupPatchField<surfaceScalarField, scalar>("phi");

    const fvsPatchField<scalar>& phiap =
        patch().lookupPatchField<surfaceScalarField, scalar>("phia");

    const fvPatchField<vector>& Up =
        patch().lookupPatchField<volVectorField, vector>("U");

    const fvPatchField<vector>& Uap =
        patch().lookupPatchField<volVectorField, vector>("Ua");

    operator==((phiap / patch().magSf() - 1.0) * phip / patch().magSf() + (Up & Uap));

    fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::adjointOutletPressureFvPatchScalarField::write(Ostream& os) const
{
    fvPatchScalarField::write(os);
    writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    makePatchTypeField
    (
        fvPatchScalarField,
        adjointOutletPressureFvPatchScalarField
    );
}

// ************************************************************************* //
