#include <zoltanRenumber.hxx>

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

Class
	Foam::zoltanRenumber

Description
	Renumber using Zoltan

	Zoltan install:
	- in your ~/.bashrc:
			export ZOLTAN_ARCH_DIR=\
				$WM_THIRD_PARTY_DIR/platforms/linux64Gcc/Zoltan_XXX
	- unpack into $WM_THIRD_PARTY_DIR
	- cd Zoltan_XXX
	- mkdir build
	- cd build
	- export CCFLAGS="-fPIC"
	- export CXXFLAGS="-fPIC"
	- export CFLAGS="-fPIC"
	- export LDFLAGS="-shared"
	- ../configure \
		--prefix=$ZOLTAN_ARCH_DIR \
		--with-ccflags=-fPIC --with-cxxflags=-fPIC --with-ldflags=-shared

SourceFiles
	zoltanRenumber.C

\*---------------------------------------------------------------------------*/

#include <addToRunTimeSelectionTable.hxx>
#include <IFstream.hxx>
#include <labelIOList.hxx>
#include <polyMesh.hxx>
#include <globalMeshData.hxx>
#include <globalIndex.hxx>
#include <uint.hxx>
#include <PstreamGlobals.hxx>