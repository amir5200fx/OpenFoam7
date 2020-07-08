#pragma once
#ifndef _data_Header
#define _data_Header

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
	tnbLib::data

Description
	Database for solution and other reduced data.

	fvMesh is derived from data so that all fields have access to the data from
	the mesh reference they hold.

SourceFiles
	data.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
								Class data Declaration
	\*---------------------------------------------------------------------------*/

	class data
		:
		public IOdictionary
	{
		// Private Member Functions

			//- Disallow default bitwise copy construction
		data(const data&) = delete;

		//- Disallow default bitwise assignment
		void operator=(const data&) = delete;


	public:

		//- Debug switch
		static int debug;


		// Constructors

			//- Construct for objectRegistry
		data(const objectRegistry& obr);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_data_Header
