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

#include <test.hxx>

#include <OSspecific.hxx>

#include <IOstreams.hxx>
#include <DLList.hxx>

#include <OFstream.hxx>
#include <jobInfo.hxx>

using namespace tnbLib;

void tnbLib::Test_DLList()
{
	

	fileName myFileName("Test_DLList.txt");
	OFstream myFile(myFileName);

	DLList<scalar> myList;

	for (int i = 0; i < 10; i++)
	{
		myList.append(1.3*i);
	}

	myList.append(100.3);
	myList.append(500.3);

	myFile << nl << "And again using STL iterator: " << nl << endl;

	forAllIter(DLList<scalar>, myList, iter)
	{
		myFile << "element:" << *iter << endl;
	}


	myFile << nl << "And again using the same STL iterator: " << nl << endl;

	forAllIter(DLList<scalar>, myList, iter)
	{
		myFile << "Removing " << myList.remove(iter) << endl;
	}

	myList.append(500.3);
	myList.append(200.3);
	myList.append(100.3);


	myFile << nl << "And again using STL const_iterator: " << nl << endl;


	forAllConstIter(DLList<scalar>, myList, iter)
	{
		myFile << "element:" << *iter << endl;
	}

	myFile << nl << "Testing swapUp and swapDown: " << endl;

	myFile << nl << "swapUp" << endl;

	myList.swapUp(myList.DLListBase::first());
	myList.swapUp(myList.DLListBase::last());

	forAllIter(DLList<scalar>, myList, iter)
	{
		myFile << "element:" << *iter << endl;
	}

	myFile << nl << "swapDown" << endl;

	myList.swapDown(myList.DLListBase::first());
	myList.swapDown(myList.DLListBase::last());

	forAllIter(DLList<scalar>, myList, iter)
	{
		myFile << "element:" << *iter << endl;
	}


	myFile << nl << "Testing transfer: " << nl << nl
		<< "original: " << myList << endl;

	DLList<scalar> newList;
	newList.transfer(myList);

	myFile << nl << "source: " << myList << nl
		<< nl << "target: " << newList << endl;

	myFile << nl << "Done." << endl;
}