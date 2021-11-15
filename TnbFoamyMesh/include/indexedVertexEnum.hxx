#pragma once
#ifndef _indexedVertexEnum_Header
#define _indexedVertexEnum_Header

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
	tnbLib::indexedVertexEnum

Description

SourceFiles
	indexedVertexEnum.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>
#include <NamedEnum.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class indexedVertexEnum
	{
	public:

		enum vertexType
		{
			vtUnassigned = 0,
			vtInternal = 1,
			vtInternalNearBoundary = 2,
			vtInternalSurface = 3,
			vtInternalSurfaceBaffle = 4,
			vtExternalSurfaceBaffle = 5,
			vtInternalFeatureEdge = 6,
			vtInternalFeatureEdgeBaffle = 7,
			vtExternalFeatureEdgeBaffle = 8,
			vtInternalFeaturePoint = 9,
			vtExternalSurface = 10,
			vtExternalFeatureEdge = 11,
			vtExternalFeaturePoint = 12,
			vtFar = 13,
			vtConstrained = 14
		};

		enum vertexMotion
		{
			fixed = 0,
			movable = 1
		};

		static FoamFoamyMesh_EXPORT const tnbLib::NamedEnum<vertexType, 15> vertexTypeNames_;

		static FoamFoamyMesh_EXPORT const tnbLib::NamedEnum<vertexMotion, 2> vertexMotionNames_;

		friend FoamFoamyMesh_EXPORT Ostream& operator<<(tnbLib::Ostream&, const vertexType&);

		friend FoamFoamyMesh_EXPORT Istream& operator>>(tnbLib::Istream&, vertexType&);
	};


	FoamFoamyMesh_EXPORT Istream& operator>>(Istream&, indexedVertexEnum::vertexType&);
	FoamFoamyMesh_EXPORT Ostream& operator<<(Ostream&, const indexedVertexEnum::vertexType&);

	template<>
	inline bool contiguous<indexedVertexEnum>()
	{
		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_indexedVertexEnum_Header
