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

#include <engineMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::engineMesh> tnbLib::engineMesh::New
(
    const tnbLib::IOobject& io
)
{
    // get model name, but do not register the dictionary
    // otherwise it is registered in the database twice
    const word modelType
    (
        IOdictionary
        (
			tnbLib::IOobject
            (
                "engineGeometry",
                io.time().constant(),
                io.db(),
                tnbLib::IOobject::MUST_READ_IF_MODIFIED,
                tnbLib::IOobject::NO_WRITE,
                false
            )
        ).lookup("engineMesh")
    );

    Info << "Selecting engineMesh " << modelType << endl;

    IOobjectConstructorTable::iterator cstrIter =
        IOobjectConstructorTablePtr_->find(modelType);

    if (cstrIter == IOobjectConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown engineMesh type "
            << modelType << nl << nl
            << "Valid engineMesh types are :" << endl
            << IOobjectConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<engineMesh>(cstrIter()(io));
}


// ************************************************************************* //
