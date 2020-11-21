#pragma once
#ifndef _regionProperties_Header
#define _regionProperties_Header

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
	tnbLib::regionProperties

Description
	Simple class to hold region information for coupled region simulations.

	Gives per physics ('fluid', 'solid') the names of the regions. There
	is no assumption on this level that one region should only have one
	set of physics.

SourceFiles
	regionProperties.C

\*---------------------------------------------------------------------------*/

#include <Time.hxx>
#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class regionProperties Declaration
	\*---------------------------------------------------------------------------*/

	class regionProperties
		:
		public HashTable<wordList>
	{
	public:

		// Constructors

			//- Construct from components
		FoamLagrangian_EXPORT regionProperties(const Time& runTime);

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT regionProperties(const regionProperties&) = delete;


		//- Destructor
		FoamLagrangian_EXPORT ~regionProperties();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const regionProperties&) = delete;
	};


	FoamLagrangian_EXPORT const word& regionDir(const word& regionName);

	FoamLagrangian_EXPORT wordList selectRegionNames(const argList& args, const Time& runTime);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_regionProperties_Header
