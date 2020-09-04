#pragma once
#ifndef _STARCDsurfaceFormat_Header
#define _STARCDsurfaceFormat_Header

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
	tnbLib::fileFormats::STARCDsurfaceFormat

Description
	Read/write the surface shells from pro-STAR vrt/cel files.

Note
	Uses the extension \a .inp (input) to denote the format.

See also
	tnbLib::meshReaders::STARCD

SourceFiles
	STARCDsurfaceFormat.C

\*---------------------------------------------------------------------------*/

#include <MeshedSurface.hxx>
#include <MeshedSurfaceProxy.hxx>
#include <UnsortedMeshedSurface.hxx>
#include <STARCDsurfaceFormatCore.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							 Class STARCDsurfaceFormat Declaration
		\*---------------------------------------------------------------------------*/

		template<class Face>
		class STARCDsurfaceFormat
			:
			public MeshedSurface<Face>,
			public STARCDsurfaceFormatCore
		{
			// Private Data

				//- STAR-CD identifier for shell shapes (2d elements)
			static const int starcdShellShape_ = 3;

			//- STAR-CD identifier for shell type (shells vs. baffles)
			static const int starcdShellType_ = 4;


			// Private Member Functions

			static inline void writeShell
			(
				Ostream&,
				const Face&,
				const label cellId,
				const label cellTableId
			);


		public:

			// Constructors

				//- Construct from file name
			STARCDsurfaceFormat(const fileName&);

			//- Disallow default bitwise copy construction
			STARCDsurfaceFormat(const STARCDsurfaceFormat<Face>&) = delete;


			// Selectors

				//- Read file and return surface
			static autoPtr<MeshedSurface<Face>> New(const fileName& name)
			{
				return autoPtr<MeshedSurface<Face>>
					(
						new STARCDsurfaceFormat<Face>(name)
						);
			}


			//- Destructor
			virtual ~STARCDsurfaceFormat()
			{}


			// Member Functions

				//- Write surface mesh components by proxy
			static void write(const fileName&, const MeshedSurfaceProxy<Face>&);

			//- Read from file
			virtual bool read(const fileName&);

			//- Write object
			virtual void write(const fileName& name) const
			{
				write(name, MeshedSurfaceProxy<Face>(*this));
			}


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const STARCDsurfaceFormat<Face>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <STARCDsurfaceFormatI.hxx>

//#ifdef NoRepository
//#include <STARCDsurfaceFormat.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STARCDsurfaceFormat_Header
