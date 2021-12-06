#pragma once
#ifndef _SyamlalViscosityTwoPhase_Header
#define _SyamlalViscosityTwoPhase_Header

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
    tnbLib::kineticTheoryModels::viscosityModels::Syamlal

Description

SourceFiles
    SyamlalViscosityTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "viscosityModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace viscosityModels
        {

            /*---------------------------------------------------------------------------*\
                                       Class Syamlal Declaration
            \*---------------------------------------------------------------------------*/

            class Syamlal
                :
                public viscosityModel
            {

            public:

                //- Runtime type information
                TypeName("Syamlal");


                // Constructors

                    //- Construct from components
                Syamlal(const dictionary& dict);


                //- Destructor
                virtual ~Syamlal();


                // Member Functions

                tmp<volScalarField> nu
                (
                    const volScalarField& alpha1,
                    const volScalarField& Theta,
                    const volScalarField& g0,
                    const volScalarField& rho1,
                    const volScalarField& da,
                    const dimensionedScalar& e
                ) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace viscosityModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SyamlalViscosityTwoPhase_Header
