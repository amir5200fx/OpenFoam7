#pragma once
#ifndef _edgeMeshFormat_Header
#define _edgeMeshFormat_Header

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
	tnbLib::fileFormats::edgeMeshFormat

Description
	Provide a means of reading/writing the single-file OpenFOAM edge format.

Note
   This class provides more methods than the regular edge format interface.

SourceFiles
	edgeMeshFormat.C

\*---------------------------------------------------------------------------*/

#include <edgeMesh.hxx>
#include <Ostream.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class edgeMeshFormat Declaration
		\*---------------------------------------------------------------------------*/

		class edgeMeshFormat
			:
			public edgeMesh
		{
		protected:

			// Protected Member Functions

				//- Write header information
			static FoamFvMesh_EXPORT void writeHeader
			(
				Ostream&,
				const pointField&,
				const edgeList&
			);


		public:

			// Constructors

				//- Construct from file name
			FoamFvMesh_EXPORT edgeMeshFormat(const fileName&);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT edgeMeshFormat(const edgeMeshFormat&) = delete;


			// Selectors

				//- Read file and return edgeMesh
			static autoPtr<edgeMesh> New(const fileName& name)
			{
				return autoPtr<edgeMesh>
					(
						new edgeMeshFormat(name)
						);
			}


			//- Destructor
			virtual ~edgeMeshFormat()
			{}


			// Member Functions

				//- Read edgeMesh components from stream
			static FoamFvMesh_EXPORT bool read
			(
				Istream&,
				pointField&,
				edgeList&
			);

			//- Write edgeMesh components to stream
			static FoamFvMesh_EXPORT Ostream& write
			(
				Ostream&,
				const pointField&,
				const edgeList&
			);

			//- Write edgeMesh with a mimicked IOobject header
			static FoamFvMesh_EXPORT void write(const fileName&, const edgeMesh&);

			//- Read from file
			virtual FoamFvMesh_EXPORT bool read(const fileName&);

			//- Write object
			virtual FoamFvMesh_EXPORT void write(const fileName& name) const
			{
				write(name, *this);
			}


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const edgeMeshFormat&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_edgeMeshFormat_Header
