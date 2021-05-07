#pragma once
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

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

inline tnbLib::RBD::rigidBodyModelState& tnbLib::RBD::rigidBodySolver::state()
{
	return model_.motionState_;
}


inline tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::q()
{
	return state().q();
}


inline tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::qDot()
{
	return state().qDot();
}


inline tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::qDdot()
{
	return state().qDdot();
}


inline tnbLib::scalar tnbLib::RBD::rigidBodySolver::deltaT() const
{
	return model_.motionState_.deltaT();
}


inline const tnbLib::RBD::rigidBodyModelState&
tnbLib::RBD::rigidBodySolver::state0() const
{
	return model_.motionState0_;
}

inline const tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::q0() const
{
	return state0().q();
}


inline const tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::qDot0() const
{
	return state0().qDot();
}


inline const tnbLib::scalarField& tnbLib::RBD::rigidBodySolver::qDdot0() const
{
	return state0().qDdot();
}


inline tnbLib::scalar tnbLib::RBD::rigidBodySolver::deltaT0() const
{
	return model_.motionState0_.deltaT();
}


// ************************************************************************* //
