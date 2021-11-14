#pragma once
#ifndef _freePiston_Header
#define _freePiston_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
    tnbLib::freePiston

Description
    In case of free pistons, the piston position is determined by a user-defined
    position according to time.

    The piston trajectory is specified in \c constant/engineGeometry using a
    table or a separated file. The position is relative to the cylinder head,
    i.e. decreasing when compressing.

    For example,
    \verbatim
        pistonPositionTime  table ( (0 0.13) (0.020 0.03) );
    \endverbatim

    or with a tableFile
    \verbatim
        pistonPositionTime  tableFile;
        pistonPositionTimeCoeffs
        {
            file                "data";
            outOfBounds         clamp;
            interpolationScheme linear;
        }
    \endverbatim

SourceFiles
    freePiston.C

\*---------------------------------------------------------------------------*/

#include <engineTime.hxx>
#include <dictionary.hxx>
#include <dimensionedScalar.hxx>
#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                            Class freePiston Declaration
    \*---------------------------------------------------------------------------*/

    class freePiston
        :
        public engineTime
    {
        // Private Data

        autoPtr<Function1<scalar>> pistonPositionTime_;


    public:

        //- Runtime type information
        TypeName("freePiston");


        // Constructors

            //- Construct from objectRegistry arguments
        freePiston
        (
            const word& name,
            const fileName& rootPath,
            const fileName& caseName,
            const fileName& systemName = "system",
            const fileName& constantName = "constant",
            const fileName& dictName = "engineGeometry"
        );

        //- Disallow default bitwise copy construction
        freePiston(const freePiston&) = delete;


        //- Destructor
        virtual ~freePiston()
        {}


        // Member Functions

            // Conversion

                //- Calculate the piston position from the engine geometry
                //  and given crank angle.
        scalar pistonPosition(const scalar theta) const;


        // Access

            //- Return current engine time
        virtual scalar theta() const;

        //- Return time unit
        virtual word unit() const;

        //- Return engine time increment
        virtual scalar deltaTheta() const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const freePiston&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_freePiston_Header