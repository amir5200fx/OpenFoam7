#pragma once
#ifndef _enginePiston_Header
#define _enginePiston_Header

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
    tnbLib::enginePiston

Description
    tnbLib::enginePiston

SourceFiles
    enginePiston.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <polyPatchID.hxx>
#include <coordinateSystem.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class polyMesh;
    class engineTime;

    /*---------------------------------------------------------------------------*\
                               Class enginePiston Declaration
    \*---------------------------------------------------------------------------*/

    class enginePiston
    {
        // Private Data

            //- Reference to engine mesh
        const polyMesh& mesh_;

        //- Reference to engine database
        const engineTime& engineDB_;

        //- Piston patch
        polyPatchID patchID_;

        //- Coordinate system
        autoPtr<coordinateSystem> csPtr_;


        // Piston layering data

            //- Min layer thickness
        const scalar minLayer_;

        //- Max layer thickness
        const scalar maxLayer_;


    public:

        // Static Data Members


        // Constructors

            //- Construct from components
        FoamEngine_EXPORT enginePiston
        (
            const polyMesh& mesh,
            const word& pistonPatchName,
            const autoPtr<coordinateSystem>& pistonCS,
            const scalar minLayer,
            const scalar maxLayer

        );

        //- Construct from dictionary
        FoamEngine_EXPORT enginePiston
        (
            const polyMesh& mesh,
            const dictionary& dict
        );

        //- Disallow default bitwise copy construction
        enginePiston(const enginePiston&) = delete;


        // Member Functions

            //- Return coordinate system
        const coordinateSystem& cs() const
        {
            return csPtr_();
        }

        //- Return ID of piston patch
        const polyPatchID& patchID() const
        {
            return patchID_;
        }

        // Piston layering thickness

        scalar minLayer() const
        {
            return minLayer_;
        }

        scalar maxLayer() const
        {
            return maxLayer_;
        }


        //- Write dictionary
        FoamEngine_EXPORT void writeDict(Ostream&) const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const enginePiston&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_enginePiston_Header