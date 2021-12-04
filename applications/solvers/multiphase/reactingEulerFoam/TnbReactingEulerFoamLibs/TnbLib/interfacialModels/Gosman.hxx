#pragma once
#ifndef _Gosman_Header
#define _Gosman_Header

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
    tnbLib::turbulentDispersionModels::Gosman

Description
    Turbulent dispersion model of Gosman et al.

    Reference:
    \verbatim
        Gosman, A. D., Lekakou, C., Politis, S., Issa, R. I., &
        Looney, M. K. (1992).
        Multidimensional modeling of turbulent two-phase flows in stirred
        vessels.
        AIChE Journal, 38(12), 1946-1956.
     \endverbatim

SourceFiles
    Gosman.C

\*---------------------------------------------------------------------------*/

#include <turbulentDispersionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace turbulentDispersionModels
    {

        /*---------------------------------------------------------------------------*\
                                     Class Gosman Declaration
        \*---------------------------------------------------------------------------*/

        class Gosman
            :
            public turbulentDispersionModel
        {
            // Private Data

                //- Schmidt number
            const dimensionedScalar sigma_;


        public:

            //- Runtime type information
            TypeName("Gosman");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT Gosman
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~Gosman();


            // Member Functions

                //- Turbulent diffusivity
                //  multiplying the gradient of the phase-fraction
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> D() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace turbulentDispersionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Gosman_Header