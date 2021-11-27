#pragma once
#ifndef _constantSurfaceTensionCoefficient_Header
#define _constantSurfaceTensionCoefficient_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
    tnbLib::surfaceTensionModels::constantSurfaceTensionCoefficient

Description
    Constant value surface tension model.

SourceFiles
    constantSurfaceTensionCoefficient.C

\*---------------------------------------------------------------------------*/

#include <reactingEulerFoamLibs_Module.hxx>

#include <surfaceTensionModelMultiphase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace surfaceTensionModels
    {

        /*---------------------------------------------------------------------------*\
                      Class constantSurfaceTensionCoefficient Declaration
        \*---------------------------------------------------------------------------*/

        class constantSurfaceTensionCoefficient
            :
            public surfaceTensionModel
        {
            // Private Data

                //- Constant surface tension value
            const dimensionedScalar sigma_;


        public:

            //- Runtime type information
            TypeName("constant");


            // Constructors

                //- Construct from a dictionary and a phase pair
            constantSurfaceTensionCoefficient
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            virtual ~constantSurfaceTensionCoefficient();


            // Member Functions

                //- Aspect ratio
            virtual tmp<volScalarField> sigma() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace surfaceTensionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantSurfaceTensionCoefficient_Header
