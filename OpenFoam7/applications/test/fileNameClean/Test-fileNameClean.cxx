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
    fileNameCleanTest

Description

\*---------------------------------------------------------------------------*/

#include <argList.hxx>
#include <fileName.hxx>
#include <SubList.hxx>
#include <IOobject.hxx>
#include <IOstream.hxx>
#include <OSspecific.hxx>

void printCleaning(tnbLib::fileName& pathName)
{
	tnbLib::Info << "fileName = " << pathName << tnbLib::nl
		<< "  path() = " << pathName.path() << tnbLib::nl
		<< "  name() = " << pathName.name() << tnbLib::nl
		<< "  joined = " << pathName.path() / pathName.name() << tnbLib::nl << tnbLib::nl;

	pathName.clean();

    tnbLib::Info << "cleaned  = " << pathName << tnbLib::nl
		<< "  path() = " << pathName.path() << tnbLib::nl
		<< "  name() = " << pathName.name() << tnbLib::nl
		<< "  joined = " << pathName.path() / pathName.name() << tnbLib::nl << tnbLib::nl;

    tnbLib::IOobject::writeDivider(tnbLib::Info);
}

void tnbLib::Test_fileNameClean(int argc, char* argv[])
{
	writeInfoHeader = false;

	argList::noParallel();
	argList::validArgs.insert("fileName .. fileNameN");
	argList::addOption("istream", "file", "test Istream values");

	argList args(argc, argv, false, true);

	if (args.size() <= 1 && args.options().empty())
	{
		args.printUsage();
	}

	fileName pathName;
	if (args.optionReadIfPresent("case", pathName))
	{
		Info << nl
			<< "-case" << nl
			<< "path = " << args.path() << nl
			<< "root = " << args.rootPath() << nl
			<< "case = " << args.caseName() << nl
			<< "FOAM_CASE=" << getEnv("FOAM_CASE") << nl
			<< "FOAM_CASENAME=" << getEnv("FOAM_CASENAME") << nl
			<< endl;

		printCleaning(pathName);
	}

	for (label argI = 1; argI < args.size(); ++argI)
	{
		pathName = args[argI];
		printCleaning(pathName);
	}

	if (args.optionFound("istream"))
	{
		args.optionLookup("istream")() >> pathName;

		Info << nl
			<< "-case" << nl
			<< "path = " << args.path() << nl
			<< "root = " << args.rootPath() << nl
			<< "case = " << args.caseName() << nl
			<< "FOAM_CASE=" << getEnv("FOAM_CASE") << nl
			<< "FOAM_CASENAME=" << getEnv("FOAM_CASENAME") << nl
			<< endl;

		printCleaning(pathName);
	}

	Info << "\nEnd\n" << endl;
}