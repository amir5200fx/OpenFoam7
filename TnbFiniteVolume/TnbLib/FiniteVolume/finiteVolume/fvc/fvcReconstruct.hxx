#pragma once
#ifndef _fvcReconstruct_Header
#define _fvcReconstruct_Header

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

InNamespace
	tnbLib::fvc

Description
	Reconstruct volField from a face flux field.

SourceFiles
	fvcReconstruct.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <tmp.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		template<class Type>
		tmp
			<
			GeometricField
			<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
			> reconstruct
			(
				const GeometricField<Type, fvsPatchField, surfaceMesh>&
			);

		template<class Type>
		tmp
			<
			GeometricField
			<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
			> reconstruct
			(
				const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>&
			);

		tmp<volScalarField> reconstructMag(const surfaceScalarField&);
		tmp<volScalarField> reconstructMag(const tmp<surfaceScalarField>&);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvcReconstructI.hxx>
//#include <fvcSimpleReconstruct_Imp.hxx>

//#ifdef NoRepository
//#include <fvcReconstruct.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvcReconstruct_Header
