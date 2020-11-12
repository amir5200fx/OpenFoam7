#pragma once
#ifndef _reactingMultiphaseCloud_Header
#define _reactingMultiphaseCloud_Header

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
	tnbLib::reactingMultiphaseCloud

Description
	Virtual abstract base class for templated reactingMultiphaseCloud

SourceFiles
	reactingMultiphaseCloud.C

\*---------------------------------------------------------------------------*/

#include <typeInfo.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class reactingMultiphaseCloud Declaration
	\*---------------------------------------------------------------------------*/

	class reactingMultiphaseCloud
	{
	public:

		//- Runtime type information
		//TypeName("reactingMultiphaseCloud");
		static const char* typeName_() { return "reactingMultiphaseCloud"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT reactingMultiphaseCloud();

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT reactingMultiphaseCloud(const reactingMultiphaseCloud&) = delete;


		//- Destructor
		FoamLagrangian_EXPORT virtual ~reactingMultiphaseCloud();


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const reactingMultiphaseCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_reactingMultiphaseCloud_Header
