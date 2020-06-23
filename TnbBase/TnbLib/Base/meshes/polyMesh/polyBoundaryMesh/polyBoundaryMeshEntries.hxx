#pragma once
#ifndef _polyBoundaryMeshEntries_Header
#define _polyBoundaryMeshEntries_Header

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
	tnbLib::polyBoundaryMeshEntries

Description
	tnbLib::polyBoundaryMeshEntries

SourceFiles
	polyBoundaryMeshEntries.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <PtrList.hxx>
#include <entry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class polyBoundaryMeshEntries
		:
		public regIOobject,
		public PtrList<entry>
	{

	public:

		//- Runtime type information
		TypeName("polyBoundaryMesh");


		// Constructors

		explicit polyBoundaryMeshEntries(const IOobject& io)
			:
			regIOobject(io),
			PtrList<entry>(readStream(typeName))
		{
			close();
		}


		// Member Functions

		bool writeData(Ostream&) const
		{
			NotImplemented;
			return false;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyBoundaryMeshEntries_Header
