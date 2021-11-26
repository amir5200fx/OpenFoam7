#pragma once
#ifndef _immiscibleIncompressibleThreePhaseMixture_Header
#define _immiscibleIncompressibleThreePhaseMixture_Header

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
    tnbLib::immiscibleIncompressibleThreePhaseMixture

Description
    An immiscible incompressible two-phase mixture transport model

SourceFiles
    immiscibleIncompressibleThreePhaseMixture.C

\*---------------------------------------------------------------------------*/

#include "incompressibleThreePhaseMixture.hxx"
#include "threePhaseInterfaceProperties.hxx"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
              Class immiscibleIncompressibleThreePhaseMixture Declaration
    \*---------------------------------------------------------------------------*/

    class immiscibleIncompressibleThreePhaseMixture
        :
        public incompressibleThreePhaseMixture,
        public threePhaseInterfaceProperties
    {

    public:

        // Constructors

            //- Construct from components
        immiscibleIncompressibleThreePhaseMixture
        (
            const volVectorField& U,
            const surfaceScalarField& phi
        );


        //- Destructor
        virtual ~immiscibleIncompressibleThreePhaseMixture()
        {}


        // Member Functions

            //- Correct the transport and interface properties
        virtual void correct()
        {
            incompressibleThreePhaseMixture::correct();
            threePhaseInterfaceProperties::correct();
        }
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_immiscibleIncompressibleThreePhaseMixture_Header
