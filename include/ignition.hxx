#pragma once
#ifndef _ignition_Header
#define _ignition_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
    tnbLib::ignition

Description
    tnbLib::ignition

SourceFiles
    ignition.C
    ignitionIO.C

\*---------------------------------------------------------------------------*/

#include <ignitionSite.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class fvMesh;

    /*---------------------------------------------------------------------------*\
                               Class ignition Declaration
    \*---------------------------------------------------------------------------*/

    class ignition
    {
        // Private Data

        const fvMesh& mesh_;

        Switch ignite_;

        PtrList<ignitionSite> ignSites_;


    public:

        // Constructors

            //- Construct from Istream and database
        FoamEngine_EXPORT ignition(const dictionary&, const Time&, const fvMesh&);

        //- Construct from Istream and engineTime
        FoamEngine_EXPORT ignition(const dictionary&, const engineTime&, const fvMesh&);

        //- Disallow default bitwise copy construction
        ignition(const ignition&) = delete;


        // Member Functions

            //- Return the set of ignition sites
        const PtrList<ignitionSite>& sites()
        {
            return ignSites_;
        }


        // Check

        bool ignite() const
        {
            return ignite_;
        }

        //- Are any of the ignition site currently igniting
        FoamEngine_EXPORT bool igniting() const;

        //- Has the mixture been ignited?
        FoamEngine_EXPORT bool ignited() const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const ignition&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_ignition_Header
