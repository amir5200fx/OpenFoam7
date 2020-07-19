#pragma once
#ifndef _triSurfaceFieldsFwd_Header
#define _triSurfaceFieldsFwd_Header

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

\*---------------------------------------------------------------------------*/

#include <fieldTypes.hxx>
#include <triSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type, class GeoMesh>
	class DimensionedField;

	class triSurfaceGeoMesh;

	typedef tnbLib::DimensionedField<label, triSurfaceGeoMesh>
		triSurfaceLabelField;
	typedef tnbLib::DimensionedField<scalar, triSurfaceGeoMesh>
		triSurfaceScalarField;
	typedef tnbLib::DimensionedField<vector, triSurfaceGeoMesh>
		triSurfaceVectorField;
	typedef tnbLib::DimensionedField<sphericalTensor, triSurfaceGeoMesh>
		triSurfaceSphericalTensorField;
	typedef tnbLib::DimensionedField<symmTensor, triSurfaceGeoMesh>
		triSurfaceSymmTensorField;
	typedef tnbLib::DimensionedField<tensor, triSurfaceGeoMesh>
		triSurfaceTensorField;

	class triSurfacePointGeoMesh;

	typedef tnbLib::DimensionedField<label, triSurfacePointGeoMesh>
		triSurfacePointLabelField;
	typedef tnbLib::DimensionedField<scalar, triSurfacePointGeoMesh>
		triSurfacePointScalarField;
	typedef tnbLib::DimensionedField<vector, triSurfacePointGeoMesh>
		triSurfacePointVectorField;
	typedef tnbLib::DimensionedField<sphericalTensor, triSurfacePointGeoMesh>
		triSurfacePointSphericalTensorField;
	typedef tnbLib::DimensionedField<symmTensor, triSurfacePointGeoMesh>
		triSurfacePointSymmTensorField;
	typedef tnbLib::DimensionedField<tensor, triSurfacePointGeoMesh>
		triSurfacePointTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurfaceFieldsFwd_Header
