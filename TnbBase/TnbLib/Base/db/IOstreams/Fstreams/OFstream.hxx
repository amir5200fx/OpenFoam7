#pragma once
#ifndef _OFstream_Header
#define _OFstream_Header

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
	tnbLib::OFstream

Description
	Output to file stream.

SourceFiles
	OFstream.C

\*---------------------------------------------------------------------------*/

#include <OSstream.hxx>
#include <fileName.hxx>
#include <className.hxx>

#include <fstream>
using std::ofstream;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class OFstream;

	/*---------------------------------------------------------------------------*\
						  Class OFstreamAllocator Declaration
	\*---------------------------------------------------------------------------*/

	//- A std::ostream with ability to handle compressed files
	class OFstreamAllocator
	{
		friend class OFstream;

		ostream* ofPtr_;

		// Constructors

			//- Construct from pathname
		FoamBase_EXPORT OFstreamAllocator
		(
			const fileName& pathname,
			IOstream::compressionType compression = IOstream::UNCOMPRESSED,
			const bool append = false
		);

		//- Destructor
		FoamBase_EXPORT ~OFstreamAllocator();

	};


	/*---------------------------------------------------------------------------*\
							  Class OFstream Declaration
	\*---------------------------------------------------------------------------*/

	class OFstream
		:
		private OFstreamAllocator,
		public OSstream
	{
		// Private Data

		fileName pathname_;


	public:

		// Declare name of the class and its debug switch
		//ClassName("OFstream");
		static const char* typeName_() { return "OFstream"; } 
		static FoamBase_EXPORT const ::tnbLib::word typeName; 
		static FoamBase_EXPORT int debug;


		// Constructors

			//- Construct from pathname
		FoamBase_EXPORT OFstream
		(
			const fileName& pathname,
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED,
			const bool append = false
		);


		//- Destructor
		FoamBase_EXPORT ~OFstream();


		// Member Functions

			// Access

				//- Return the name of the stream
		const fileName& name() const
		{
			return pathname_;
		}

		//- Return non-const access to the name of the stream
		fileName& name()
		{
			return pathname_;
		}


		// STL stream

			//- Access to underlying std::ostream
		FoamBase_EXPORT virtual ostream& stdStream();

		//- Const access to underlying std::ostream
		FoamBase_EXPORT virtual const ostream& stdStream() const;


		// Print

			//- Print description of IOstream to Ostream
		FoamBase_EXPORT void print(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	//- Global predefined null output stream "/dev/null"
	FoamBase_EXPORT extern OFstream Snull;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OFstream_Header
