#pragma once
#ifndef _writePointSet_Header
#define _writePointSet_Header

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
    Write pointSet to vtk polydata file. Only one data which is original
    pointID.

SourceFiles
    writePointSet.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <primitiveMesh.hxx>
#include <pointSet.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	//- Write pointSet to vtk polydata file.
	//  Only one data which is original pointID.
	void writePointSet
	(
		const bool binary,
		const primitiveMesh& mesh,
		const topoSet& set,
		const fileName& fileName
	);

} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_writePointSet_Header
