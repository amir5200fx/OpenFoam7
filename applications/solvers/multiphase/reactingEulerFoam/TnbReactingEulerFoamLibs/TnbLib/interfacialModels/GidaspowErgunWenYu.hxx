#pragma once
#ifndef _GidaspowErgunWenYu_Header
#define _GidaspowErgunWenYu_Header

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
    tnbLib::dragModels::GidaspowErgunWenYu

Description
    Gidaspow, Ergun, Wen and Yu drag model

    Reference:
    \verbatim
        Gidaspow, D. (1994).
        Multiphase flow and fluidization: continuum and kinetic theory
        descriptions.
        Academic press, New York.
    \endverbatim

SourceFiles
    GidaspowErgunWenYu.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        class Ergun;
        class WenYu;

        /*---------------------------------------------------------------------------*\
                                   Class GidaspowErgunWenYu Declaration
        \*---------------------------------------------------------------------------*/

        class GidaspowErgunWenYu
            :
            public dragModel
        {
            // Private Data

                //- Ergun drag model
            autoPtr<Ergun> Ergun_;

            //- Wen Yu drag model
            autoPtr<WenYu> WenYu_;


        public:

            //- Runtime type information
            TypeName("GidaspowErgunWenYu");


            // Constructors

                //- Construct from a dictionary and an ordered phase pair
            FoamReactingEulerFoamLibs_EXPORT GidaspowErgunWenYu
            (
                const dictionary& interfaceDict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~GidaspowErgunWenYu();


            // Member Functions

                //- Drag coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GidaspowErgunWenYu_Header
