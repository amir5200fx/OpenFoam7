#pragma once
#ifndef _LunPressureTwoPhase_Header
#define _LunPressureTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
    tnbLib::kineticTheoryModels::granularPressureModels::Lun

Description

SourceFiles
    LunPressureTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "granularPressureModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace granularPressureModels
        {

            /*---------------------------------------------------------------------------*\
                                       Class Lun Declaration
            \*---------------------------------------------------------------------------*/

            class Lun
                :
                public granularPressureModel
            {

            public:

                //- Runtime type information
                TypeName("Lun");


                // Constructors

                    //- Construct from components
                Lun(const dictionary& dict);


                //- Destructor
                virtual ~Lun();


                // Member Functions

                tmp<volScalarField> granularPressureCoeff
                (
                    const volScalarField& alpha1,
                    const volScalarField& g0,
                    const volScalarField& rho1,
                    const dimensionedScalar& e
                ) const;

                tmp<volScalarField> granularPressureCoeffPrime
                (
                    const volScalarField& alpha1,
                    const volScalarField& g0,
                    const volScalarField& g0prime,
                    const volScalarField& rho1,
                    const dimensionedScalar& e
                ) const;
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace granularPressureModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LunPressureTwoPhase_Header
