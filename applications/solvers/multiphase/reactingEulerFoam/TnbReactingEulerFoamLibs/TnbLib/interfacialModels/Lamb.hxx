#pragma once
#ifndef _Lamb_Header
#define _Lamb_Header

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
    tnbLib::virtualMassModels::Lamb

Description
    Virtual mass model of Lamb.

    Reference:
    \verbatim
        Lamb, H. (1993).
        Hydrodynamics.
        Cambridge university press.
    \endverbatim

SourceFiles
    Lamb.C

\*---------------------------------------------------------------------------*/

#include <virtualMassModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace virtualMassModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class Lamb Declaration
        \*---------------------------------------------------------------------------*/

        class Lamb
            :
            public virtualMassModel
        {
        public:

            //- Runtime type information
            TypeName("Lamb");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT Lamb
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~Lamb();


            // Member Functions

                //- Virtual mass coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> Cvm() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace virtualMassModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_Lamb_Header
