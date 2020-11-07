#pragma once
#ifndef _findRefCell_Header
#define _findRefCell_Header

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
	tnbLib

Description
	Find the reference cell nearest (in index) to the given cell but which
	is not on a cyclic, symmetry or processor patch.

SourceFiles
	findRefCell.C

\*---------------------------------------------------------------------------*/

#include <label.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	//- If the field fieldRef needs referencing find the reference cell nearest
	//  (in index) to the given cell looked-up for field, but which is not on a
	//  cyclic, symmetry or processor patch and return true, otherwise return false.
	FoamFiniteVolume_EXPORT bool setRefCell
	(
		const volScalarField& field,
		const volScalarField& fieldRef,
		const dictionary& dict,
		label& refCelli,
		scalar& refValue,
		const bool forceReference = false
	);

	//- If the field needs referencing find the reference cell nearest
	//  (in index) to the given cell looked-up for field, but which is not on a
	//  cyclic, symmetry or processor patch and return true, otherwise return false.
	FoamFiniteVolume_EXPORT bool setRefCell
	(
		const volScalarField& field,
		const dictionary& dict,
		label& refCelli,
		scalar& refValue,
		const bool forceReference = false
	);

	//- Return the current value of field in the reference cell
	FoamFiniteVolume_EXPORT scalar getRefCellValue
	(
		const volScalarField& field,
		const label refCelli
	);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_findRefCell_Header
