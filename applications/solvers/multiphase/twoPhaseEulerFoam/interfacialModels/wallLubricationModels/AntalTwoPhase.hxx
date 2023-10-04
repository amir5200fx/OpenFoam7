#pragma once
#ifndef _AntalTwoPhase_Header
#define _AntalTwoPhase_Header

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
    tnbLib::wallLubricationModels::Antal

Description
    Wall lubrication model of Antal et al.

    Reference:
    \verbatim
        "Analysis of phase distribution in fully developed laminar bubbly
         two-phase flow"
        Antal, S.P., Lahey Jr, R.T., and Flaherty, J.E.
        International Journal of Multiphase Flow
        Volume 17, Issue 5, September 1991, pp. 635-652
    \endverbatim

SourceFiles
    AntalTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "wallLubricationModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallLubricationModels
    {

        /*---------------------------------------------------------------------------*\
                                    Class Antal Declaration
        \*---------------------------------------------------------------------------*/

        class Antal
            :
            public wallLubricationModel
        {
            // Private Data

                //- Coefficient 1
            const dimensionedScalar Cw1_;

            //- Coefficient 2
            const dimensionedScalar Cw2_;


        public:

            //- Runtime type information
            TypeName("Antal");


            // Constructors

                //- Construct from components
            Antal
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~Antal();


            // Member Functions

                //- Return phase-intensive wall lubrication force
            tmp<volVectorField> Fi() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallLubricationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_AntalTwoPhase_Header