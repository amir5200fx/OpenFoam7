#pragma once
#ifndef _constantNuHeatTransfer_Header
#define _constantNuHeatTransfer_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
    tnbLib::heatTransferModels::constantNuHeatTransfer

Description
    Model which applies a user provided constant Nusselt number for interfacial
    heat transfer.

SourceFiles
    constantNuHeatTransfer.C

\*---------------------------------------------------------------------------*/

#include <heatTransferModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace heatTransferModels
    {

        /*---------------------------------------------------------------------------*\
                            Class constantNuHeatTransfer Declaration
        \*---------------------------------------------------------------------------*/

        class constantNuHeatTransfer
            :
            public heatTransferModel
        {
            // Private Data

                //- Nusselt number
            dimensionedScalar Nu_;

        public:

            //- Runtime type information
            TypeName("constantNu");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT constantNuHeatTransfer
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~constantNuHeatTransfer();


            // Member Functions

                //- The heat transfer function K used in the enthalpy equation
            FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> K(const scalar residualAlpha) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace heatTransferModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantNuHeatTransfer_Header
