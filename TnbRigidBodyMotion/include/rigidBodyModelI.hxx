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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::RBD::rigidBodyModel::nBodies() const
{
	return bodies_.size();
}


inline tnbLib::PtrList<tnbLib::RBD::rigidBody>
tnbLib::RBD::rigidBodyModel::bodies() const
{
	return bodies_;
}


inline const tnbLib::DynamicList<tnbLib::label>&
tnbLib::RBD::rigidBodyModel::lambda() const
{
	return lambda_;
}


inline const tnbLib::PtrList<tnbLib::RBD::joint>&
tnbLib::RBD::rigidBodyModel::joints() const
{
	return joints_;
}


inline tnbLib::label tnbLib::RBD::rigidBodyModel::nDoF() const
{
	return nDoF_;
}


inline bool tnbLib::RBD::rigidBodyModel::unitQuaternions() const
{
	return unitQuaternions_;
}


inline const tnbLib::vector& tnbLib::RBD::rigidBodyModel::g() const
{
	return g_;
}


inline tnbLib::vector& tnbLib::RBD::rigidBodyModel::g()
{
	return g_;
}


inline const tnbLib::word& tnbLib::RBD::rigidBodyModel::name
(
	const label bodyID
) const
{
	if (merged(bodyID))
	{
		return mergedBody(bodyID).name();
	}
	else
	{
		return bodies_[bodyID].name();
	}
}


inline const tnbLib::RBD::rigidBodyInertia&
tnbLib::RBD::rigidBodyModel::I(const label i) const
{
	return bodies_[i];
}


inline const tnbLib::spatialVector&
tnbLib::RBD::rigidBodyModel::v(const label i) const
{
	return v_[i];
}


inline bool tnbLib::RBD::rigidBodyModel::merged(label bodyID) const
{
	return bodyID < 0;
}


inline tnbLib::label tnbLib::RBD::rigidBodyModel::master(label bodyID) const
{
	if (bodyID < 0)
	{
		return mergedBody(bodyID).masterID();
	}
	else
	{
		return bodyID;
	}
}


inline tnbLib::label
tnbLib::RBD::rigidBodyModel::mergedBodyID(const label mergedBodyIndex) const
{
	return -1 - mergedBodyIndex;
}


inline tnbLib::label
tnbLib::RBD::rigidBodyModel::mergedBodyIndex(const label mergedBodyID) const
{
	return -1 - mergedBodyID;
}


inline const tnbLib::RBD::subBody&
tnbLib::RBD::rigidBodyModel::mergedBody(label mergedBodyID) const
{
	if (!merged(mergedBodyID))
	{
		FatalErrorInFunction
			<< "Body " << mergedBodyID << " has not been merged"
			<< abort(FatalError);
	}

	return mergedBodies_[mergedBodyIndex(mergedBodyID)];
}


inline tnbLib::label tnbLib::RBD::rigidBodyModel::bodyID(const word& name) const
{
	return bodyIDs_[name];
}


inline tnbLib::vector tnbLib::RBD::rigidBodyModel::masterPoint
(
	const label bodyID,
	const vector& p
) const
{
	if (merged(bodyID))
	{
		return
			(
				mergedBody(bodyID).masterXT().inv()
				&& spatialVector(Zero, p)
				).l();
	}
	else
	{
		return p;
	}
}


inline tnbLib::spatialVector tnbLib::RBD::rigidBodyModel::v
(
	const label bodyID,
	const vector& p
) const
{
	return
		(
			spatialTransform
			(
				X0_[master(bodyID)].E().T(),
				masterPoint(bodyID, p)
			)
			& v_[master(bodyID)]
			);
}


// ************************************************************************* //
