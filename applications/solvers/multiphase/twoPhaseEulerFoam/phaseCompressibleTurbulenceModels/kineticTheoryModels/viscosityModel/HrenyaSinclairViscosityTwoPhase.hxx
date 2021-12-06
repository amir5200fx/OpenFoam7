#pragma once
#ifndef _HrenyaSinclairViscosityTwoPhase_Header
#define _HrenyaSinclairViscosityTwoPhase_Header

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
    tnbLib::kineticTheoryModels::viscosityModels::HrenyaSinclair

Description

SourceFiles
    HrenyaSinclairViscosityTwoPhase.cxx

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
                                       Class HrenyaSinclair Declaration
            \*---------------------------------------------------------------------------*/

            class HrenyaSinclair
                :
                public viscosityModel
            {
                // Private Data

                dictionary coeffDict_;

                //- Characteristic length of geometry
                dimensionedScalar L_;


            public:

                //- Runtime type information
                TypeName("HrenyaSinclair");


                // Constructors

                    //- Construct from components
                HrenyaSinclair(const dictionary& dict);


                //- Destructor
                virtual ~HrenyaSinclair();


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

                virtual bool read();
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace viscosityModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_HrenyaSinclairViscosityTwoPhase_Header
