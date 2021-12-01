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

#include <copiedFixedValueFvPatchScalarField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::copiedFixedValueFvPatchScalarField::copiedFixedValueFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
    :
    fixedValueFvPatchScalarField(p, iF),
    sourceFieldName_("default")
{}


tnbLib::copiedFixedValueFvPatchScalarField::copiedFixedValueFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
    :
    fixedValueFvPatchScalarField(p, iF, dict),
    sourceFieldName_(dict.lookup("sourceFieldName"))
{}


tnbLib::copiedFixedValueFvPatchScalarField::copiedFixedValueFvPatchScalarField
(
    const copiedFixedValueFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
    :
    fixedValueFvPatchScalarField(ptf, p, iF, mapper),
    sourceFieldName_(ptf.sourceFieldName_)
{}


tnbLib::copiedFixedValueFvPatchScalarField::copiedFixedValueFvPatchScalarField
(
    const copiedFixedValueFvPatchScalarField& awfpsf
)
    :
    fixedValueFvPatchScalarField(awfpsf),
    sourceFieldName_(awfpsf.sourceFieldName_)
{}


tnbLib::copiedFixedValueFvPatchScalarField::copiedFixedValueFvPatchScalarField
(
    const copiedFixedValueFvPatchScalarField& awfpsf,
    const DimensionedField<scalar, volMesh>& iF
)
    :
    fixedValueFvPatchScalarField(awfpsf, iF),
    sourceFieldName_(awfpsf.sourceFieldName_)
{}



// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::copiedFixedValueFvPatchScalarField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    operator==
        (
            patch().lookupPatchField<volScalarField, scalar>(sourceFieldName_)
            );

    fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::copiedFixedValueFvPatchScalarField::write(Ostream& os) const
{
    fvPatchField<scalar>::write(os);
    writeEntry(os, "sourceFieldName", sourceFieldName_);
    writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    makePatchTypeField
    (
        fvPatchScalarField,
        copiedFixedValueFvPatchScalarField
    );
}


// ************************************************************************* //
