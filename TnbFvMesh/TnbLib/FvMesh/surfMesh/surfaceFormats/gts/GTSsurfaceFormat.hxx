#pragma once
#ifndef _GTSsurfaceFormat_Header
#define _GTSsurfaceFormat_Header

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
	tnbLib::fileFormats::GTSsurfaceFormat

Description
	Provide a means of reading/writing GTS format.
	The output is never sorted by zone and is only written if it consists
	entirely of triangles.

SourceFiles
	GTSsurfaceFormat.C

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
							  Class GTSsurfaceFormat Declaration
		\*---------------------------------------------------------------------------*/

		template<class Face>
		class GTSsurfaceFormat
			:
			public UnsortedMeshedSurface<Face>
		{
		public:

			// Constructors

				//- Construct from file name
			GTSsurfaceFormat(const fileName&);

			//- Disallow default bitwise copy construction
			GTSsurfaceFormat(const GTSsurfaceFormat<Face>&) = delete;


			// Selectors

				//- Read file and return surface
			static autoPtr<UnsortedMeshedSurface<Face>> New(const fileName& name)
			{
				return autoPtr<UnsortedMeshedSurface<Face>>
					(
						new GTSsurfaceFormat<Face>(name)
						);
			}


			//- Destructor
			virtual ~GTSsurfaceFormat()
			{}


			// Member Functions

				//- Write MeshedSurface
			static void write(const fileName&, const MeshedSurface<Face>&);

			//- Write UnsortedMeshedSurface, the output remains unsorted
			static void write(const fileName&, const UnsortedMeshedSurface<Face>&);

			//- Read from file
			virtual bool read(const fileName&);

			//- Write object
			virtual void write(const fileName& name) const
			{
				write(name, *this);
			}


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const GTSsurfaceFormat<Face>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GTSsurfaceFormatI.hxx>

//#ifdef NoRepository
//#include <GTSsurfaceFormat.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GTSsurfaceFormat_Header
