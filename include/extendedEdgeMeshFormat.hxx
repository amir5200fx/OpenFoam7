#pragma once
#ifndef _extendedEdgeMeshFormat_Header
#define _extendedEdgeMeshFormat_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::fileFormats::extendedEdgeMeshFormat

Description
	Provide a means of reading/writing the single-file OpenFOAM
	extendedEdgeMesh format

SourceFiles
	extendedEdgeMeshFormat.C

\*---------------------------------------------------------------------------*/

#include <extendedEdgeMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
								Class extendedEdgeMeshFormat Declaration
		\*---------------------------------------------------------------------------*/

		class extendedEdgeMeshFormat
			:
			public extendedEdgeMesh
		{
		public:

			// Constructors

				//- Construct from file name
			extendedEdgeMeshFormat(const fileName&);

			//- Disallow default bitwise copy construction
			extendedEdgeMeshFormat(const extendedEdgeMeshFormat&) = delete;


			//- Destructor
			virtual ~extendedEdgeMeshFormat()
			{}


			// Member Functions

				//- Read from file
			virtual bool read(const fileName&);


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const extendedEdgeMeshFormat&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_extendedEdgeMeshFormat_Header
