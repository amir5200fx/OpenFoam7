#pragma once
#ifndef _WenYu_Header
#define _WenYu_Header

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
    tnbLib::dragModels::WenYu

Description
    Wen and Yu drag model

    Reference:
    \verbatim
        Enwald, H., Peirano, E., & Almstedt, A. E. (1996).
        Eulerian two-phase flow theory applied to fluidization.
        International Journal of Multiphase Flow, 22, 21-66.
        Eq. 86-87, p. 40.
    \endverbatim

SourceFiles
    WenYu.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class WenYu Declaration
        \*---------------------------------------------------------------------------*/

        class WenYu
            :
            public dragModel
        {
            // Private Data

                //- Residual Reynolds Number
            const dimensionedScalar residualRe_;


        public:

            //- Runtime type information
            TypeName("WenYu");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT WenYu
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~WenYu();


            // Member Functions

                //- Drag coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WenYu_Header