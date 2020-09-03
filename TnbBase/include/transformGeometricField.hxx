#pragma once
#ifndef _transformGeometricField_Header
#define _transformGeometricField_Header

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

InClass
	tnbLib::transformGeometricField

Description
	Spatial transformation functions for FieldFields.

SourceFiles
	transformGeometricField.C

\*---------------------------------------------------------------------------*/

#include <transform.hxx>
#include <GeometricField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>&,
		const GeometricField<tensor, PatchField, GeoMesh>&,
		const GeometricField<Type, PatchField, GeoMesh>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>&,
		const GeometricField<Type, PatchField, GeoMesh>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>&,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>&,
		const GeometricField<Type, PatchField, GeoMesh>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh>>&,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	);


	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>&,
		const dimensionedTensor&,
		const GeometricField<Type, PatchField, GeoMesh>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const dimensionedTensor&,
		const GeometricField<Type, PatchField, GeoMesh>&
	);

	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh>> transform
	(
		const dimensionedTensor&,
		const tmp<GeometricField<Type, PatchField, GeoMesh>>&
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <transformGeometricFieldI.hxx>

//#ifdef NoRepository
//#include <transformGeometricField.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformGeometricField_Header
