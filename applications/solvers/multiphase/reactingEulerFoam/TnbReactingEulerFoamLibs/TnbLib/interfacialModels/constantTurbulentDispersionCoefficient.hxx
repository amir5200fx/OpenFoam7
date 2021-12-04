#pragma once
#ifndef _constantTurbulentDispersionCoefficient_Header
#define _constantTurbulentDispersionCoefficient_Header

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
    tnbLib::turbulentDispersionModels::constantTurbulentDispersionCoefficient

Description
    Constant coefficient turbulent dispersion model.

SourceFiles
    constantTurbulentDispersionCoefficient.C

\*---------------------------------------------------------------------------*/

#include <turbulentDispersionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace turbulentDispersionModels
    {

        /*---------------------------------------------------------------------------*\
                      Class constantTurbulentDispersionCoefficient Declaration
        \*---------------------------------------------------------------------------*/

        class constantTurbulentDispersionCoefficient
            :
            public turbulentDispersionModel
        {
            // Private Data

                //- Constant turbulent dispersion coefficient
            const dimensionedScalar Ctd_;


        public:

            //- Runtime type information
            TypeName("constantCoefficient");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT constantTurbulentDispersionCoefficient
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~constantTurbulentDispersionCoefficient();


            // Member Functions

                //- Turbulent diffusivity
                //  multiplying the gradient of the phase-fraction
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> D() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace turbulentDispersionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantTurbulentDispersionCoefficient_Header