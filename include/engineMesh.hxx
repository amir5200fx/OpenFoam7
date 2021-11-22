#pragma once
#ifndef _engineMesh_Header
#define _engineMesh_Header

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
    tnbLib::engineMesh

Description
    tnbLib::engineMesh

SourceFiles
    engineMesh.C

\*---------------------------------------------------------------------------*/

#include <Engine_Module.hxx>

#include <engineTime.hxx>
#include <fvMesh.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class engineMesh Declaration
    \*---------------------------------------------------------------------------*/

    class engineMesh
        :
        public fvMesh
    {
    protected:

        // Protected data

        const engineTime& engineDB_;

        label pistonIndex_;
        label linerIndex_;
        label cylinderHeadIndex_;

        dimensionedScalar deckHeight_;
        dimensionedScalar pistonPosition_;


    public:

        //- Runtime type information
        /*TypeName("engineMesh");*/
        static const char* typeName_() { return "engineMesh"; }
        static FoamEngine_EXPORT const ::tnbLib::word typeName;
        static FoamEngine_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Declare run-time constructor selection table

        /*declareRunTimeSelectionTable
        (
            autoPtr,
            engineMesh,
            IOobject,
            (const IOobject& io),
            (io)
        );*/
        typedef autoPtr<engineMesh> (*IOobjectConstructorPtr)(const IOobject& io);
        typedef HashTable<IOobjectConstructorPtr, word, string::hash> IOobjectConstructorTable;
        static FoamEngine_EXPORT IOobjectConstructorTable* IOobjectConstructorTablePtr_;
        static FoamEngine_EXPORT void constructIOobjectConstructorTables();
        static FoamEngine_EXPORT void destroyIOobjectConstructorTables();

        template <class engineMeshType>
        class addIOobjectConstructorToTable
        {
        public:
	        static autoPtr<engineMesh> New(const IOobject& io) { return autoPtr<engineMesh>(new engineMeshType(io)); }

	        addIOobjectConstructorToTable(const word& lookup = engineMeshType::typeName)
	        {
		        constructIOobjectConstructorTables();
		        if (!IOobjectConstructorTablePtr_->insert(lookup, New))
		        {
			        std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "engineMesh" <<
				        std::endl;
			        error::safePrintStack(std::cerr);
		        }
	        }

	        ~addIOobjectConstructorToTable() { destroyIOobjectConstructorTables(); }
        };

        template <class engineMeshType>
        class addRemovableIOobjectConstructorToTable
        {
	        const word& lookup_;
        public:
	        static autoPtr<engineMesh> New(const IOobject& io) { return autoPtr<engineMesh>(new engineMeshType(io)); }

	        addRemovableIOobjectConstructorToTable(const word& lookup = engineMeshType::typeName) : lookup_(lookup)
	        {
		        constructIOobjectConstructorTables();
		        IOobjectConstructorTablePtr_->set(lookup, New);
	        }

	        ~addRemovableIOobjectConstructorToTable()
	        {
		        if (IOobjectConstructorTablePtr_) { IOobjectConstructorTablePtr_->erase(lookup_); }
	        }
        };;


        // Constructors

            //- Construct from objectRegistry, and read/write options
        FoamEngine_EXPORT explicit engineMesh(const IOobject& io);

        //- Disallow default bitwise copy construction
        engineMesh(const engineMesh&) = delete;


        // Selectors

            //- Select null constructed
        static FoamEngine_EXPORT autoPtr<engineMesh> New(const IOobject& io);


        //- Destructor
        FoamEngine_EXPORT virtual ~engineMesh();


        // Member Functions

            // Edit

        virtual void move() = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const engineMesh&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_engineMesh_Header
