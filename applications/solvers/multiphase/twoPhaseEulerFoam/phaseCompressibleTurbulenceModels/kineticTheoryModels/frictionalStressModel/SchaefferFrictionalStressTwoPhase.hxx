#pragma once
#ifndef _SchaefferFrictionalStressTwoPhase_Header
#define _SchaefferFrictionalStressTwoPhase_Header

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
    tnbLib::kineticTheoryModels::frictionalStressModels::Schaeffer

Description

SourceFiles
    SchaefferFrictionalStressTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "frictionalStressModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace kineticTheoryModels
    {
        namespace frictionalStressModels
        {

            /*---------------------------------------------------------------------------*\
                                       Class Schaeffer Declaration
            \*---------------------------------------------------------------------------*/

            class Schaeffer
                :
                public frictionalStressModel
            {
                // Private Data

                dictionary coeffDict_;

                //- Angle of internal friction
                dimensionedScalar phi_;


            public:

                //- Runtime type information
                TypeName("Schaeffer");


                // Constructors

                    //- Construct from components
                Schaeffer(const dictionary& dict);


                //- Destructor
                virtual ~Schaeffer();


                // Member Functions

                virtual tmp<volScalarField> frictionalPressure
                (
                    const phaseModel& phase,
                    const dimensionedScalar& alphaMinFriction,
                    const dimensionedScalar& alphaMax
                ) const;

                virtual tmp<volScalarField> frictionalPressurePrime
                (
                    const phaseModel& phase,
                    const dimensionedScalar& alphaMinFriction,
                    const dimensionedScalar& alphaMax
                ) const;

                virtual tmp<volScalarField> nu
                (
                    const phaseModel& phase,
                    const dimensionedScalar& alphaMinFriction,
                    const dimensionedScalar& alphaMax,
                    const volScalarField& pf,
                    const volSymmTensorField& D
                ) const;

                virtual bool read();
            };


            // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        } // End namespace frictionalStressModels
    } // End namespace kineticTheoryModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SchaefferFrictionalStressTwoPhase_Header
