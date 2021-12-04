#pragma once
#ifndef _TomiyamaWallLubrication_Header
#define _TomiyamaWallLubrication_Header

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
        Otromke, M. (2013).
        Implementation and Comparison of Correlations for interfacial Forces in
        a Gas-Liquid System within an Euler-Euler Framework.
        PhD Thesis.
    \endverbatim

    \verbatim
        Tomiyama, A. (1998).
        Struggle with computational bubble dynamics.
        Multiphase Science and Technology, 10(4), 369-405.
    \endverbatim

SourceFiles
    TomiyamaWallLubrication.C

\*---------------------------------------------------------------------------*/

#include <wallLubricationModel.hxx>

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
            FoamReactingEulerFoamLibs_EXPORT TomiyamaWallLubrication
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~TomiyamaWallLubrication();


            // Member Functions

                //- Return phase-intensive wall lubrication force
            FoamReactingEulerFoamLibs_EXPORT tmp<volVectorField> Fi() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallLubricationModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_TomiyamaWallLubrication_Header