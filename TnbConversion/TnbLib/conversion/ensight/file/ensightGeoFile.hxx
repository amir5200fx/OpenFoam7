#pragma once
#ifndef _ensightGeoFile_Header
#define _ensightGeoFile_Header

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
	tnbLib::ensightGeoFile

Description
	Specialized Ensight output with extra geometry file header

\*---------------------------------------------------------------------------*/

#include <ensightFile.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class ensightGeoFile Declaration
	\*---------------------------------------------------------------------------*/

	class ensightGeoFile
		:
		public ensightFile
	{
	public:

		// Constructors

			//- Construct from pathname
		FoamConversion_EXPORT ensightGeoFile
		(
			const fileName& pathname,
			IOstream::streamFormat format = IOstream::BINARY
		);

		//- Disallow default bitwise copy construction
		FoamConversion_EXPORT ensightGeoFile(const ensightGeoFile&);



		//- Destructor
		FoamConversion_EXPORT ~ensightGeoFile();


		// Output

			//- Write keyword with trailing newline
		FoamConversion_EXPORT virtual Ostream& writeKeyword(const string& key);


		// Member Operators

			//- Disallow default bitwise assignment
		FoamConversion_EXPORT void operator=(const ensightGeoFile&) = delete;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_ensightGeoFile_Header
