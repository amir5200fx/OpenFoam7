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
    surfaceMeshExport

Description
    Export from surfMesh to various third-party surface formats with
    optional scaling or transformations (rotate/translate) on a
    coordinateSystem.

Usage
    \b surfaceMeshExport outputFile [OPTION]

    Options:
      - \par -clean
        Perform some surface checking/cleanup on the input surface.

      - \par -name \<name\>
        Specify an alternative surface name when writing.

      - \par -scaleIn \<scale\>
        Specify a scaling factor when reading files.

      - \par -scaleOut \<scale\>
        Specify a scaling factor when writing files.

      - \par -dict \<dictionary\>
        Specify an alternative dictionary for constant/coordinateSystems.

      - \par -from \<coordinateSystem\>
        Specify a coordinate system when reading files.

      - \par -to \<coordinateSystem\>
        Specify a coordinate system when writing files.

Note
    The filename extensions are used to determine the file format type.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <argList.hxx>
#include <Time.hxx>

#include <MeshedSurfaces.hxx>
#include <coordinateSystems.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
    argList::addNote
    (
        "export from surfMesh to various third-party surface formats"
    );

    argList::noParallel();
    argList::validArgs.append("output surface file");

    argList::addBoolOption
    (
        "clean",
        "perform some surface checking/cleanup on the input surface"
    );
    argList::addOption
    (
        "name",
        "name",
        "specify an alternative surface name when reading - "
        "default is 'default'"
    );
    argList::addOption
    (
        "scaleIn",
        "factor",
        "geometry scaling factor on input - default is 1"
    );
    argList::addOption
    (
        "scaleOut",
        "factor",
        "geometry scaling factor on output - default is 1"
    );
#include <addDictOption.lxx>
    argList::addOption
    (
        "from",
        "coordinateSystem",
        "specify the source coordinate system, applied after '-scaleIn'"
    );
    argList::addOption
    (
        "to",
        "coordinateSystem",
        "specify the target coordinate system, applied before '-scaleOut'"
    );

    argList args(argc, argv);
    Time runTime(args.rootPath(), args.caseName());

    const fileName exportName = args[1];
    const word importName = args.optionLookupOrDefault<word>("name", "default");

    // check that writing is supported
    if (!MeshedSurface<face>::canWriteType(exportName.ext(), true))
    {
        return 1;
    }


    // get the coordinate transformations
    autoPtr<coordinateSystem> fromCsys;
    autoPtr<coordinateSystem> toCsys;

    if (args.optionFound("from") || args.optionFound("to"))
    {
        autoPtr<IOobject> ioPtr;

        if (args.optionFound("dict"))
        {
            const fileName dictPath = args["dict"];

            ioPtr.set
            (
                new IOobject
                (
                    (
                        isDir(dictPath)
                        ? dictPath / coordinateSystems::typeName
                        : dictPath
                        ),
                    runTime,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE,
                    false
                )
            );
        }
        else
        {
            ioPtr.set
            (
                new IOobject
                (
                    coordinateSystems::typeName,
                    runTime.constant(),
                    runTime,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE,
                    false
                )
            );
        }


        if (!ioPtr->typeHeaderOk<coordinateSystems>(false))
        {
            FatalErrorInFunction
                << ioPtr->objectPath() << nl
                << exit(FatalError);
        }

        coordinateSystems csLst(ioPtr());

        if (args.optionFound("from"))
        {
            const word csName = args["from"];

            const label csIndex = csLst.findIndex(csName);
            if (csIndex < 0)
            {
                FatalErrorInFunction
                    << "Cannot find -from " << csName << nl
                    << "available coordinateSystems: " << csLst.toc() << nl
                    << exit(FatalError);
            }

            fromCsys.reset(new coordinateSystem(csLst[csIndex]));
        }

        if (args.optionFound("to"))
        {
            const word csName = args["to"];

            const label csIndex = csLst.findIndex(csName);
            if (csIndex < 0)
            {
                FatalErrorInFunction
                    << "Cannot find -to " << csName << nl
                    << "available coordinateSystems: " << csLst.toc() << nl
                    << exit(FatalError);
            }

            toCsys.reset(new coordinateSystem(csLst[csIndex]));
        }


        // maybe fix this later
        if (fromCsys.valid() && toCsys.valid())
        {
            FatalErrorInFunction
                << exit(FatalError);
        }
    }


    surfMesh smesh
    (
        IOobject
        (
            importName,
            runTime.constant(),
            runTime,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    Info << "read surfMesh:\n  " << smesh.objectPath() << endl;


    // Simply copy for now, but really should have a separate write method

    MeshedSurface<face> surf(smesh);

    if (args.optionFound("clean"))
    {
        surf.cleanup(true);
    }

    scalar scaleIn = 0;
    if (args.optionReadIfPresent("scaleIn", scaleIn) && scaleIn > 0)
    {
        Info << " -scaleIn " << scaleIn << endl;
        surf.scalePoints(scaleIn);
    }

    if (fromCsys.valid())
    {
        Info << " -from " << fromCsys().name() << endl;
        tmp<pointField> tpf = fromCsys().localPosition(surf.points());
        surf.movePoints(tpf());
    }

    if (toCsys.valid())
    {
        Info << " -to " << toCsys().name() << endl;
        tmp<pointField> tpf = toCsys().globalPosition(surf.points());
        surf.movePoints(tpf());
    }

    scalar scaleOut = 0;
    if (args.optionReadIfPresent("scaleOut", scaleOut) && scaleOut > 0)
    {
        Info << " -scaleOut " << scaleOut << endl;
        surf.scalePoints(scaleOut);
    }


    surf.writeStats(Info);
    Info << endl;

    Info << "writing " << exportName << endl;
    surf.write(exportName);

    Info << "\nEnd\n" << endl;

    return 0;
}

// ************************************************************************* //
