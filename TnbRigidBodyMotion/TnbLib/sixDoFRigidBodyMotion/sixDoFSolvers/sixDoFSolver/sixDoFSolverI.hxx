#pragma once
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

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

inline tnbLib::point& tnbLib::sixDoFSolver::centreOfRotation()
{
	return body_.motionState_.centreOfRotation();
}

inline tnbLib::tensor& tnbLib::sixDoFSolver::Q()
{
	return body_.motionState_.Q();
}

inline tnbLib::vector& tnbLib::sixDoFSolver::v()
{
	return body_.motionState_.v();
}

inline tnbLib::vector& tnbLib::sixDoFSolver::a()
{
	return body_.motionState_.a();
}

inline tnbLib::vector& tnbLib::sixDoFSolver::pi()
{
	return body_.motionState_.pi();
}

inline tnbLib::vector& tnbLib::sixDoFSolver::tau()
{
	return body_.motionState_.tau();
}


inline const tnbLib::point& tnbLib::sixDoFSolver::centreOfRotation0() const
{
	return body_.motionState0_.centreOfRotation();
}

inline const tnbLib::tensor& tnbLib::sixDoFSolver::Q0() const
{
	return body_.motionState0_.Q();
}


inline const tnbLib::vector& tnbLib::sixDoFSolver::v0() const
{
	return body_.motionState0_.v();
}


inline const tnbLib::vector& tnbLib::sixDoFSolver::a0() const
{
	return body_.motionState0_.a();
}


inline const tnbLib::vector& tnbLib::sixDoFSolver::pi0() const
{
	return body_.motionState0_.pi();
}


inline const tnbLib::vector& tnbLib::sixDoFSolver::tau0() const
{
	return body_.motionState0_.tau();
}

inline tnbLib::scalar tnbLib::sixDoFSolver::aDamp() const
{
	return body_.aDamp_;
}

inline tnbLib::tensor tnbLib::sixDoFSolver::tConstraints() const
{
	return body_.tConstraints_;
}

inline tnbLib::tensor tnbLib::sixDoFSolver::rConstraints() const
{
	return body_.rConstraints_;
}

//- Apply rotation tensors to Q0 for the given torque (pi) and deltaT
//  and return the rotated Q and pi as a tuple
inline tnbLib::Tuple2<tnbLib::tensor, tnbLib::vector> tnbLib::sixDoFSolver::rotate
(
	const tensor& Q0,
	const vector& pi,
	const scalar deltaT
) const
{
	return body_.rotate(Q0, pi, deltaT);
}

//- Update and relax accelerations from the force and torque
inline void tnbLib::sixDoFSolver::updateAcceleration
(
	const vector& fGlobal,
	const vector& tauGlobal
)
{
	body_.updateAcceleration(fGlobal, tauGlobal);
}


// ************************************************************************* //
