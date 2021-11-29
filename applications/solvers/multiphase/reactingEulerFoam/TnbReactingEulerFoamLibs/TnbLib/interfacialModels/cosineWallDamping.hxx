#pragma once
#ifndef _cosineWallDamping_Header
#define _cosineWallDamping_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2019 OpenFOAM Foundation
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
    tnbLib::wallDampingModels::cosine

Description

SourceFiles
    cosineWallDamping.C

\*---------------------------------------------------------------------------*/

#include <interpolatedWallDamping.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class phasePair;

    namespace wallDampingModels
    {

        /*---------------------------------------------------------------------------*\
                                   Class cosine Declaration
        \*---------------------------------------------------------------------------*/

        class cosine
            :
            public interpolated
        {
            // Private Data

                //- Diameter coefficient
            const dimensionedScalar Cd_;


        protected:

            // Protected member functions

                //- Return the force limiter field
            virtual tmp<volScalarField> limiter() const;


        public:

            //- Runtime type information
            TypeName("cosine");


            // Constructors

                //- Construct from components
            cosine
            (
                const dictionary& dict,
                const phasePair& pair
            );


            //- Destructor
            virtual ~cosine();
        };


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    } // End namespace wallDampingModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cosineWallDamping_Header
