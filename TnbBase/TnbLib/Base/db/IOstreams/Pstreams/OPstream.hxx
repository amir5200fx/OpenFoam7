#pragma once
#ifndef _OPstream_Header
#define _OPstream_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::OPstream

Description
	Output inter-processor communications stream.

SourceFiles
	OPstream.C

\*---------------------------------------------------------------------------*/

#include <UOPstream.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							  Class OPstream Declaration
	\*---------------------------------------------------------------------------*/

	class OPstream
		:
		public Pstream,
		public UOPstream
	{

	public:

		// Constructors

			//- Construct given process index to send to and optional buffer size,
			//  write format and IO version
		OPstream
		(
			const commsTypes commsType,
			const int toProcNo,
			const label bufSize = 0,
			const int tag = UPstream::msgType(),
			const label comm = UPstream::worldComm,
			streamFormat format = BINARY,
			versionNumber version = currentVersion
		);

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OPstream_Header
