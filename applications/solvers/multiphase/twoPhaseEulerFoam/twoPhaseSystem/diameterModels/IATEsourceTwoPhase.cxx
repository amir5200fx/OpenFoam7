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

#include <includeAllModules.hxx>

#include "IATEsourceTwoPhase.hxx"

#include "twoPhaseSystem.hxx"

#include <fvMatrix.hxx>
#include <PhaseCompressibleTurbulenceModel.hxx>
#include <uniformDimensionedFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        defineTypeNameAndDebug(IATEsource, 0);
        defineRunTimeSelectionTable(IATEsource, dictionary);
    }
}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::diameterModels::IATEsource>
tnbLib::diameterModels::IATEsource::New
(
    const word& type,
    const IATE& iate,
    const dictionary& dict
)
{
    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(type);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown IATE source type "
            << type << nl << nl
            << "Valid IATE source types : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<IATEsource>(cstrIter()(iate, dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::Ur() const
{
    const uniformDimensionedVectorField& g =
        phase().U().db().lookupObject<uniformDimensionedVectorField>("g");

    return
        sqrt(2.0)
        * pow025
        (
            fluid().sigma() * mag(g)
            * (otherPhase().rho() - phase().rho())
            / sqr(otherPhase().rho())
        )
        * pow(max(1 - phase(), scalar(0)), 1.75);
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::Ut() const
{
    return sqrt(2 * otherPhase().turbulence().k());
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::Re() const
{
    return max(Ur() * phase().d() / otherPhase().nu(), scalar(1.0e-3));
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::CD() const
{
    const volScalarField Eo(this->Eo());
    const volScalarField Re(this->Re());

    return
        max
        (
            min
            (
                (16 / Re) * (1 + 0.15 * pow(Re, 0.687)),
                48 / Re
            ),
            8 * Eo / (3 * (Eo + 4))
        );
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::Mo() const
{
    const uniformDimensionedVectorField& g =
        phase().U().db().lookupObject<uniformDimensionedVectorField>("g");

    return
        mag(g) * pow4(otherPhase().nu()) * sqr(otherPhase().rho())
        * (otherPhase().rho() - phase().rho())
        / pow3(fluid().sigma());
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::Eo() const
{
    const uniformDimensionedVectorField& g =
        phase().U().db().lookupObject<uniformDimensionedVectorField>("g");

    return
        mag(g) * sqr(phase().d())
        * (otherPhase().rho() - phase().rho())
        / fluid().sigma();
}

tnbLib::tmp<tnbLib::volScalarField> tnbLib::diameterModels::IATEsource::We() const
{
    return otherPhase().rho() * sqr(Ur()) * phase().d() / fluid().sigma();
}


// ************************************************************************* //
