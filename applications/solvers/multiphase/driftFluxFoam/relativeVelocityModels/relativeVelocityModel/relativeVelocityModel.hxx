#pragma once
#ifndef _relativeVelocityModel_Header
#define _relativeVelocityModel_Header

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
    tnbLib::relativeVelocityModel

Description

SourceFiles
    relativeVelocityModel.C

\*---------------------------------------------------------------------------*/

#include "incompressibleTwoPhaseInteractingMixture.hxx"

#include <fvCFD.hxx>
#include <dictionary.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                             Class relativeVelocityModel Declaration
    \*---------------------------------------------------------------------------*/

    class relativeVelocityModel
    {
        // Private Member Functions

            //- Return the list of patchFieldTypes for Udm derived from U
        wordList UdmPatchFieldTypes() const;


    protected:

        // Protected data

            //- Mixture properties
        const incompressibleTwoPhaseInteractingMixture& mixture_;

        //- Name of the continuous phase
        const word continuousPhaseName_;

        //- Continuous phase fraction
        const volScalarField& alphac_;

        //- Dispersed phase fraction
        const volScalarField& alphad_;

        //- Continuous density
        const dimensionedScalar& rhoc_;

        //- Dispersed density
        const dimensionedScalar& rhod_;

        //- Dispersed diffusion velocity
        mutable volVectorField Udm_;


    public:

        //- Runtime type information
        TypeName("relativeVelocityModel");

        //- Declare runtime constructor selection table
        declareRunTimeSelectionTable
        (
            autoPtr,
            relativeVelocityModel,
            dictionary,
            (const dictionary& dict,
                const incompressibleTwoPhaseInteractingMixture& mixture),
            (dict, mixture)
        );


        // Constructors

            //- Construct from components
        relativeVelocityModel
        (
            const dictionary& dict,
            const incompressibleTwoPhaseInteractingMixture& mixture
        );

        //- Disallow default bitwise copy construction
        relativeVelocityModel(const relativeVelocityModel&) = delete;


        // Selector
        static autoPtr<relativeVelocityModel> New
        (
            const dictionary& dict,
            const incompressibleTwoPhaseInteractingMixture& mixture
        );


        //- Destructor
        virtual ~relativeVelocityModel();


        // Member Functions

            //- Mixture properties
        const incompressibleTwoPhaseInteractingMixture& mixture() const
        {
            return mixture_;
        }

        //- Return the mixture mean density
        tmp<volScalarField> rho() const;

        //- Return the diffusion velocity of the dispersed phase
        const volVectorField& Udm() const
        {
            return Udm_;
        }

        //- Return the stress tensor due to the phase transport
        tmp<volSymmTensorField> tauDm() const;

        //- Update the diffusion velocity
        virtual void correct() = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const relativeVelocityModel&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_relativeVelocityModel_Header
