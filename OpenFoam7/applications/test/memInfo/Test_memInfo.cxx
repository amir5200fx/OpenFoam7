#include <test.hxx>

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

Application

Description

\*---------------------------------------------------------------------------*/

#include <memInfo.hxx>
#include <IOstreams.hxx>
#include <List.hxx>
#include <vector.hxx>

void tnbLib::Test_memInfo()
{
	const int n = 10000000;
	const char* const memTags = "peak/size/rss mem: ";

	memInfo mem;

	Info << memTags << mem << endl;
	List<vector> lst(n, vector::one);

	Info << "allocate " << n << " vectors" << nl
		<< memTags << mem.update() << endl;

	lst.clear();
	Info << "clear" << nl
		<< memTags << mem.update() << endl;
}