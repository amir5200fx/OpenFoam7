#pragma once
#ifndef _ensightField_Header
#define _ensightField_Header

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

InApplication
    foamToEnsight

Description

SourceFiles
    ensightField.C

\*---------------------------------------------------------------------------*/

#include "ensightMesh.hxx"

#include <fvMeshSubset.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	//- Wrapper to get hold of the field or the subsetted field
	template<class Type>
	tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
		volField
		(
			const tnbLib::fvMeshSubset&,
			const tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>& vf
		);


	template<class Type>
	void ensightField
	(
		const tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>& vf,
		const tnbLib::ensightMesh& eMesh,
		const tnbLib::fileName& postProcPath,
		const tnbLib::word& prepend,
		const tnbLib::label timeIndex,
		const bool binary,
		const bool nodeValues,
		tnbLib::Ostream& ensightCaseFile
	);


	template<class Type>
	void writePatchField
	(
		const tnbLib::word& fieldName,
		const tnbLib::Field<Type>& pf,
		const tnbLib::word& patchName,
		const tnbLib::ensightMesh& eMesh,
		const tnbLib::fileName& postProcPath,
		const tnbLib::word& prepend,
		const tnbLib::label timeIndex,
		tnbLib::Ostream& ensightCaseFile
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "ensightFieldI.hxx"

//#ifdef NoRepository
//#include "ensightField.C"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightField_Header
