/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2015-2018 OpenFOAM Foundation
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

#include <constantSurfaceTensionCoefficient.hxx>

#include <phasePair.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace surfaceTensionModels
    {
        defineTypeNameAndDebug(constantSurfaceTensionCoefficient, 0);
        addToRunTimeSelectionTable
        (
            surfaceTensionModel,
            constantSurfaceTensionCoefficient,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::constantSurfaceTensionCoefficient::
constantSurfaceTensionCoefficient
(
    const dictionary& dict,
    const phasePair& pair,
    const bool registerObject
)
    :
    surfaceTensionModel(dict, pair, registerObject),
    sigma_("sigma", dimSigma, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::constantSurfaceTensionCoefficient::
~constantSurfaceTensionCoefficient()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::surfaceTensionModels::constantSurfaceTensionCoefficient::sigma() const
{
    const fvMesh& mesh(this->pair_.phase1().mesh());

    return volScalarField::New
    (
        "sigma",
        mesh,
        sigma_
    );
}


// ************************************************************************* //
