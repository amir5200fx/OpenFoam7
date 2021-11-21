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
    surfaceFeatureConvert

Description
    Convert between edgeMesh formats.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <Time.hxx>

#include <edgeMesh.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char* argv[])
{
    argList::addNote
    (
        "Convert between edgeMesh formats"
    );
    argList::noParallel();
    argList::validArgs.append("edge file");
    argList::validArgs.append("output edge file");
    argList::addOption
    (
        "scale",
        "factor",
        "geometry scaling factor - default is 1"
    );

    argList args(argc, argv);
    Time runTime(args.rootPath(), args.caseName());

    const fileName importName = args[1];
    const fileName exportName = args[2];

    // disable inplace editing
    if (importName == exportName)
    {
        FatalErrorInFunction
            << "Output file " << exportName << " would overwrite input file."
            << exit(FatalError);
    }

    // check that reading/writing is supported
    if
        (
            !edgeMesh::canReadType(importName.ext(), true)
            || !edgeMesh::canWriteType(exportName.ext(), true)
            )
    {
        return 1;
    }

    edgeMesh mesh(importName);

    Info << "\nRead edgeMesh " << importName << nl;
    mesh.writeStats(Info);
    Info << nl
        << "\nwriting " << exportName;

    scalar scaleFactor = 0;
    if (args.optionReadIfPresent("scale", scaleFactor) && scaleFactor > 0)
    {
        Info << " with scaling " << scaleFactor << endl;
        mesh.scalePoints(scaleFactor);
    }
    else
    {
        Info << " without scaling" << endl;
    }

    mesh.write(exportName);
    mesh.writeStats(Info);
    Info << endl;

    Info << "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
