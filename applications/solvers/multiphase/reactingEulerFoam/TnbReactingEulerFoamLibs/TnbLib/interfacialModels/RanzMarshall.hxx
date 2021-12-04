#pragma once
#ifndef _RanzMarshall_Header
#define _RanzMarshall_Header

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
    tnbLib::heatTransferModels::RanzMarshall

Description
    Ranz-Marshall correlation for turbulent heat transfer from the surface of a
    sphere to the surrounding fluid.

SourceFiles
    RanzMarshall.C

\*---------------------------------------------------------------------------*/

#include <heatTransferModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace heatTransferModels
    {

        /*---------------------------------------------------------------------------*\
                                  Class RanzMarshall Declaration
        \*---------------------------------------------------------------------------*/

        class RanzMarshall
            :
            public heatTransferModel
        {
        public:

            //- Runtime type information
            TypeName("RanzMarshall");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT RanzMarshall
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~RanzMarshall();


            // Member Functions

                //- The heat transfer function K used in the enthalpy equation
            FoamReactingEulerFoamLibs_EXPORT tmp<volScalarField> K(const scalar residualAlpha) const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace heatTransferModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_RanzMarshall_Header