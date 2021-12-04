/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include <densityChange.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <phaseSystem.hxx>
#include <fvcDdt.hxx>
#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace driftModels
        {
            defineTypeNameAndDebug(densityChangeDrift, 0);
            addToRunTimeSelectionTable(driftModel, densityChangeDrift, dictionary);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diameterModels::driftModels::densityChangeDrift::densityChangeDrift
(
    const populationBalanceModel& popBal,
    const dictionary& dict
)
    :
    driftModel(popBal, dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


void tnbLib::diameterModels::driftModels::densityChangeDrift::addToDriftRate
(
    volScalarField& driftRate,
    const label i
)
{
    const sizeGroup& fi = popBal_.sizeGroups()[i];
    volScalarField& rho = const_cast<volScalarField&>(fi.phase().rho()());

    driftRate -= (fvc::ddt(rho) + (fvc::grad(rho) & popBal_.U()))
        * popBal_.sizeGroups()[i].x() / rho;
}


// ************************************************************************* //
