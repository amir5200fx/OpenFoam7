#pragma once
#ifndef _surfZoneIOList_Header
#define _surfZoneIOList_Header

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
	tnbLib::surfZoneIOList

Description
	IOobject for a surfZoneList

SourceFiles
	surfZoneIOList.C

\*---------------------------------------------------------------------------*/

#include <surfZoneList.hxx>
#include <regIOobject.hxx>
#include <faceList.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class surfZoneIOList;

	FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfZoneIOList&);


	/*---------------------------------------------------------------------------*\
						  Class surfZoneIOList Declaration
	\*---------------------------------------------------------------------------*/

	class surfZoneIOList
		:
		public surfZoneList,
		public regIOobject
	{
	public:

		//- Runtime type information
		/*TypeName("surfZoneList");*/
		static const char* typeName_() { return "surfZoneList"; }
		static FoamFvMesh_EXPORT const ::tnbLib::word typeName;
		static FoamFvMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		FoamFvMesh_EXPORT explicit surfZoneIOList(const IOobject&);

		//- Construct from IOobject and surfZoneList
		FoamFvMesh_EXPORT surfZoneIOList(const IOobject&, const surfZoneList&);

		//- Construct from IOobject and surfZoneList
		FoamFvMesh_EXPORT surfZoneIOList(const IOobject&, surfZoneList&&);

		//- Disallow default bitwise copy construction
		FoamFvMesh_EXPORT surfZoneIOList(const surfZoneIOList&) = delete;


		//- Destructor
		FoamFvMesh_EXPORT ~surfZoneIOList();


		// Member Functions

			//- writeData member function required by regIOobject
		FoamFvMesh_EXPORT bool writeData(Ostream&) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFvMesh_EXPORT void operator=(const surfZoneIOList&) = delete;


		// IOstream Operators

		friend FoamFvMesh_EXPORT Ostream& operator<<(Ostream&, const surfZoneIOList&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfZoneIOList_Header
