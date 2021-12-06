#pragma once
#ifndef _viscosityModelTwoPhase_Header
#define _viscosityModelTwoPhase_Header

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
    tnbLib::kineticTheoryModels::viscosityModel

Description

SourceFiles
    viscosityModelTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

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
                                   Class viscosityModel Declaration
        \*---------------------------------------------------------------------------*/

        class viscosityModel
        {
        protected:

            // Protected data

            const dictionary& dict_;


        public:

            //- Runtime type information
            TypeName("viscosityModel");

            // Declare runtime constructor selection table
            declareRunTimeSelectionTable
            (
                autoPtr,
                viscosityModel,
                dictionary,
                (
                    const dictionary& dict
                    ),
                (dict)
            );


            // Constructors

                //- Construct from components
            viscosityModel(const dictionary& dict);

            //- Disallow default bitwise copy construction
            viscosityModel(const viscosityModel&) = delete;


            // Selectors

            static autoPtr<viscosityModel> New
            (
                const dictionary& dict
            );


            //- Destructor
            virtual ~viscosityModel();


            // Member Functions

            virtual tmp<volScalarField> nu
            (
                const volScalarField& alpha1,
                const volScalarField& Theta,
                const volScalarField& g0,
                const volScalarField& rho1,
                const volScalarField& da,
                const dimensionedScalar& e
            ) const = 0;

            virtual bool read()
            {
                return true;
            }


            // Member Operators

                //- Disallow default bitwise assignment
            void operator=(const viscosityModel&) = delete;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_viscosityModelTwoPhase_Header
