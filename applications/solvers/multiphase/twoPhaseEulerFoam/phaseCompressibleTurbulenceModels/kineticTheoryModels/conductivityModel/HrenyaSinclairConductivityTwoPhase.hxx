#pragma once
#ifndef _HrenyaSinclairConductivityTwoPhase_Header
#define _HrenyaSinclairConductivityTwoPhase_Header

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
    tnbLib::kineticTheoryModels::conductivityModels::HrenyaSinclair

Description

SourceFiles
    HrenyaSinclairTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "conductivityModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace conductivityModels
        {

            /*---------------------------------------------------------------------------*\
                                       Class HrenyaSinclair Declaration
            \*---------------------------------------------------------------------------*/

            class HrenyaSinclair
                :
                public conductivityModel
            {
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

                tmp<volScalarField> kappa
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

        } // End namespace conductivityModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_HrenyaSinclairConductivityTwoPhase_Header
