#pragma once
#ifndef _faceSelection_Header
#define _faceSelection_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
    tnbLib::faceSelection

Description
    Face selection method for createBaffles

SourceFiles
    faceSelection.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <dictionary.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <autoPtr.hxx>
#include <boolList.hxx>
#include <labelList.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class fvMesh;

    /*---------------------------------------------------------------------------*\
                             Class faceSelection Declaration
    \*---------------------------------------------------------------------------*/

    class faceSelection
    {
    protected:

        // Protected data

            //- Name
        const word name_;

        //- Reference to mesh
        const fvMesh& mesh_;

        //- Input dictionary
        const dictionary dict_;

        //- Switch direction?
        const Switch flip_;

    public:

        //- Runtime type information
        TypeName("faceSelection");


        // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            faceSelection,
            dictionary,
            (
                const word& name,
                const fvMesh& mesh,
                const dictionary& dict
                ),
            (name, mesh, dict)
        );


        // Constructors

            //- Construct from dictionary
        faceSelection
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict
        );

        //- Clone
        autoPtr<faceSelection> clone() const
        {
            NotImplemented;
            return autoPtr<faceSelection>(nullptr);
        }


        // Selectors

            //- Return a reference to the selected faceSelection
        static autoPtr<faceSelection> New
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict
        );


        //- Destructor
        virtual ~faceSelection();


        // Member Functions

        const word& name() const
        {
            return name_;
        }

        const dictionary& dict() const
        {
            return dict_;
        }

        virtual void select(const label, labelList&, boolList&) const = 0;

    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_faceSelection_Header
