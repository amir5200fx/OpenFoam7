#pragma once
#ifndef _NASedgeFormat_Header
#define _NASedgeFormat_Header

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
	tnbLib::fileFormats::NASedgeFormat

Description
	Nastran edge reader.

SourceFiles
	NASedgeFormat.C

\*---------------------------------------------------------------------------*/

#include <edgeMesh.hxx>
#include <NASCore.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class NASedgeFormat Declaration
		\*---------------------------------------------------------------------------*/

		class NASedgeFormat
			:
			public edgeMesh,
			public NASCore
		{
		public:

			// Constructors

				//- Construct from file name
			FoamFvMesh_EXPORT NASedgeFormat(const fileName&);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT NASedgeFormat(const NASedgeFormat&) = delete;


			// Selectors

				//- Read file and return edge mesh
			static autoPtr<edgeMesh> New(const fileName& name)
			{
				return autoPtr<edgeMesh>
					(
						new NASedgeFormat(name)
						);
			}


			//- Destructor
			virtual ~NASedgeFormat()
			{}


			// Member Functions

				//- Read from a file
			FoamFvMesh_EXPORT virtual bool read(const fileName&);


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const NASedgeFormat&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NASedgeFormat_Header
