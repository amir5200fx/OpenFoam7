#pragma once
#ifndef _IOMRFZoneList_Header
#define _IOMRFZoneList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
	tnbLib::IOMRFZoneList

Description
	List of MRF zones with IO functionality.  MRF zones are specified by a list
	of dictionary entries, e.g.

	\verbatim
	zone1
	{
		cellZone    rotor1;
		active      yes;
		...
	}

	zone2
	{
		cellZone    rotor2;
		active      yes;
		...
	}
	\endverbatim

SourceFiles
	IOMRFZoneList.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>
#include <MRFZoneList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class IOMRFZoneList Declaration
	\*---------------------------------------------------------------------------*/

	class IOMRFZoneList
		:
		public IOdictionary,
		public MRFZoneList
	{
		// Private Member Functions

			//- Create IO object if dictionary is present
		FoamFiniteVolume_EXPORT IOobject createIOobject(const fvMesh& mesh) const;


	public:

		// Constructors

			//- Construct from mesh
		FoamFiniteVolume_EXPORT IOMRFZoneList(const fvMesh& mesh);

		//- Disallow default bitwise copy construction
		FoamFiniteVolume_EXPORT IOMRFZoneList(const IOMRFZoneList&) = delete;


		//- Destructor
		virtual ~IOMRFZoneList()
		{}


		// Member Functions

			//- Read dictionary
		FoamFiniteVolume_EXPORT virtual bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamFiniteVolume_EXPORT void operator=(const IOMRFZoneList&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IOMRFZoneList_Header
