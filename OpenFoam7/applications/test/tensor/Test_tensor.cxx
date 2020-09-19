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

#include <tensor.hxx>
#include <symmTensor.hxx>
#include <transform.hxx>
#include <stringList.hxx>
#include <IOstreams.hxx>

void tnbLib::Test_tensor()
{
	tensor t1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	tensor t2(1, 2, 3, 1, 2, 3, 1, 2, 3);

	tensor t3 = t1 + t2;

	Info << t3 << endl;

	tensor t4(3, -2, 1, -2, 2, 0, 1, 0, 4);

	Info << inv(t4) << endl;
	Info << (inv(t4) & t4) << endl;

	Info << t1.x() << t1.y() << t1.z() << endl;

	tensor t6(1, 0, -4, 0, 5, 4, -4, 4, 3);
	// tensor t6(1,2,0,2,5,0,0,0,0);

	Info << "tensor " << t6 << endl;
	vector e = eigenValues(t6);
	Info << "eigenvalues " << e << endl;

	tensor ev = eigenVectors(t6);
	Info << "eigenvectors " << ev << endl;

	Info << "Check determinant " << e.x() * e.y() * e.z() << " " << det(t6) << endl;

	Info << "Check eigenvectors "
		<< (eigenVectors(t6, e) & t6) << " "
		<< (e.x() * eigenVectors(t6, e).x())
		<< (e.y() * eigenVectors(t6, e).y())
		<< (e.z() * eigenVectors(t6, e).z())
		<< endl;

	Info << "Check eigenvalues for symmTensor "
		<< eigenValues(symm(t6)) - eigenValues(tensor(symm(t6))) << endl;

	Info << "Check eigenvectors for symmTensor "
		<< eigenVectors(symm(t6)) - eigenVectors(tensor(symm(t6))) << endl;

	tensor t7(1, 2, 3, 2, 4, 5, 3, 5, 6);

	Info << "Check transformation "
		<< (t1 & t7 & t1.T()) << " " << transform(t1, t7) << endl;

	symmTensor st1(1, 2, 3, 4, 5, 6);
	symmTensor st2(7, 8, 9, 10, 11, 12);

	Info << "Check symmetric transformation "
		<< transform(t1, st1) << endl;

	Info << "Check dot product of symmetric tensors "
		<< (st1 & st2) << endl;

	Info << "Check inner sqr of a symmetric tensor "
		<< innerSqr(st1) << " " << innerSqr(st1) - (st1 & st1) << endl;

	Info << "Check symmetric part of dot product of symmetric tensors "
		<< twoSymm(st1 & st2) - ((st1 & st2) + (st2 & st1)) << endl;

	tensor sk1 = skew(t6);
	Info << "Check dot product of symmetric and skew tensors "
		<< twoSymm(st1 & sk1) - ((st1 & sk1) - (sk1 & st1)) << endl;

	vector v1(1, 2, 3);

	Info << sqr(v1) << endl;
	Info << symm(t7) << endl;
	Info << twoSymm(t7) << endl;
	Info << magSqr(st1) << endl;
	Info << mag(st1) << endl;

	Info << (symm(t7) && t7) - (0.5 * (t7 + t7.T()) && t7) << endl;
	Info << (t7 && symm(t7)) - (t7 && 0.5 * (t7 + t7.T())) << endl;
}