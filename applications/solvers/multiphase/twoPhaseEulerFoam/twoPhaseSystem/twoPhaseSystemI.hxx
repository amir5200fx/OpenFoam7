#pragma once
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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class modelType>
const modelType& twoPhaseSystem::lookupSubModel
(
	const phasePair& key
) const
{
	return
		mesh().lookupObject<modelType>
		(
			IOobject::groupName(modelType::typeName, key.name())
			);
}


template<>
inline const dragModel& twoPhaseSystem::lookupSubModel<dragModel>
(
	const phaseModel& dispersed,
	const phaseModel& continuous
	) const
{
	return drag_->phaseModel(dispersed);
}


template<>
inline const virtualMassModel& twoPhaseSystem::lookupSubModel<virtualMassModel>
(
	const phaseModel& dispersed,
	const phaseModel& continuous
	) const
{
	return virtualMass_->phaseModel(dispersed);
}

inline const tnbLib::fvMesh& tnbLib::twoPhaseSystem::mesh() const
{
    return mesh_;
}


inline const tnbLib::phaseModel& tnbLib::twoPhaseSystem::phase1() const
{
    return phase1_;
}


inline tnbLib::phaseModel& tnbLib::twoPhaseSystem::phase1()
{
    return phase1_;
}


inline const tnbLib::phaseModel& tnbLib::twoPhaseSystem::phase2() const
{
    return phase2_;
}


inline tnbLib::phaseModel& tnbLib::twoPhaseSystem::phase2()
{
    return phase2_;
}


inline const tnbLib::phaseModel& tnbLib::twoPhaseSystem::otherPhase
(
    const phaseModel& phase
) const
{
    if (&phase == &phase1_)
    {
        return phase2_;
    }
    else
    {
        return phase1_;
    }
}


inline const tnbLib::surfaceScalarField& tnbLib::twoPhaseSystem::phi() const
{
    return phi_;
}


inline tnbLib::surfaceScalarField& tnbLib::twoPhaseSystem::phi()
{
    return phi_;
}


inline const tnbLib::volScalarField& tnbLib::twoPhaseSystem::dgdt() const
{
    return dgdt_;
}


inline tnbLib::volScalarField& tnbLib::twoPhaseSystem::dgdt()
{
    return dgdt_;
}


inline tnbLib::tmp<tnbLib::surfaceScalarField>& tnbLib::twoPhaseSystem::pPrimeByA()
{
    return pPrimeByA_;
}


// ************************************************************************* //
