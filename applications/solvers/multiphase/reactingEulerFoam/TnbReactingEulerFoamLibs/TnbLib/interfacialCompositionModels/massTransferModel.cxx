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

#define FoamRegisterDebugSwitch_EXPORT_DEFINE  //added by Payvand

#include <massTransferModel.hxx>

#include <phasePair.hxx>
#include <BlendedInterfacialModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(massTransferModel, 0);
    defineBlendedInterfacialModelTypeNameAndDebug(massTransferModel, 0);
    defineRunTimeSelectionTable(massTransferModel, dictionary);
}

const tnbLib::dimensionSet tnbLib::massTransferModel::dimK(0, -2, 0, 0, 0);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::massTransferModel::massTransferModel
(
    const dictionary& dict,
    const phasePair& pair
)
    :
    pair_(pair)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::massTransferModel::~massTransferModel()
{}


// ************************************************************************* //
