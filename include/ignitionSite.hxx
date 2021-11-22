#pragma once
#ifndef _ignitionSite_Header
#define _ignitionSite_Header

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
    tnbLib::ignitionSite

Description
    tnbLib::ignitionSite

SourceFiles
    ignitionSiteI.H
    ignitionSite.C
    ignitionSiteIO.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <vector.hxx>
#include <labelList.hxx>
#include <scalarList.hxx>
#include <autoPtr.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class Time;
    class engineTime;
    class fvMesh;

    /*---------------------------------------------------------------------------*\
                               Class ignitionSite Declaration
    \*---------------------------------------------------------------------------*/

    class ignitionSite
    {
        // Private Data

        const Time& db_;
        const fvMesh& mesh_;

        dictionary ignitionSiteDict_;

        vector location_;
        scalar diameter_;
        scalar time_;
        scalar duration_;
        scalar strength_;

        labelList cells_;
        scalarList cellVolumes_;

        //- Current time index.
        //  Used during the update for moving meshes
        mutable label timeIndex_;


        // Private Member Functions

        FoamEngine_EXPORT void findIgnitionCells(const fvMesh&);


    public:

        // Public classes

            //- Class used for the read-construction of
            //  PtrLists of ignitionSite
        class iNew
        {
            const Time& db_;
            const fvMesh& mesh_;

        public:

            iNew(const Time& db, const fvMesh& mesh)
                :
                db_(db),
                mesh_(mesh)
            {}

            autoPtr<ignitionSite> operator()(Istream& is) const
            {
                return autoPtr<ignitionSite>(new ignitionSite(is, db_, mesh_));
            }
        };


        // Constructors

            //- Construct from Istream and database
        FoamEngine_EXPORT ignitionSite(Istream&, const Time&, const fvMesh&);

        //- Construct from Istream and engineTime
        FoamEngine_EXPORT ignitionSite(Istream&, const engineTime&, const fvMesh&);

        //- Copy constructor
        ignitionSite(const ignitionSite&) = default;

        //- Clone
        autoPtr<ignitionSite> clone() const
        {
            return autoPtr<ignitionSite>(new ignitionSite(*this));
        }


        // Member Functions

            // Access

        const vector& location() const
        {
            return location_;
        }

        scalar diameter() const
        {
            return diameter_;
        }

        scalar time() const
        {
            return time_;
        }

        scalar duration() const
        {
            return duration_;
        }

        scalar strength() const
        {
            return strength_;
        }

        //- Return the ignition cells updated if the mesh moved
        FoamEngine_EXPORT const labelList& cells() const;

        const scalarList& cellVolumes() const
        {
            return cellVolumes_;
        }


        // Check

        FoamEngine_EXPORT bool igniting() const;

        FoamEngine_EXPORT bool ignited() const;


        // Member Operators

        FoamEngine_EXPORT void operator=(const ignitionSite&);
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_ignitionSite_Header