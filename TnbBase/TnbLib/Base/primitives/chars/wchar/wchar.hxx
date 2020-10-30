#pragma once
#ifndef _wchar_Header
#define _wchar_Header

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

Primitive
	wchar_t

Description
	A wide-character and a pointer to a wide-character string.

SourceFiles
	wcharIO.C

See also
	http://en.wikipedia.org/wiki/UTF-8
	http://en.wikibooks.org/wiki/Unicode/Character_reference

\*---------------------------------------------------------------------------*/

#include <includeModule.hxx>

#include <cwchar>
#include <string>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Istream;
	class Ostream;

	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	//- Output wide character (Unicode) as UTF-8
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const wchar_t);

	//- Output wide character (Unicode) string as UTF-8
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const wchar_t*);

	//- Output wide character (Unicode) string as UTF-8
	FoamBase_EXPORT Ostream& operator<<(Ostream&, const std::wstring&);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wchar_Header
