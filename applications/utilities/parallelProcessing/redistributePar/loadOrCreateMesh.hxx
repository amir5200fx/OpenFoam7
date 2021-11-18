#pragma once
#ifndef _loadOrCreateMesh_Header
#define _loadOrCreateMesh_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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
    Load or create (0 size) a mesh. Used in distributing meshes to a
    larger number of processors

SourceFiles
    loadOrCreateMesh.C

\*---------------------------------------------------------------------------*/

#define FoamIOPtrList_EXPORT_DEFINE
#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <includeAllModules.hxx>

#include <fvMesh.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
namespace tnbLib
{

	//- Load (if it exists) or create zero cell mesh given an IOobject:
	//      name     : regionName
	//      instance : exact directory where to find mesh (i.e. does not
	//                 do a findInstance
	autoPtr<fvMesh> loadOrCreateMesh(const IOobject& io);

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_loadOrCreateMesh_Header