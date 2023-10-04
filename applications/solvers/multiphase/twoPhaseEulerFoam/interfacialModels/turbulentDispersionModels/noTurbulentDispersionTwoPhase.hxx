#pragma once
#ifndef _noTurbulentDispersionTwoPhase_Header
#define _noTurbulentDispersionTwoPhase_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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
    tnbLib::turbulentDispersionModels::noTurbulentDispersion

Description

SourceFiles
	noTurbulentDispersionTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "turbulentDispersionModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace turbulentDispersionModels
    {

        /*---------------------------------------------------------------------------*\
                              Class noTurbulentDispersion Declaration
        \*---------------------------------------------------------------------------*/

        class noTurbulentDispersion
            :
            public turbulentDispersionModel
        {
        public:

            //- Runtime type information
            TypeName("none");


            // Constructors

                //- Construct from a dictionary and a phase pair
            noTurbulentDispersion
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~noTurbulentDispersion();


            // Member Functions

                //- Turbulent diffusivity
                //  multiplying the gradient of the phase-fraction
            virtual tmp<volScalarField> D() const;

            //- Turbulent dispersion force
            virtual tmp<volVectorField> F() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace turbulentDispersionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_noTurbulentDispersionTwoPhase_Header