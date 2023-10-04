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

#include "constantTurbulentDispersionCoefficientTwoPhase.hxx"

#include "phasePairTwoPhase.hxx"

#include <PhaseCompressibleTurbulenceModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace turbulentDispersionModels
    {
        defineTypeNameAndDebug(constantTurbulentDispersionCoefficient, 0);
        addToRunTimeSelectionTable
        (
            turbulentDispersionModel,
            constantTurbulentDispersionCoefficient,
            dictionary
        );
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::constantTurbulentDispersionCoefficient::
constantTurbulentDispersionCoefficient
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    turbulentDispersionModel(dict, pair),
    Ctd_("Ctd", dimless, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::turbulentDispersionModels::constantTurbulentDispersionCoefficient::
~constantTurbulentDispersionCoefficient()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::turbulentDispersionModels::constantTurbulentDispersionCoefficient::
D() const
{
    return
        Ctd_
        * pair_.dispersed()
        * pair_.continuous().rho()
        * pair_.continuous().turbulence().k();
}


// ************************************************************************* //
