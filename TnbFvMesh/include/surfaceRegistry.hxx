#pragma once
#ifndef _surfaceRegistry_Header
#define _surfaceRegistry_Header

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
	tnbLib::surfaceRegistry

Description
	Wraps the normal objectRegistry with a local instance for %surfaces.

SourceFiles
	surfaceRegistry.C

\*---------------------------------------------------------------------------*/

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class surfaceRegistry Declaration
	\*---------------------------------------------------------------------------*/

	class surfaceRegistry
		:
		public objectRegistry
	{
	public:

		//- Runtime type information
		/*TypeName("surfaceRegistry");*/
		static const char* typeName_() { return "surfaceRegistry"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- The prefix to local: %surfaces
		static FoamFvMesh_EXPORT const word prefix;

		//- The default surface name: %default
		static FoamFvMesh_EXPORT word defaultName;


		// Constructors

			//- Construct for the given objectRegistry and named surface
		FoamFvMesh_EXPORT surfaceRegistry(const objectRegistry&, const word& surfName = "");

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT surfaceRegistry(const surfaceRegistry&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT virtual ~surfaceRegistry();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const surfaceRegistry&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceRegistry_Header
