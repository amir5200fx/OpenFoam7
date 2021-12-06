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

#include "phasePairTwoPhase.hxx"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::EoH
(
    const volScalarField& d
) const
{
    return
        mag(dispersed().rho() - continuous().rho())
        * mag(g())
        * sqr(d)
        / sigma();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phasePair::phasePair
(
    const phaseModel& phase1,
    const phaseModel& phase2,
    const dimensionedVector& g,
    const scalarTable& sigmaTable,
    const bool ordered
)
    :
    phasePairKey(phase1.name(), phase2.name(), ordered),
    phase1_(phase1),
    phase2_(phase2),
    g_(g),
    sigma_
    (
        "sigma",
        dimensionSet(1, 0, -2, 0, 0),
        sigmaTable
        [
            phasePairKey
            (
                phase1.name(),
                phase2.name(),
                false
            )
        ]
)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phasePair::~phasePair()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::phaseModel& tnbLib::phasePair::dispersed() const
{
    FatalErrorInFunction
        << "Requested dispersed phase from an unordered pair."
        << exit(FatalError);

    return phase1_;
}


const tnbLib::phaseModel& tnbLib::phasePair::continuous() const
{
    FatalErrorInFunction
        << "Requested continuous phase from an unordered pair."
        << exit(FatalError);

    return phase1_;
}


tnbLib::word tnbLib::phasePair::name() const
{
    word name2(phase2().name());
    name2[0] = toupper(name2[0]);
    return phase1().name() + "And" + name2;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::rho() const
{
    return phase1() * phase1().rho() + phase2() * phase2().rho();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::magUr() const
{
    return mag(phase1().U() - phase2().U());
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::phasePair::Ur() const
{
    return dispersed().U() - continuous().U();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::Re() const
{
    return magUr() * dispersed().d() / continuous().nu();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::Pr() const
{
    return
        continuous().nu() * continuous().Cp() * continuous().rho()
        / continuous().kappa();
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::Eo() const
{
    return EoH(dispersed().d());
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::EoH1() const
{
    return
        EoH
        (
            dispersed().d()
            * cbrt(1 + 0.163 * pow(Eo(), 0.757))
        );
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::EoH2() const
{
    return
        EoH
        (
            dispersed().d()
            / cbrt(E())
        );
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::Mo() const
{
    return
        mag(g())
        * continuous().nu()
        * pow3(continuous().nu() * continuous().rho() / sigma());
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::Ta() const
{
    return Re() * pow(Mo(), 0.23);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::phasePair::E() const
{
    FatalErrorInFunction
        << "Requested aspect ratio of the dispersed phase in an unordered pair"
        << exit(FatalError);

    return phase1();
}


// ************************************************************************* //
