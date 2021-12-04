/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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

#include <phaseChange.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <phaseSystem.hxx>
#include <phasePairKey.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace driftModels
        {
            defineTypeNameAndDebug(phaseChange, 0);
            addToRunTimeSelectionTable(driftModel, phaseChange, dictionary);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diameterModels::driftModels::phaseChange::phaseChange
(
    const populationBalanceModel& popBal,
    const dictionary& dict
)
    :
    driftModel(popBal, dict),
    pairKeys_(dict.lookup("pairs")),
    numberWeighted_(dict.lookupOrDefault<Switch>("numberWeighted", false)),
    W_(pairKeys_.size())
{
    const phaseSystem& fluid = popBal_.fluid();

    forAll(pairKeys_, i)
    {
        const phasePair& pair = fluid.phasePairs()[pairKeys_[i]];

        W_.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    IOobject::groupName(type() + ":W", pair.name()),
                    popBal_.mesh().time().timeName(),
                    popBal_.mesh()
                ),
                popBal_.mesh(),
                dimensionedScalar
                (
                    inv(numberWeighted_ ? dimVolume : dimLength),
                    Zero
                )
            )
        );
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::diameterModels::driftModels::phaseChange::correct()
{
    const phaseSystem& fluid = popBal_.fluid();

    forAll(pairKeys_, i)
    {
        W_[i] = Zero;
    }

    forAll(pairKeys_, k)
    {
        if (fluid.phasePairs().found(pairKeys_[k]))
        {
            const phasePair& pair = fluid.phasePairs()[pairKeys_[k]];

            forAll(popBal_.velocityGroups(), j)
            {
                const velocityGroup& vgj = popBal_.velocityGroups()[j];
                if (pair.contains(vgj.phase()))
                {
                    forAll(vgj.sizeGroups(), i)
                    {
                        const sizeGroup& fi = vgj.sizeGroups()[i];

                        W_[k] +=
                            fi * max(fi.phase(), small)
                            / (numberWeighted_ ? fi.x() : fi.d());
                    }
                }
            }
        }
    }
}


void tnbLib::diameterModels::driftModels::phaseChange::addToDriftRate
(
    volScalarField& driftRate,
    const label i
)
{
    const velocityGroup& vg = popBal_.sizeGroups()[i].VelocityGroup();

    forAll(pairKeys_, k)
    {
        const phasePair& pair =
            popBal_.fluid().phasePairs()[pairKeys_[k]];

        if (pair.contains(vg.phase()))
        {
            const volScalarField& iDmdt =
                popBal_.mesh().lookupObject<volScalarField>
                (
                    IOobject::groupName("iDmdt", pair.name())
                    );

            const scalar iDmdtSign =
                vg.phase().name() == pair.first() ? +1 : -1;

            const sizeGroup& fi = popBal_.sizeGroups()[i];

            tmp<volScalarField> dDriftRate
            (
                iDmdtSign * iDmdt / (fi.phase().rho() * W_[k])
            );

            if (!numberWeighted_)
            {
                dDriftRate.ref() *= fi.x() / fi.d();
            }

            driftRate += dDriftRate;
        }
    }
}


// ************************************************************************* //
