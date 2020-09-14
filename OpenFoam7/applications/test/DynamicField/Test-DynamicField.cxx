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

\*---------------------------------------------------------------------------*/

#include <test.hxx>

#include <point.hxx>
#include <DynamicField.hxx>
#include <IOstreams.hxx>

using namespace tnbLib;

#include <OFstream.hxx>
#include <jobInfo.hxx>


void tnbLib::Test_DynamicField()
{
	fileName myFileName("Test-DynamicField.txt");
	OFstream myFile(myFileName);

	DynamicField<point, 0, 10, 11> testField;
	DynamicField<point, 0, 10, 11> testField2;

	testField.setSize(5);
	testField2.setSize(5);

	testField[0] = testField2[0] = vector(1.0, 4.5, 6.3);
	testField[1] = testField2[1] = vector(5.2, 2.3, 3.5);
	testField[2] = testField2[2] = vector(7.5, 4.7, 7.7);
	testField[3] = testField2[3] = vector(2.8, 8.2, 2.3);
	testField[4] = testField2[4] = vector(6.1, 1.7, 8.8);

	myFile << "testField:" << testField << endl;

	testField.append(vector(0.5, 4.8, 6.2));

	myFile << "testField after appending:" << testField << endl;

	testField.append(vector(2.7, 2.3, 6.1));

	myFile << "testField after appending:" << testField << endl;

	vector elem = testField.remove();

	myFile << "removed element:" << elem << endl;
	myFile << "testField:" << testField << endl;

	testField.append(vector(3.0, 1.3, 9.2));

	myFile << "testField:" << testField << endl;

	testField.setSize(10, vector(1.5, 0.6, -1.0));

	myFile << "testField after setSize:" << testField << endl;

	testField.append(testField2);

	myFile << "testField after appending testField2:" << testField << endl;

	testField = testField2;

	myFile << "testField after assignment:" << testField << endl;

	testField += testField2;

	myFile << "testField after field algebra:" << testField << endl;

	testField.clear();

	testField.append(vector(3.0, 1.3, 9.2));

	myFile << "testField after clear and append:" << testField << endl;

	testField.clearStorage();

	myFile << "testField after clearStorage:" << testField << endl;
}