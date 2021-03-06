#pragma once
#ifndef _STLsurfaceFormatCore_Header
#define _STLsurfaceFormatCore_Header

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
	tnbLib::fileFormats::STLsurfaceFormatCore

Description
	Internal class used by the STLsurfaceFormat

SourceFiles
	STLsurfaceFormatCore.C
	STLsurfaceFormatASCII.L

\*---------------------------------------------------------------------------*/

#include <STLtriangle.hxx>
#include <triFace.hxx>
#include <IFstream.hxx>
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileFormats
	{

		/*---------------------------------------------------------------------------*\
							Class STLsurfaceFormatCore Declaration
		\*---------------------------------------------------------------------------*/

		class STLsurfaceFormatCore
		{
			// Private Data

			bool sorted_;

			//- The points supporting the facets
			pointField points_;

			//- The zones associated with the faces
			List<label> zoneIds_;

			//- The solid names, in the order of their first appearance
			List<word> names_;

			//- The solid count, in the order of their first appearance
			List<label> sizes_;


			// Private Member Functions

				//- Determine the file type
			static FoamFvMesh_EXPORT int detectBINARY(const fileName&);

			//- Read ASCII
			FoamFvMesh_EXPORT bool readASCII(istream&, const off_t);

			//- Read BINARY
			FoamFvMesh_EXPORT bool readBINARY(istream&, const off_t);


		public:

			// Static Data

				//- The number of bytes in the STL binary header
			static const unsigned int headerSize = 80;


			// Static Member Functions

				//- Write "STL binary file" and number of triangles to stream
			static FoamFvMesh_EXPORT void writeHeaderBINARY(ostream&, unsigned int);


			// Constructors

				//- Read from file, filling in the information
			FoamFvMesh_EXPORT STLsurfaceFormatCore(const fileName&);

			//- Disallow default bitwise copy construction
			FoamFvMesh_EXPORT STLsurfaceFormatCore(const STLsurfaceFormatCore&) = delete;


			//- Destructor
			FoamFvMesh_EXPORT ~STLsurfaceFormatCore();


			// Member Functions

				//- File read was already sorted
			bool sorted() const
			{
				return sorted_;
			}

			//- Flush all values
			void clear()
			{
				sorted_ = true;
				points_.clear();
				zoneIds_.clear();
				names_.clear();
				sizes_.clear();
			}

			//- Return full access to the points
			pointField& points()
			{
				return points_;
			}

			//- Return full access to the zoneIds
			List<label>& zoneIds()
			{
				return zoneIds_;
			}

			//- The list of solid names in the order of their first appearance
			List<word>& names()
			{
				return names_;
			}

			//- The list of solid sizes in the order of their first appearance
			List<label>& sizes()
			{
				return sizes_;
			}


			// Member Operators

				//- Disallow default bitwise assignment
			FoamFvMesh_EXPORT void operator=(const STLsurfaceFormatCore&) = delete;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileFormats
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_STLsurfaceFormatCore_Header
