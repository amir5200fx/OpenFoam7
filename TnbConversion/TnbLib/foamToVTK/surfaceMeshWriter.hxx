#pragma once
#ifndef _surfaceMeshWriter_Header
#define _surfaceMeshWriter_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
    tnbLib::surfaceMeshWriter

Description
    Write faces with fields

SourceFiles
    surfaceMeshWriter.C
    surfaceMeshWriterTemplates.C

\*---------------------------------------------------------------------------*/

#include <vtkMesh.hxx>
#include <pointMesh.hxx>
#include <OFstream.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <indirectPrimitivePatch.hxx>

#include <writeFuns.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class volPointInterpolation;

    /*---------------------------------------------------------------------------*\
                          Class surfaceMeshWriter Declaration
    \*---------------------------------------------------------------------------*/

    class surfaceMeshWriter
    {
        const bool binary_;

        const indirectPrimitivePatch& pp_;

        const fileName fName_;

        std::ofstream os_;


    public:

        // Constructors

            //- Construct from components
        surfaceMeshWriter
        (
            const bool binary,
            const indirectPrimitivePatch& pp,
            const word& name,
            const fileName&
        );


        // Member Functions

        std::ofstream& os()
        {
            return os_;
        }

        //- Extract face data
        template<class Type>
        tmp<Field<Type>> getFaceField
        (
            const GeometricField<Type, fvsPatchField, surfaceMesh>&
        ) const;

        //- Write surfaceFields
        template<class Type>
        void write
        (
            const UPtrList
            <
            const GeometricField<Type, fvsPatchField, surfaceMesh>
            >&
        );
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include "surfaceMeshWriterTemplates.C"
//#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceMeshWriterI.hxx>

#endif // !_surfaceMeshWriter_Header
