#pragma once
#ifndef _pointFeatureEdgesTypes_Header
#define _pointFeatureEdgesTypes_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::pointFeatureEdgesTypes

Description
    Holds information on the types of feature edges attached to feature points.

SourceFiles
    pointFeatureEdgesTypes.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <HashTable.hxx>
#include <extendedFeatureEdgeMesh.hxx>
#include <List.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of friend functions and operators

    class pointFeatureEdgesTypes;

    FoamFoamyMesh_EXPORT Ostream& operator<<(Ostream&, const pointFeatureEdgesTypes&);


    /*---------------------------------------------------------------------------*\
                       Class pointFeatureEdgesTypes Declaration
    \*---------------------------------------------------------------------------*/

    //- Hold the types of feature edges attached to the point.
    class pointFeatureEdgesTypes
        :
        public HashTable<label, extendedFeatureEdgeMesh::edgeStatus>
    {
        // Private Data

            //- Reference to the feature edge mesh
        const extendedFeatureEdgeMesh& feMesh_;

        //- Label of the point
        label pointLabel_;


    public:

        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT pointFeatureEdgesTypes
        (
            const extendedFeatureEdgeMesh& feMesh,
            const label pointLabel
        );


        //- Destructor
        FoamFoamyMesh_EXPORT ~pointFeatureEdgesTypes();


        // Member Functions

            //- Fill the pointFeatureEdgesType class with the types of feature
            //  edges that are attached to the point.
		FoamFoamyMesh_EXPORT List<extendedFeatureEdgeMesh::edgeStatus> calcPointFeatureEdgesTypes();


        // Info

        friend FoamFoamyMesh_EXPORT Ostream& operator<<
            (
                Ostream& os,
                const pointFeatureEdgesTypes& p
                );
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointFeatureEdgesTypes_Header
