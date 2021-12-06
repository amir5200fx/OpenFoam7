#pragma once
#ifndef _JohnsonJacksonParticleThetaFvPatchScalarFieldTwoPhase_Header
#define _JohnsonJacksonParticleThetaFvPatchScalarFieldTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2019 OpenFOAM Foundation
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
    tnbLib::JohnsonJacksonParticleThetaFvPatchScalarField

Description
    Robin condition for the particulate granular temperature.

    References:
    \verbatim
        "Multifluid Eulerian modeling of dense gas�solids fluidized bed
         hydrodynamics: Influence of the dissipation parameters"
        Reuge, N.,
        Chemical Engineering Science
        Volume 63, Issue 22, November 2008, pp. 5540-5551
    \endverbatim

    \verbatim
        "Frictional-collisional constitutive relations for granular materials,
         with application to plane shearing"
        Johnson, P.C., and Jackson, R.,
        Journal of Fluid Mechanics
        Volume 176, March 1987, pp. 67-93
    \endverbatim

SourceFiles
    JohnsonJacksonParticleThetaFvPatchScalarFieldTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <mixedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
            Class JohnsonJacksonParticleThetaFvPatchScalarField Declaration
    \*---------------------------------------------------------------------------*/

    class JohnsonJacksonParticleThetaFvPatchScalarField
        :
        public mixedFvPatchScalarField
    {
        // Private Data

            //- Particle-wall restitution coefficient
        dimensionedScalar restitutionCoefficient_;

        //- Specularity coefficient
        dimensionedScalar specularityCoefficient_;


    public:

        //- Runtime type information
        TypeName("JohnsonJacksonParticleTheta");


        // Constructors

            //- Construct from patch and internal field
        JohnsonJacksonParticleThetaFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        JohnsonJacksonParticleThetaFvPatchScalarField
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping onto a new patch
        JohnsonJacksonParticleThetaFvPatchScalarField
        (
            const JohnsonJacksonParticleThetaFvPatchScalarField&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Copy constructor
        JohnsonJacksonParticleThetaFvPatchScalarField
        (
            const JohnsonJacksonParticleThetaFvPatchScalarField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
                (
                    new JohnsonJacksonParticleThetaFvPatchScalarField(*this)
                    );
        }

        //- Copy constructor setting internal field reference
        JohnsonJacksonParticleThetaFvPatchScalarField
        (
            const JohnsonJacksonParticleThetaFvPatchScalarField&,
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
                    new JohnsonJacksonParticleThetaFvPatchScalarField(*this, iF)
                    );
        }


        // Member Functions

            // Mapping functions

                //- Map (and resize as needed) from self given a mapping object
                //  Used to update fields following mesh topology change
        virtual void autoMap(const fvPatchFieldMapper&);

        //- Reverse map the given fvPatchField onto this fvPatchField
        //  Used to reconstruct fields
        virtual void rmap(const fvPatchScalarField&, const labelList&);


        //- Update the coefficients
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_JohnsonJacksonParticleThetaFvPatchScalarFieldTwoPhase_Header
