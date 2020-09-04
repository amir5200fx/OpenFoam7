#pragma once
#ifndef _blockMeshTools_Header
#define _blockMeshTools_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

Namespace
	tnbLib::blockMeshTools

Description
	Tools for parsing label(List) with dictionary lookup.

SourceFiles
	blockMeshTools.C
	blockMeshToolsTemplates.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockMeshTools
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			//- In-place read with dictionary lookup
		void read(Istream&, label&, const dictionary&);

		//- In-place read with dictionary lookup
		template<class T>
		void read(Istream&, List<T>&, const dictionary&);

		//- Return-read with dictionary lookup
		label read(Istream&, const dictionary&);

		//- Return-read with dictionary lookup
		template<class T>
		List<T> read(Istream& is, const dictionary&);

		//- Write with dictionary lookup
		void write(Ostream&, const label, const dictionary&);

		//- Linear search for label entry
		const keyType& findEntry(const dictionary&, const label);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace blockMeshTools
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <blockMeshToolsI.hxx>

//#ifdef NoRepository
//#include <blockMeshToolsTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_blockMeshTools_Header
