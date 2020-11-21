#pragma once
#ifndef _threadedCollatedOFstream_Header
#define _threadedCollatedOFstream_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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
	tnbLib::threadedCollatedOFstream

Description
	Master-only drop-in replacement for OFstream.

SourceFiles
	threadedCollatedOFstream.C

\*---------------------------------------------------------------------------*/

#include <OStringStream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class OFstreamCollator;

	/*---------------------------------------------------------------------------*\
					  Class threadedCollatedOFstream Declaration
	\*---------------------------------------------------------------------------*/

	class threadedCollatedOFstream
		:
		public OStringStream
	{
		// Private Data

		OFstreamCollator& writer_;

		const fileName pathName_;

		const IOstream::compressionType compression_;

		const bool useThread_;


	public:

		// Constructors

			//- Construct and set stream status
		FoamBase_EXPORT threadedCollatedOFstream
		(
			OFstreamCollator&,
			const fileName& pathname,
			streamFormat format = ASCII,
			versionNumber version = currentVersion,
			compressionType compression = UNCOMPRESSED,
			const bool useThread = true
		);


		//- Destructor
		FoamBase_EXPORT ~threadedCollatedOFstream();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_threadedCollatedOFstream_Header
