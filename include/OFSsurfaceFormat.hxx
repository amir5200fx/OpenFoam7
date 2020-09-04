#pragma once
#ifndef _OFSsurfaceFormat_Header
#define _OFSsurfaceFormat_Header

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
	tnbLib::fileFormats::OFSsurfaceFormat

Description
	Provide a means of reading/writing the single-file OpenFOAM surface format.

Note
	This class provides more methods than the regular surface format interface.

SourceFiles
	OFSsurfaceFormat.C

\*---------------------------------------------------------------------------*/

#include <Ostream.hxx>
#include <OFstream.hxx>
#include <MeshedSurface.hxx>
#include <MeshedSurfaceProxy.hxx>
#include <UnsortedMeshedSurface.hxx>
#include <OFSsurfaceFormatCore.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class OFSsurfaceFormat Declaration
		\*---------------------------------------------------------------------------*/

		template<class Face>
		class OFSsurfaceFormat
			:
			public MeshedSurface<Face>,
			public OFSsurfaceFormatCore
		{
		public:

			// Constructors

				//- Construct from file name
			OFSsurfaceFormat(const fileName&);

			//- Disallow default bitwise copy construction
			OFSsurfaceFormat(const OFSsurfaceFormat<Face>&) = delete;


			// Selectors

				//- Read file and return surface
			static autoPtr<MeshedSurface<Face>> New(const fileName& name)
			{
				return autoPtr<MeshedSurface<Face>>
					(
						new OFSsurfaceFormat<Face>(name)
						);
			}


			//- Destructor
			virtual ~OFSsurfaceFormat()
			{}



			// Member Functions

				//- Read surface mesh components
			static bool read
			(
				Istream&,
				pointField&,
				List<Face>&,
				List<surfZone>&
			);

			//- Read MeshedSurface
			static bool read
			(
				Istream&,
				MeshedSurface<Face>&
			);

			//- Read UnsortedMeshedSurface
			//  The output is sorted by zones
			static bool read
			(
				Istream&,
				UnsortedMeshedSurface<Face>&
			);

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
			void operator=(const OFSsurfaceFormat<Face>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <OFSsurfaceFormatI.hxx>

//#ifdef NoRepository
//#include <OFSsurfaceFormat.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OFSsurfaceFormat_Header
