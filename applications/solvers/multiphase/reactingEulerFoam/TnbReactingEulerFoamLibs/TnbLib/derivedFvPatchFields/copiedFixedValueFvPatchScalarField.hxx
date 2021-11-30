#pragma once
#ifndef _copiedFixedValueFvPatchScalarField_Header
#define _copiedFixedValueFvPatchScalarField_Header

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
    tnbLib::copiedFixedValueFvPatchScalarField

Description
    Copies the boundary values from a user specified field.

See also
    tnbLib::fixedValueFvPatchField

SourceFiles
    copiedFixedValueFvPatchScalarField.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                Class copiedFixedValueFvPatchScalarField Declaration
    \*---------------------------------------------------------------------------*/

    class copiedFixedValueFvPatchScalarField
        :
        public fixedValueFvPatchScalarField
    {
    protected:

        // Protected data

        word sourceFieldName_;

    public:

        //- Runtime type information
        TypeName("copiedFixedValue");


        // Constructors

            //- Construct from patch and internal field
        FoamReactingEulerFoamLibs_EXPORT copiedFixedValueFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        FoamReactingEulerFoamLibs_EXPORT copiedFixedValueFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  copiedFixedValueFvPatchScalarField
        //  onto a new patch
        FoamReactingEulerFoamLibs_EXPORT copiedFixedValueFvPatchScalarField
        (
            const copiedFixedValueFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Copy constructor
        FoamReactingEulerFoamLibs_EXPORT copiedFixedValueFvPatchScalarField
        (
            const copiedFixedValueFvPatchScalarField&
        );

        //- Copy constructor setting internal field reference
        FoamReactingEulerFoamLibs_EXPORT copiedFixedValueFvPatchScalarField
        (
            const copiedFixedValueFvPatchScalarField&,
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

#endif // !_copiedFixedValueFvPatchScalarField_Header
