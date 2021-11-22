#pragma once
#ifndef _adjointOutletVelocityFvPatchVectorField_Header
#define _adjointOutletVelocityFvPatchVectorField_Header

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

Class
    tnbLib::adjointOutletVelocityFvPatchVectorField

Description

SourceFiles
    adjointOutletVelocityFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                     Class adjointOutletVelocityFvPatch Declaration
    \*---------------------------------------------------------------------------*/

    class adjointOutletVelocityFvPatchVectorField
        :
        public fixedValueFvPatchVectorField
    {

    public:

        //- Runtime type information
        TypeName("adjointOutletVelocity");


        // Constructors

            //- Construct from patch and internal field
        adjointOutletVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        adjointOutletVelocityFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given adjointOutletVelocityFvPatchVectorField
        //  onto a new patch
        adjointOutletVelocityFvPatchVectorField
        (
            const adjointOutletVelocityFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
                (
                    new adjointOutletVelocityFvPatchVectorField(*this)
                    );
        }

        //- Construct as copy setting internal field reference
        adjointOutletVelocityFvPatchVectorField
        (
            const adjointOutletVelocityFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
                (
                    new adjointOutletVelocityFvPatchVectorField(*this, iF)
                    );
        }


        // Member Functions

            //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_adjointOutletVelocityFvPatchVectorField_Header