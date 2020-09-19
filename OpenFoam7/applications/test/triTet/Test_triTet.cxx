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
	Tuple2Test

Description

\*---------------------------------------------------------------------------*/

#include <point.hxx>
#include <triangle.hxx>
#include <tetrahedron.hxx>
#include <IOstreams.hxx>

void tnbLib::Test_triTet()
{
	triangle<point, point> tri
	(
		vector(0, 0, 0),
		vector(1, 0, 0),
		vector(1, 1, 0)
	);

	Info << "tri circumCentre = " << tri.circumCentre() << endl;
	Info << "tri circumRadius = " << tri.circumRadius() << endl;

	tetrahedron<point, point> tet
	(
		vector(1, 0, 0),
		vector(0, 1, 0),
		vector(0, 0, 1),
		vector(0.5773502, 0.5773502, 0.5773502)
	);

	Info << "tet circumCentre = " << tet.circumCentre() << endl;
	Info << "tet circumRadius = " << tet.circumRadius() << endl;

	vector a(Sin);
	vector b(Sin);
	vector c(Sin);
	vector d(Sin);

	Info << "tet circumRadius = "
		<< tetrahedron<point, point>(a, b, c, d).circumRadius() << endl;
}