#pragma once
#ifndef _WRLsurfaceFormat_Header
#define _WRLsurfaceFormat_Header

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
	tnbLib::fileFormats::WRLsurfaceFormat

Description
	Provide a means of writing VRML97 (wrl) format.

SourceFiles
	WRLsurfaceFormat.C

\*---------------------------------------------------------------------------*/

#include <MeshedSurface.hxx>
#include <MeshedSurfaceProxy.hxx>
#include <UnsortedMeshedSurface.hxx>
#include <WRLsurfaceFormatCore.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							  Class WRLsurfaceFormat Declaration
		\*---------------------------------------------------------------------------*/

		template<class Face>
		class WRLsurfaceFormat
			:
			public MeshedSurface<Face>,
			public WRLsurfaceFormatCore

		{
		public:

			// Constructors

				//- Construct null
			WRLsurfaceFormat();

			//- Disallow default bitwise copy construction
			WRLsurfaceFormat(const WRLsurfaceFormat<Face>&) = delete;


			//- Destructor
			virtual ~WRLsurfaceFormat()
			{}


			// Member Functions

				//- Write surface mesh components by proxy
			static void write(const fileName&, const MeshedSurfaceProxy<Face>&);

			//- Write object file
			virtual void write(const fileName& name) const
			{
				write(name, MeshedSurfaceProxy<Face>(*this));
			}


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const WRLsurfaceFormat<Face>&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <WRLsurfaceFormatI.hxx>

//#ifdef NoRepository
//#include <WRLsurfaceFormat.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_WRLsurfaceFormat_Header
