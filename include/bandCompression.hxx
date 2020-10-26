#pragma once
#ifndef _bandCompression_Header
#define _bandCompression_Header

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
	The bandCompression function renumbers the addressing such that the
	band of the matrix is reduced. The algorithm uses a simple search
	through the neighbour list in order of connectivity.
	(CutHill-McKee algorithm)

SourceFiles
	bandCompression.C

\*---------------------------------------------------------------------------*/

#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	//- Renumbers the addressing to reduce the band of the matrix.
	//  The algorithm uses a simple search through the neighbour list
	//  Returns the order in which the cells need to be visited (i.e. ordered to
	//  original)
	FoamBase_EXPORT labelList bandCompression(const labelListList& addressing);

	//- Renumber with addressing in losort form (neighbour + start in neighbour)
	FoamBase_EXPORT labelList bandCompression(const labelList& cellCells, const labelList& offsets);

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_bandCompression_Header
