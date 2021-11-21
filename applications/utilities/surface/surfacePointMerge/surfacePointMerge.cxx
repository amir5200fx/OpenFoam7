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
    surfacePointMerge

Description
    Merges points on surface if they are within absolute distance.
    Since absolute distance use with care!

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <triSurface.hxx>
#include <triSurfaceTools.hxx>
#include <argList.hxx>
#include <OFstream.hxx>
#include <boundBox.hxx>

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <removeCaseOptions.lxx>

    argList::validArgs.append("surface file");
    argList::validArgs.append("output surface file");
    argList::validArgs.append("merge distance");
    argList args(argc, argv);

    const fileName surfFileName = args[1];
    const fileName outFileName = args[2];
    const scalar   mergeTol = args.argRead<scalar>(3);

    Info << "Reading surface from " << surfFileName << " ..." << endl;
    Info << "Merging points within " << mergeTol << " metre." << endl;

    triSurface surf1(surfFileName);

    Info << "Original surface:" << endl;

    surf1.writeStats(Info);


    triSurface cleanSurf(surf1);

    while (true)
    {
        label nOldVert = cleanSurf.nPoints();

        cleanSurf = triSurfaceTools::mergePoints(cleanSurf, mergeTol);

        Info << "After merging points:" << endl;

        cleanSurf.writeStats(Info);

        if (nOldVert == cleanSurf.nPoints())
        {
            break;
        }
    }

    cleanSurf.write(outFileName);

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
