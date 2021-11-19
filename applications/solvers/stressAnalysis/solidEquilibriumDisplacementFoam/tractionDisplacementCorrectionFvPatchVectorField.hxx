#pragma once
#ifndef _tractionDisplacementCorrectionFvPatchVectorField_Header
#define _tractionDisplacementCorrectionFvPatchVectorField_Header

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

#include <includeAllModules.hxx>

#include <fvPatchFields.hxx>
#include <fixedGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
            Class tractionDisplacementCorrectionStressFvPatch Declaration
    \*---------------------------------------------------------------------------*/

    class tractionDisplacementCorrectionFvPatchVectorField
        :
        public fixedGradientFvPatchVectorField
    {

        // Private Data

        vectorField traction_;
        scalarField pressure_;


    public:

        //- Runtime type information
        TypeName("tractionDisplacement");


        // Constructors

            //- Construct from patch and internal field
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and Istream
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            Istream&
        );

        //- Construct from patch, internal field and dictionary
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  tractionDisplacementCorrectionFvPatchVectorField onto a new patch
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const tractionDisplacementCorrectionFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy setting internal field reference
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const tractionDisplacementCorrectionFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
                (
                    new tractionDisplacementCorrectionFvPatchVectorField(*this)
                    );
        }

        //- Construct as copy setting internal field reference
        tractionDisplacementCorrectionFvPatchVectorField
        (
            const tractionDisplacementCorrectionFvPatchVectorField&,
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
                    new tractionDisplacementCorrectionFvPatchVectorField(*this, iF)
                    );
        }


        // Member Functions

            // Access

        virtual const vectorField& traction() const
        {
            return traction_;
        }

        virtual vectorField& traction()
        {
            return traction_;
        }

        virtual const scalarField& pressure() const
        {
            return pressure_;
        }

        virtual  scalarField& pressure()
        {
            return pressure_;
        }


        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            //  Used to update fields following mesh topology change
        virtual void autoMap(const fvPatchFieldMapper&);

        //- Reverse map the given fvPatchField onto this fvPatchField
        //  Used to reconstruct fields
        virtual void rmap(const fvPatchVectorField&, const labelList&);


        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tractionDisplacementCorrectionFvPatchVectorField_Header
