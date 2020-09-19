//#include <test.hxx>
//
///*---------------------------------------------------------------------------*\
//  =========                 |
//  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
//   \\    /   O peration     | Website:  https://openfoam.org
//	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
//	 \\/     M anipulation  |
//-------------------------------------------------------------------------------
//License
//	This file is part of OpenFOAM.
//
//	OpenFOAM is free software: you can redistribute it and/or modify it
//	under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
//	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//	for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
//
//Description
//
//\*---------------------------------------------------------------------------*/
//
//#include <vector.hxx>
//#include <IOstreams.hxx>
//#include <vectorTools.hxx>
//#include <unitConversion.hxx>
//
//namespace tnbLib
//{
//	void test(const vector& a, const vector& b, const scalar tolerance)
//	{
//		Info << "Vectors " << a << " and " << b
//			<< " are (to tolerance of " << tolerance << "): ";
//
//		if (vectorTools::areParallel(a, b, tolerance))
//			Info << " parallel ";
//
//		if (vectorTools::areOrthogonal(a, b, tolerance))
//			Info << " orthogonal ";
//
//		if (vectorTools::areAcute(a, b))
//			Info << " acute ";
//
//		if (vectorTools::areObtuse(a, b))
//			Info << " obtuse ";
//
//		Info << ", angle = " << vectorTools::degAngleBetween(a, b);
//
//		Info << endl;
//	}
//}
//
//void tnbLib::Test_vectorTools()
//{
//	vector a(1.0, 1.0, 1.0);
//	vector b(2.0, 2.0, 2.0);
//
//	test(a, b, 0.0);
//	test(a, b, vSmall);
//	test(a, b, small);
//	test(a, b, 1e-3);
//	test(a, b, 1e-1);
//
//	a = vector(1, 0, 0);
//	b = vector(0, 2, 0);
//
//	test(a, b, 0.0);
//	test(a, b, vSmall);
//	test(a, b, small);
//	test(a, b, 1e-3);
//	test(a, b, 1e-1);
//
//	a = vector(1, 0, 0);
//	b = vector(-1, 0, 0);
//
//	test(a, b, 0.0);
//	test(a, b, vSmall);
//	test(a, b, small);
//	test(a, b, 1e-3);
//	test(a, b, 1e-1);
//
//	a = vector(1, 0, 0);
//	b = vector(-1, 2, 0);
//
//	test(a, b, 0.0);
//	test(a, b, vSmall);
//	test(a, b, small);
//	test(a, b, 1e-3);
//	test(a, b, 1e-1);
//}