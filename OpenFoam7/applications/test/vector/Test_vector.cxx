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

Description

\*---------------------------------------------------------------------------*/

#include <vector.hxx>
#include <IOstreams.hxx>

void tnbLib::Test_vector()
{
	Info << vector::zero << endl
		<< vector::one << endl
		<< vector::dim << endl
		<< vector::rank << endl;

	vector d(0.5, 0.5, 0.5);
	d /= mag(d);

	vector dSmall = (1e-100) * d;
	dSmall /= mag(dSmall);

	Info << (dSmall - d) << endl;

	d *= 4.0;

	Info << d << endl;

	Info << d + d << endl;

	Info << magSqr(d) << endl;

	vector d2(0.5, 0.51, -0.5);
	Info << cmptMax(d2) << " "
		<< cmptSum(d2) << " "
		<< cmptProduct(d2) << " "
		<< cmptMag(d2)
		<< endl;
	Info << min(d, d2) << endl;
}