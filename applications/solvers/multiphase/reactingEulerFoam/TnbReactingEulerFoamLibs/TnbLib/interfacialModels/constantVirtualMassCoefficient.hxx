#pragma once
#ifndef _constantVirtualMassCoefficient_Header
#define _constantVirtualMassCoefficient_Header

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
    tnbLib::virtualMassModels::constantVirtualMassCoefficient

Description
    Constant coefficient virtual mass model.

SourceFiles
    constantVirtualMassCoefficient.C

\*---------------------------------------------------------------------------*/

#include <virtualMassModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace virtualMassModels
    {

        /*---------------------------------------------------------------------------*\
                         Class constantVirtualMassCoefficient Declaration
        \*---------------------------------------------------------------------------*/

        class constantVirtualMassCoefficient
            :
            public virtualMassModel
        {
            // Private Data

                //- Constant virtual mass coefficient
            const dimensionedScalar Cvm_;


        public:

            //- Runtime type information
            TypeName("constantCoefficient");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT constantVirtualMassCoefficient
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~constantVirtualMassCoefficient();


            // Member Functions

                //- Virtual mass coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Cvm() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace virtualMassModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantVirtualMassCoefficient_Header