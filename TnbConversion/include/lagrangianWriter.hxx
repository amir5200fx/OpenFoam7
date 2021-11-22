#pragma once
#ifndef _lagrangianWriter_Header
#define _lagrangianWriter_Header

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
    tnbLib::lagrangianWriter

Description
    Write fields (internal).

SourceFiles
    lagrangianWriter.C
    lagrangianWriterTemplates.C

\*---------------------------------------------------------------------------*/

#include <vtkMesh.hxx>
#include <OFstream.hxx>
#include <Cloud.hxx>
#include <volFields.hxx>
#include <pointFields.hxx>
#include <writeFuns.hxx>
////#include <writeFuns.hxx> this header was included in 
//                           "lagrangianWriteTemplates.cxx"
//                            which is moved here but it is 
//                            not needed so has been disabled by Payvand

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class volPointInterpolation;

    /*---------------------------------------------------------------------------*\
                               Class lagrangianWriter Declaration
    \*---------------------------------------------------------------------------*/

    class lagrangianWriter
    {
        const vtkMesh& vMesh_;

        const bool binary_;

        const fileName fName_;

        const word cloudName_;

        std::ofstream os_;

        label nParcels_;


    public:

        // Constructors

            //- Construct from components
        lagrangianWriter
        (
            const vtkMesh&,
            const bool binary,
            const fileName&,
            const word&,
            const bool dummyCloud
        );


        // Member Functions

        std::ofstream& os()
        {
            return os_;
        }

        void writeParcelHeader(const label nFields);

        //- Write IOField
        template<class Type>
        void writeIOField(const wordList&);
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//#ifdef NoRepository
//#include "lagrangianWriterTemplates.C"
//#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <lagrangianWriterI.hxx>

#endif // !_lagrangianWriter_Header
