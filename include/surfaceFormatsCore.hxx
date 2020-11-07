#pragma once
#ifndef _surfaceFormatsCore_Header
#define _surfaceFormatsCore_Header

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

Class
	tnbLib::fileFormats::surfaceFormatsCore

Description
	A collection of helper functions for reading/writing surface formats.

SourceFiles
	surfaceFormatsCore.C

\*---------------------------------------------------------------------------*/

#include <Map.hxx>
#include <HashSet.hxx>
#include <labelList.hxx>
#include <surfZoneList.hxx>
#include <surfZoneIdentifierList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class IFstream;
	class Time;

	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							 Class surfaceFormatsCore Declaration
		\*---------------------------------------------------------------------------*/

		class surfaceFormatsCore
		{
		protected:

			//- Return a list with a single entry,
			//  the size corresponds to that of the container
			template<class Container>
			static List<surfZone> oneZone
			(
				const Container& container,
				const word& name = "zone0"
			)
			{
				return List<surfZone>(1, surfZone(name, container.size(), 0, 0));
			}

			//- Read non-comment line
			static FoamFvMesh_EXPORT string getLineNoComment(IFstream&);


		public:

			// Static Data

				//- The file extension corresponding to 'native' surface format
				//  Normally "ofs" (mnemonic: OF = OpenFOAM, S = Surface)
			static FoamFvMesh_EXPORT word nativeExt;


			// Static Member Functions

			static FoamFvMesh_EXPORT bool checkSupport
			(
				const wordHashSet& available,
				const word& ext,
				const bool verbose,
				const word& functionName
			);

			//- Return the local file name (within time directory)
			//  NEEDS FIXING
			static FoamFvMesh_EXPORT fileName localMeshFileName(const word& surfName = "");

			//- Find instance with surfName
			//  NEEDS FIXING
			static FoamFvMesh_EXPORT fileName findMeshInstance(const Time&, const word& surfName = "");

			//- Find mesh file with surfName
			//  NEEDS FIXING
			static FoamFvMesh_EXPORT fileName findMeshFile(const Time&, const word& surfName = "");


			// Constructors

				//- Construct null
			FoamFvMesh_EXPORT surfaceFormatsCore();


			//- Destructor
			FoamFvMesh_EXPORT virtual ~surfaceFormatsCore();
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_surfaceFormatsCore_Header
