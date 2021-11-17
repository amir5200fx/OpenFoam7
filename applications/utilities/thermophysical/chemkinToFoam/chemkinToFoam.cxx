/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
    chemkinToFoam

Description
    Converts CHEMKINIII thermodynamics and reaction data files into
    OpenFOAM format.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <chemkinReader.hxx>
#include <OFstream.hxx>
#include <OStringStream.hxx>
#include <IStringStream.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <removeCaseOptions.lxx>

    // Increase the precision of the output for JANAF coefficients
    Ostream::defaultPrecision(10);

    argList::validArgs.append("CHEMKIN file");
    argList::validArgs.append("CHEMKIN thermodynamics file");
    argList::validArgs.append("CHEMKIN transport file");
    argList::validArgs.append("OpenFOAM chemistry file");
    argList::validArgs.append("OpenFOAM thermodynamics file");

    argList::addBoolOption
    (
        "newFormat",
        "read Chemkin thermo file in new format"
    );

    argList args(argc, argv);

    bool newFormat = args.optionFound("newFormat");

    speciesTable species;

    chemkinReader cr(species, args[1], args[3], args[2], newFormat);

    OFstream reactionsFile(args[4]);
    writeEntry(reactionsFile, "elements", cr.elementNames());
    reactionsFile << nl;
    writeEntry(reactionsFile, "species", cr.species());
    reactionsFile << nl;
    cr.reactions().write(reactionsFile);

    // Temporary hack to splice the specie composition data into the thermo file
    // pending complete integration into the thermodynamics structure

    OStringStream os;
    cr.speciesThermo().write(os);
    dictionary thermoDict(IStringStream(os.str())());

    wordList speciesList(thermoDict.toc());

    // Add elements
    forAll(speciesList, si)
    {
        dictionary elementsDict("elements");
        forAll(cr.specieComposition()[speciesList[si]], ei)
        {
            elementsDict.add
            (
                cr.specieComposition()[speciesList[si]][ei].name(),
                cr.specieComposition()[speciesList[si]][ei].nAtoms()
            );
        }

        thermoDict.subDict(speciesList[si]).add("elements", elementsDict);
    }

    thermoDict.write(OFstream(args[5])(), false);

    reactionsFile << nl;

    writeEntry
    (
        reactionsFile,
        "Tlow",
        Reaction<gasHThermoPhysics>::TlowDefault
    );
    writeEntry
    (
        reactionsFile,
        "Thigh",
        Reaction<gasHThermoPhysics>::ThighDefault
    );

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
