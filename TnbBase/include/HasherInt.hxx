#pragma once
#ifndef _HasherInt_Header
#define _HasherInt_Header

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

InNamespace
	Foam

Description
	Optimized hashing functions.

See also
	Hasher.H

\*---------------------------------------------------------------------------*/

#include <Hasher.hxx>

#include <cstddef>
#include <stdint.h>    // C++0x uses <cstdint>

namespace tnbLib
{

	//- An optimized version of Hasher
	//  @param[in] data - an array of uint32_t values
	//  @param[in] len  - the number of values (not bytes)
	//  @param[in] seed - the previous hash, or an arbitrary value
	unsigned HasherInt(const uint32_t*, size_t length, unsigned seed = 0);

	//- An optimized version of Hasher, returning dual hash values
	//  @param[in] data - an array of uint32_t values
	//  @param[in] len  - the number of values (not bytes)
	//  @param[in] hash1 - the previous hash, or an arbitrary value
	//    on output, the primary hash value
	//  @param[in] hash1 - the previous hash, or an arbitrary value
	//    on output, the secondary hash value
	unsigned HasherDual
	(
		const uint32_t*,
		size_t len,
		unsigned& hash1,
		unsigned& hash2
	);
}

#endif // !_HasherInt_Header
