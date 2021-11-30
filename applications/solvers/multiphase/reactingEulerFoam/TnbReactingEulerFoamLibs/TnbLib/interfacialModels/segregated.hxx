#pragma once
#ifndef _segregated_Header
#define _segregated_Header

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
    tnbLib::dragModels::segregated

Description
    Segregated drag model for use in regions with no obvious dispersed phase.

    Reference:
    \verbatim
        Marschall, H. (2011).
        Towards the numerical simulation of multi-scale two-phase flows.
        PhD Thesis, TU M�nchen.
    \endverbatim

SourceFiles
    segregated.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class segregated Declaration
        \*---------------------------------------------------------------------------*/

        class segregated
            :
            public dragModel
        {
            // Private Data

                //- M coefficient
            const dimensionedScalar m_;

            //- N coefficient
            const dimensionedScalar n_;


        public:

            //- Runtime type information
            TypeName("segregated");


            // Constructors

                //- Construct from components
            FoamReactingEulerFoamLibs_EXPORT segregated
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~segregated();


            // Member Functions

                //- Drag coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> CdRe() const;

            //- The drag function used in the momentum equation
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> K() const;

            //- The drag function Kf used in the face-momentum equations
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<surfaceScalarField> Kf() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_segregated_Header
