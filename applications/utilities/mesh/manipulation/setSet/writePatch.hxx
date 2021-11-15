#pragma once
#ifndef _writePatch_Header
#define _writePatch_Header

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
    tnbLib::writePatch

Description
    Write faceSet to vtk polydata file. Only one data which is original
    faceID.

SourceFiles
    writePatch.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <primitiveMesh.hxx>
#include <primitiveFacePatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Write faceSet
	void writePatch
	(
		const bool binary,
		const word& setName,
		const primitiveFacePatch& fp,
		const word& fieldName,
		labelList& fieldValues,
		const fileName& fileName
	);

} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_writePatch_Header
