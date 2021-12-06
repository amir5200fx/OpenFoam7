#pragma once
#ifndef _TomiyamaAnalyticTwoPhase_Header
#define _TomiyamaAnalyticTwoPhase_Header

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
    tnbLib::dragModels::TomiyamaAnalytic

Description
    Analytical drag model of Tomiyama et al.

    Reference:
    \verbatim
        "Drag Coefficients of Bubbles. 1st Report. Drag Coefficients of a
         Single Bubble in a Stagnant Liquid."
        Tomiyama, A., Kataoka, I., and Sakaguchi, T.,
        Nippon Kikai Gakkai Ronbunshu
        Volume 61, Issue 587, 1995, pp. 2357-2364
    \endverbatim

SourceFiles
    TomiyamaAnalyticTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "dragModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class TomiyamaAnalytic Declaration
        \*---------------------------------------------------------------------------*/

        class TomiyamaAnalytic
            :
            public dragModel
        {
            // Private Data

                //- Residual Reynolds Number
            const dimensionedScalar residualRe_;

            //- Residual Eotvos number
            const dimensionedScalar residualEo_;

            //- Residual aspect ratio
            const dimensionedScalar residualE_;


        public:

            //- Runtime type information
            TypeName("TomiyamaAnalytic");


            // Constructors

                //- Construct from a dictionary and a phase pair
            TomiyamaAnalytic
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            virtual ~TomiyamaAnalytic();


            // Member Functions

                // Drag coefficient
            virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaAnalyticTwoPhase_Header
