#pragma once
#ifndef _frictionalStressModelTwoPhase_Header
#define _frictionalStressModelTwoPhase_Header

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
    tnbLib::kineticTheoryModels::frictionalStressModel

SourceFiles
    frictionalStressModelTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "phaseModelTwoPhase.hxx"

#include <dictionary.hxx>
#include <volFields.hxx>
#include <dimensionedTypes.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class frictionalStressModel Declaration
        \*---------------------------------------------------------------------------*/

        class frictionalStressModel
        {
        protected:

            // Protected data

                //- Reference to higher-level dictionary for re-read
            const dictionary& dict_;


        public:

            //- Runtime type information
            TypeName("frictionalStressModel");

            // Declare runtime constructor selection table
            declareRunTimeSelectionTable
            (
                autoPtr,
                frictionalStressModel,
                dictionary,
                (
                    const dictionary& dict
                    ),
                (dict)
            );


            // Constructors

                //- Construct from components
            frictionalStressModel(const dictionary& dict);

            //- Disallow default bitwise copy construction
            frictionalStressModel(const frictionalStressModel&) = delete;


            // Selectors

            static autoPtr<frictionalStressModel> New
            (
                const dictionary& dict
            );


            //- Destructor
            virtual ~frictionalStressModel();


            // Member Functions

            virtual tmp<volScalarField> frictionalPressure
            (
                const phaseModel& phase,
                const dimensionedScalar& alphaMinFriction,
                const dimensionedScalar& alphaMax
            ) const = 0;

            virtual tmp<volScalarField> frictionalPressurePrime
            (
                const phaseModel& phase,
                const dimensionedScalar& alphaMinFriction,
                const dimensionedScalar& alphaMax
            ) const = 0;

            virtual tmp<volScalarField> nu
            (
                const phaseModel& phase,
                const dimensionedScalar& alphaMinFriction,
                const dimensionedScalar& alphaMax,
                const volScalarField& pf,
                const volSymmTensorField& D
            ) const = 0;

            virtual bool read() = 0;


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const frictionalStressModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_frictionalStressModelTwoPhase_Header
