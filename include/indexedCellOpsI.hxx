#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

#include <Pstream.hxx>

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class CellType>
tnbLib::label CGAL::indexedCellOps::dualVertexMasterProc(const CellType& c)
{
	if (!c->parallelDualVertex())
	{
		return -1;
	}

	// The master processor is the lowest numbered of the four on this tet.

	int masterProc = tnbLib::Pstream::nProcs() + 1;

	for (tnbLib::label vI = 0; vI < 4; ++vI)
	{
		if (c->vertex(vI)->referred())
		{
			masterProc = min(masterProc, c->vertex(vI)->procIndex());
		}
		else
		{
			masterProc = min(masterProc, tnbLib::Pstream::myProcNo());
		}
	}

	return masterProc;
}


template<class CellType>
tnbLib::FixedList<tnbLib::label, 4>
CGAL::indexedCellOps::processorsAttached(const CellType& c)
{
	tnbLib::FixedList<tnbLib::label, 4> procsAttached(tnbLib::Pstream::myProcNo());

	if (!c->parallelDualVertex())
	{
		return procsAttached;
	}

	for (tnbLib::label vI = 0; vI < 4; ++vI)
	{
		if (c->vertex(vI)->referred())
		{
			procsAttached[vI] = c->vertex(vI)->procIndex();
		}
	}

	return procsAttached;
}


// ************************************************************************* //
