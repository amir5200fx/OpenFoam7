/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2019 OpenFOAM Foundation
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

#include <KocamustafaogullariIshii.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <uniformDimensionedFields.hxx>
#include <compressibleTurbulenceModel.hxx>
#include <ThermalDiffusivity.hxx>
#include <PhaseCompressibleTurbulenceModel.hxx>
#include <phaseSystem.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace wallBoilingModels
    {
        namespace departureDiameterModels
        {
            defineTypeNameAndDebug(KocamustafaogullariIshii, 0);
            addToRunTimeSelectionTable
            (
                departureDiameterModel,
                KocamustafaogullariIshii,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureDiameterModels::
KocamustafaogullariIshii::KocamustafaogullariIshii
(
    const dictionary& dict
)
    :
    departureDiameterModel(),
    phi_(readScalar(dict.lookup("phi")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallBoilingModels::departureDiameterModels::
KocamustafaogullariIshii::~KocamustafaogullariIshii()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField>
tnbLib::wallBoilingModels::departureDiameterModels::
KocamustafaogullariIshii::dDeparture
(
    const phaseModel& liquid,
    const phaseModel& vapor,
    const label patchi,
    const scalarField& Tl,
    const scalarField& Tsatw,
    const scalarField& L
) const
{
    // Gravitational acceleration
    const uniformDimensionedVectorField& g =
        liquid.mesh().lookupObject<uniformDimensionedVectorField>("g");

    const scalarField rhoLiquid(liquid.thermo().rho(patchi));
    const scalarField rhoVapor(vapor.thermo().rho(patchi));

    const scalarField rhoM((rhoLiquid - rhoVapor) / rhoVapor);

    const tmp<volScalarField>& tsigma
    (
        liquid.fluid().sigma(phasePairKey(liquid.name(), vapor.name()))
    );
    const volScalarField& sigma = tsigma();
    const fvPatchScalarField& sigmaw = sigma.boundaryField()[patchi];

    return
        0.0012 * pow(rhoM, 0.9) * 0.0208 * phi_
        * sqrt(sigmaw / (mag(g.value()) * (rhoLiquid - rhoVapor)));
}


void tnbLib::wallBoilingModels::departureDiameterModels::
KocamustafaogullariIshii::write(Ostream& os) const
{
    departureDiameterModel::write(os);
    writeEntry(os, "phi", phi_);
}


// ************************************************************************* //
