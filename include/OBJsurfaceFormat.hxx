#pragma once
#ifndef _OBJsurfaceFormat_Header
#define _OBJsurfaceFormat_Header

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
	tnbLib::fileFormats::OBJsurfaceFormat

Description
	Provide a means of reading/writing Alias/Wavefront OBJ format.

	Does not handle negative face indices.

SourceFiles
	OBJsurfaceFormat.C

\*---------------------------------------------------------------------------*/

#include <MeshedSurface.hxx>
#include <MeshedSurfaceProxy.hxx>
#include <UnsortedMeshedSurface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class OBJsurfaceFormat Declaration
		\*---------------------------------------------------------------------------*/

		template<class Face>
		class OBJsurfaceFormat
			:
			public MeshedSurface<Face>
		{
		public:

			// Constructors

				//- Construct from file name
			OBJsurfaceFormat(const fileName&);

			//- Disallow default bitwise copy construction
			OBJsurfaceFormat(const OBJsurfaceFormat<Face>&) = delete;


			// Selectors

				//- Read file and return surface
			static autoPtr<MeshedSurface<Face>> New(const fileName& name)
			{
				return autoPtr<MeshedSurface<Face>>
					(
						new OBJsurfaceFormat<Face>(name)
						);
			}


			//- Destructor
			virtual ~OBJsurfaceFormat()
			{}


			// Member Functions

				//- Write surface mesh components by proxy
			static void write(const fileName&, const MeshedSurfaceProxy<Face>&);

			//- Read from file
			virtual bool read(const fileName&);

			//- Write object file
			virtual void write(const fileName& name) const
			{
				write(name, MeshedSurfaceProxy<Face>(*this));
			}


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const OBJsurfaceFormat<Face>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <OBJsurfaceFormatI.hxx>

//#ifdef NoRepository
//#include <OBJsurfaceFormat.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OBJsurfaceFormat_Header
