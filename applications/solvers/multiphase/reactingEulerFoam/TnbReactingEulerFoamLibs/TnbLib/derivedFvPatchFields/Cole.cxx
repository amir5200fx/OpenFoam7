/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

#include <Cole.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <uniformDimensionedFields.hxx>
#include <compressibleTurbulenceModel.hxx>
#include <ThermalDiffusivity.hxx>
#include <PhaseCompressibleTurbulenceModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace departureFrequencyModels
        {
            defineTypeNameAndDebug(Cole, 0);
            addToRunTimeSelectionTable
            (
                departureFrequencyModel,
                Cole,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureFrequencyModels::
Cole::Cole(const dictionary& dict)
    :
    departureFrequencyModel()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureFrequencyModels::
Cole::~Cole()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::wallBoilingModels::departureFrequencyModels::
Cole::fDeparture
(
    const phaseModel& liquid,
    const phaseModel& vapor,
    const label patchi,
    const scalarField& dDep
) const
{
    // Gravitational acceleration
    const uniformDimensionedVectorField& g =
        liquid.mesh().lookupObject<uniformDimensionedVectorField>("g");

    const scalarField rhoLiquid(liquid.thermo().rho(patchi));
    const scalarField rhoVapor(vapor.thermo().rho(patchi));

    return sqrt
    (
        4 * mag(g).value()
        * max(rhoLiquid - rhoVapor, scalar(0.1))
        / (3 * dDep * rhoLiquid)
    );
}


// ************************************************************************* //
