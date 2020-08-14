#pragma once
#ifndef _reconstructLagrangian_Header
#define _reconstructLagrangian_Header

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
	tnbLib::reconstructLagrangian

Description

SourceFiles
	reconstructLagrangianPositions.C
	reconstructLagrangianFields.C

\*---------------------------------------------------------------------------*/

#include <cloud.hxx>
#include <polyMesh.hxx>
#include <IOobjectList.hxx>
#include <CompactIOField.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void reconstructLagrangianPositions
	(
		const polyMesh& mesh,
		const word& cloudName,
		const PtrList<fvMesh>& meshes,
		const PtrList<labelIOList>& faceProcAddressing,
		const PtrList<labelIOList>& cellProcAddressing
	);


	template<class Type>
	tmp<IOField<Type>> reconstructLagrangianField
	(
		const word& cloudName,
		const polyMesh& mesh,
		const PtrList<fvMesh>& meshes,
		const word& fieldName
	);


	template<class Type>
	tmp<CompactIOField<Field<Type>, Type>> reconstructLagrangianFieldField
	(
		const word& cloudName,
		const polyMesh& mesh,
		const PtrList<fvMesh>& meshes,
		const word& fieldName
	);


	template<class Type>
	void reconstructLagrangianFields
	(
		const word& cloudName,
		const polyMesh& mesh,
		const PtrList<fvMesh>& meshes,
		const IOobjectList& objects,
		const HashSet<word>& selectedFields
	);


	template<class Type>
	void reconstructLagrangianFieldFields
	(
		const word& cloudName,
		const polyMesh& mesh,
		const PtrList<fvMesh>& meshes,
		const IOobjectList& objects,
		const HashSet<word>& selectedFields
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <reconstructLagrangianFields.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_reconstructLagrangian_Header
