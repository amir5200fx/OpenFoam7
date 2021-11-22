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

#include "adjointOutletVelocityFvPatchVectorField.hxx"

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::adjointOutletVelocityFvPatchVectorField::
adjointOutletVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
    :
    fixedValueFvPatchVectorField(p, iF)
{}


tnbLib::adjointOutletVelocityFvPatchVectorField::
adjointOutletVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
    :
    fixedValueFvPatchVectorField(p, iF, dict)
{}


tnbLib::adjointOutletVelocityFvPatchVectorField::
adjointOutletVelocityFvPatchVectorField
(
    const adjointOutletVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
    :
    fixedValueFvPatchVectorField(ptf, p, iF, mapper)
{}


tnbLib::adjointOutletVelocityFvPatchVectorField::
adjointOutletVelocityFvPatchVectorField
(
    const adjointOutletVelocityFvPatchVectorField& pivpvf,
    const DimensionedField<vector, volMesh>& iF
)
    :
    fixedValueFvPatchVectorField(pivpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Update the coefficients associated with the patch field
void tnbLib::adjointOutletVelocityFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const fvsPatchField<scalar>& phiap =
        patch().lookupPatchField<surfaceScalarField, scalar>("phia");

    const fvPatchField<vector>& Up =
        patch().lookupPatchField<volVectorField, vector>("U");

    scalarField Un(mag(patch().nf() & Up));
    vectorField UtHat((Up - patch().nf() * Un) / (Un + small));

    vectorField Uan(patch().nf() * (patch().nf() & patchInternalField()));

    vectorField::operator=(phiap * patch().Sf() / sqr(patch().magSf()) + UtHat);
    // vectorField::operator=(Uan + UtHat);

    fixedValueFvPatchVectorField::updateCoeffs();
}


void tnbLib::adjointOutletVelocityFvPatchVectorField::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
    writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    makePatchTypeField
    (
        fvPatchVectorField,
        adjointOutletVelocityFvPatchVectorField
    );
}


// ************************************************************************* //
