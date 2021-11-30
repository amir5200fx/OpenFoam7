#pragma once
#ifndef _IshiiZuber_Header
#define _IshiiZuber_Header

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
    tnbLib::dragModels::IshiiZuber

Description
    Ishii and Zuber (1979) drag model for dense dispersed bubbly flows.

    Reference:
    \verbatim
        Ishii, M., & Zuber, N. (1979).
        Drag coefficient and relative velocity in bubbly, droplet or particulate
        flows.
        AIChE Journal, 25(5), 843-855.
    \endverbatim

SourceFiles
    IshiiZuber.C

\*---------------------------------------------------------------------------*/

#include <dragModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace dragModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class IshiiZuber Declaration
        \*---------------------------------------------------------------------------*/

        class IshiiZuber
            :
            public dragModel
        {

        public:

            //- Runtime type information
            TypeName("IshiiZuber");


            // Constructors

                //- Construct from a dictionary and a phase pair
            FoamReactingEulerFoamLibs_EXPORT IshiiZuber
            (
                const dictionary& dict,
                const phasePair& pair,
                const bool registerObject
            );


            //- Destructor
            FoamReactingEulerFoamLibs_EXPORT virtual ~IshiiZuber();


            // Member Functions

                //- Drag coefficient
            FoamReactingEulerFoamLibs_EXPORT virtual tmp<volScalarField> CdRe() const;
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace dragModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IshiiZuber_Header
