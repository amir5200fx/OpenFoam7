#pragma once
#ifndef _searchableBoxFeatures_Header
#define _searchableBoxFeatures_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
    tnbLib::searchableBoxFeatures

Description

SourceFiles
    searchableBoxFeatures.C

\*---------------------------------------------------------------------------*/

#include <searchableSurfaceFeatures.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                       Class searchableBoxFeatures Declaration
    \*---------------------------------------------------------------------------*/

    class searchableBoxFeatures
        :
        public searchableSurfaceFeatures
    {
    private:

        // Private Member Data

            //- Which side of the box to mesh
        const extendedFeatureEdgeMesh::sideVolumeType mode_;


    public:

        //- Runtime type information
        /*TypeName("searchableBoxFeatures");*/
        static const char* typeName_() { return "searchableBoxFeatures"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Constructors

            //- Construct from searchable surface and dictionary
        FoamFoamyMesh_EXPORT searchableBoxFeatures
        (
            const searchableSurface& surface,
            const dictionary& dict
        );

        //- Disallow default bitwise copy construction
        searchableBoxFeatures(const searchableBoxFeatures&) = delete;


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~searchableBoxFeatures();


        // Member Functions

            //- Return true for a searchable box having features
        virtual bool hasFeatures() const
        {
            return true;
        }

        //- Return an extendedFeatureEdgeMesh containing the features
		FoamFoamyMesh_EXPORT virtual autoPtr<extendedFeatureEdgeMesh> features() const;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const searchableBoxFeatures&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_searchableBoxFeatures_Header
