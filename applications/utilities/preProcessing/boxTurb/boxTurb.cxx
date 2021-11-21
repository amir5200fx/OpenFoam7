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
    boxTurb

Description
    Makes a box of turbulence which conforms to a given energy
    spectrum and is divergence free.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <graph.hxx>
#include <OFstream.hxx>
#include <Kmesh.hxx>
#include <turbGen.hxx>
#include <calcEk.hxx>
#include <writeFile.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{
    argList::noParallel();
#include <setRootCase.lxx>

#include <createTime.lxx>
#include <createMesh.lxx>
#include "createFields.lxx"
#include "readBoxTurbDict.lxx"


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Kmesh K(mesh);

    turbGen Ugen(K, Ea, k0);

    U.primitiveFieldRef() = Ugen.U();
    U.correctBoundaryConditions();

    Info << "k("
        << runTime.timeName()
        << ") = "
        << 3.0 / 2.0 * average(magSqr(U)).value() << endl;

    U.write();

    calcEk(U, K).write
    (
        runTime.path()
        / functionObjects::writeFile::outputPrefix
        / "graphs"
        / runTime.timeName(),
        "Ek",
        runTime.graphFormat()
    );

    Info << "end" << endl;

    return 0;
}


// ************************************************************************* //