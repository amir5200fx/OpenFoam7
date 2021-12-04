#pragma once
#ifndef _constantAspectRatio_Header
#define _constantAspectRatio_Header

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
    tnbLib::aspectRatioModels::constantAspectRatio

Description
    Constant value aspect ratio model.

SourceFiles
    constantAspectRatio.C

\*---------------------------------------------------------------------------*/

#include <aspectRatioModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace aspectRatioModels
    {

        /*---------------------------------------------------------------------------*\
                                 Class constantAspectRatio Declaration
        \*---------------------------------------------------------------------------*/

        class constantAspectRatio
            :
            public aspectRatioModel
        {
            // Private Data

                //- Constant aspect ratio value
            const dimensionedScalar E0_;


        public:

            //- Runtime type information
            TypeName("constant");


            // Constructors

                //- Construct from a dictionary and an ordered phase pair
            FoamReactingEulerFoamLibs_EXPORT constantAspectRatio
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~constantAspectRatio();


            // Member Functions

                //- Aspect ratio
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> E() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace aspectRatioModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_constantAspectRatio_Header