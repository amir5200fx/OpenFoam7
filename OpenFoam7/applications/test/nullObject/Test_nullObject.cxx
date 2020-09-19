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

#include <nullObject.hxx>
#include <IOstreams.hxx>

class SimpleClass
{

public:

	//- Null constructor
	SimpleClass()
	{}
};

void tnbLib::Test_nullObject()
{
	// Test pointer and reference to a class

	SimpleClass* ptrToClass = new SimpleClass;
	SimpleClass& refToClass(*ptrToClass);

	if (notNull(ptrToClass))
	{
		Info << "Pass: ptrToClass is not null" << endl;
	}
	else
	{
		Info << "FAIL: refToClass is null" << endl;
	}

	if (notNull(refToClass))
	{
		Info << "Pass: refToClass is not null" << endl;
	}
	else
	{
		Info << "FAIL: refToClass is null" << endl;
	}


	// Test pointer and reference to the nullObject

	const SimpleClass* ptrToNull(NullObjectPtr<SimpleClass>());
	const SimpleClass& refToNull(*ptrToNull);

	if (isNull(ptrToNull))
	{
		Info << "Pass: ptrToNull is null" << endl;
	}
	else
	{
		Info << "FAIL: ptrToNull is not null" << endl;
	}

	if (isNull(refToNull))
	{
		Info << "Pass: refToNull is null" << endl;
	}
	else
	{
		Info << "FAIL: refToNull is not null" << endl;
	}

	// Clean-up
	delete ptrToClass;
}