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
    volPointInterpolationTest

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
#include <setRootCase.lxx>

#include <createTime.lxx>
#include <createMesh.lxx>

    Info << "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info << "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    const pointMesh& pMesh = pointMesh::New(mesh);
    const pointBoundaryMesh& pbm = pMesh.boundary();

    Info << "pointMesh boundary" << nl;
    forAll(pbm, patchi)
    {
        Info << "patch=" << pbm[patchi].name()
            << ", type=" << pbm[patchi].type()
            << ", coupled=" << pbm[patchi].coupled()
            << endl;
    }

    const volPointInterpolation& pInterp = volPointInterpolation::New(mesh);


    pointScalarField pp(pInterp.interpolate(p));
    Info << pp.name() << " boundary" << endl;
    forAll(pp.boundaryField(), patchi)
    {
        Info << pbm[patchi].name() << " coupled="
            << pp.boundaryField()[patchi].coupled() << endl;
    }

    pp.write();

    pointVectorField pU(pInterp.interpolate(U));
    pU.write();

    return 0;
}


// ************************************************************************* //
