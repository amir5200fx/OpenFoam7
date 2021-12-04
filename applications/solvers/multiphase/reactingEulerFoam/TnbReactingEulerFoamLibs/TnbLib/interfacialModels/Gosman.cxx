/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2014-2018 OpenFOAM Foundation
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

#include <Gosman.hxx>

#include <phasePair.hxx>
#include <phaseCompressibleTurbulenceModelMultiphase.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <dragModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace turbulentDispersionModels
    {
        defineTypeNameAndDebug(Gosman, 0);
        addToRunTimeSelectionTable
        (
            turbulentDispersionModel,
            Gosman,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::Gosman::Gosman
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    turbulentDispersionModel(dict, pair),
    sigma_("sigma", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::Gosman::~Gosman()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::turbulentDispersionModels::Gosman::D() const
{
    const fvMesh& mesh(pair_.phase1().mesh());
    const dragModel&
        drag
        (
            mesh.lookupObject<dragModel>
            (
                IOobject::groupName(dragModel::typeName, pair_.name())
                )
        );

    return
        0.75
        * drag.CdRe()
        * pair_.dispersed()
        * pair_.continuous().nu()
        * continuousTurbulence().nut()
        / (
            sigma_
            * sqr(pair_.dispersed().d())
            )
        * pair_.continuous().rho();
}


// ************************************************************************* //
