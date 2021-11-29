#pragma once
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

// * * * * * * * * * * * * Private Member Functions * * * * * * * * * * * * //

inline tnbLib::label tnbLib::diameterModels::populationBalanceModel::nCorr() const
{
    return mesh_.solverDict(name_).lookupType<label>("nCorr");
}


inline tnbLib::label
tnbLib::diameterModels::populationBalanceModel::sourceUpdateInterval() const
{
    return
        mesh_.solverDict(name_)
        .lookupOrDefault<label>("sourceUpdateInterval", 1);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::phaseSystem&
tnbLib::diameterModels::populationBalanceModel::fluid() const
{
    return fluid_;
}


inline const tnbLib::fvMesh&
tnbLib::diameterModels::populationBalanceModel::mesh() const
{
    return mesh_;
}


inline const tnbLib::dictionary&
tnbLib::diameterModels::populationBalanceModel::dict() const
{
    return dict_;
}


inline const tnbLib::phaseModel&
tnbLib::diameterModels::populationBalanceModel::continuousPhase() const
{
    return continuousPhase_;
}


inline const tnbLib::UPtrList<tnbLib::diameterModels::velocityGroup>&
tnbLib::diameterModels::populationBalanceModel::velocityGroups() const
{
    return velocityGroups_;
}


inline const tnbLib::UPtrList<tnbLib::diameterModels::sizeGroup>&
tnbLib::diameterModels::populationBalanceModel::sizeGroups() const
{
    return sizeGroups_;
}


inline const tnbLib::diameterModels::populationBalanceModel::phasePairTable&
tnbLib::diameterModels::populationBalanceModel::phasePairs() const
{
    return phasePairs_;
}


inline const tnbLib::PtrList<tnbLib::dimensionedScalar>&
tnbLib::diameterModels::populationBalanceModel::v() const
{
    return v_;
}


inline const tnbLib::volScalarField&
tnbLib::diameterModels::populationBalanceModel::alphas() const
{
    if (velocityGroups_.size() > 1)
    {
        return alphas_();
    }
    else
    {
        return velocityGroups_.first().phase();
    }
}


inline const tnbLib::volVectorField&
tnbLib::diameterModels::populationBalanceModel::U() const
{
    if (velocityGroups_.size() > 1)
    {
        return U_();
    }
    else
    {
        return velocityGroups_.first().phase().U();
    }
}


// ************************************************************************* //
