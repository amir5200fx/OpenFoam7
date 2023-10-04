#pragma once
#ifndef _TomiyamaWallLubricationTwoPhase_Header
#define _TomiyamaWallLubricationTwoPhase_Header

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
    tnbLib::wallLubricationModels::TomiyamaWallLubrication

Description
    Wall lubrication model of Tomiyama.

    References:
    \verbatim
        "Implementation and Comparison of Correlations for interfacial Forces
         in a Gas-Liquid System within an Euler-Euler Framework"
        Otromke, M.
        PhD Thesis, April 2013
    \endverbatim

    \verbatim
        "Struggle with Computational Bubble Dynamics"
        Tomiyama, A.,
        Multiphase Science and Technology
        Volume 10, Issue 4, 1998, pp. 369-405
    \endverbatim

SourceFiles
    TomiyamaWallLubricationTwoPhase.cxx

\*---------------------------------------------------------------------------*/

#include "wallLubricationModelTwoPhase.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallLubricationModels
    {

        /*---------------------------------------------------------------------------*\
                                    Class TomiyamaWallLubrication Declaration
        \*---------------------------------------------------------------------------*/

        class TomiyamaWallLubrication
            :
            public wallLubricationModel
        {
            // Private Data

                //- Characteristic channel dimension
            const dimensionedScalar D_;


        public:

            //- Runtime type information
            TypeName("Tomiyama");


            // Constructors

                //- Construct from components
            TomiyamaWallLubrication
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~TomiyamaWallLubrication();


            // Member Functions

                //- Return phase-intensive wall lubrication force
            tmp<volVectorField> Fi() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallLubricationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaWallLubricationTwoPhase_Header