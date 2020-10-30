#pragma once
#ifndef _STARCDedgeFormat_Header
#define _STARCDedgeFormat_Header

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
	tnbLib::fileFormats::STARCDedgeFormat

Description
	Read/write the lines from pro-STAR vrt/cel files.

Note
	Uses the extension \a .inp (input) to denote the format.

See also
	tnbLib::meshReaders::STARCD

SourceFiles
	STARCDedgeFormat.C

\*---------------------------------------------------------------------------*/

#include <edgeMesh.hxx>
#include <STARCDCore.hxx>

#include <IFstream.hxx>
#include <Ostream.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class STARCDedgeFormat Declaration
		\*---------------------------------------------------------------------------*/

		class STARCDedgeFormat
			:
			public edgeMesh,
			public STARCDCore
		{
			// Private Data

				//- STAR-CD identifier for line shapes (1d elements)
			static const int starcdLineShape_ = 2;

			//- STAR-CD identifier for line type
			static const int starcdLineType_ = 5;


			// Private Member Functions

			static inline void writeLines
			(
				Ostream&,
				const edgeList&
			);


		protected:

			// Protected Member Functions

			static FoamFvMesh_EXPORT void writeCase
			(
				Ostream&,
				const pointField&,
				const label nEdges
			);


		public:

			// Constructors

				//- Construct from file name
			FoamFvMesh_EXPORT STARCDedgeFormat(const fileName&);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT STARCDedgeFormat(const STARCDedgeFormat&) = delete;


			// Selectors

				//- Read file and return edgeMesh
			static autoPtr<edgeMesh> New(const fileName& name)
			{
				return autoPtr<edgeMesh>
					(
						new STARCDedgeFormat(name)
						);
			}


			//- Destructor
			virtual ~STARCDedgeFormat()
			{}


			// Member Functions

				//- Write edge mesh
			static FoamFvMesh_EXPORT void write(const fileName&, const edgeMesh&);

			//- Read from file
			FoamFvMesh_EXPORT virtual bool read(const fileName&);

			//- Write object
			virtual void write(const fileName& name) const
			{
				write(name, *this);
			}


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const STARCDedgeFormat&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDedgeFormat_Header
