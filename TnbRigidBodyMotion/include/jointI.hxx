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

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::RBD::joint::joint(const rigidBodyModel& model, const label nDoF)
	:
	model_(model),
	S_(nDoF),
	index_(0),
	qIndex_(0)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::RBD::joint::nDoF() const
{
	return S_.size();
}

inline bool tnbLib::RBD::joint::unitQuaternion() const
{
	return false;
}

inline tnbLib::label tnbLib::RBD::joint::index() const
{
	return index_;
}

inline tnbLib::label tnbLib::RBD::joint::qIndex() const
{
	return qIndex_;
}

inline const tnbLib::List<tnbLib::spatialVector>& tnbLib::RBD::joint::S() const
{
	return S_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::RBD::joint::operator=(const joint& j)
{
	S_ = j.S_;
	index_ = j.index_;
	qIndex_ = j.qIndex_;
}


inline tnbLib::quaternion tnbLib::RBD::joint::unitQuaternion
(
	const scalarField& q
) const
{
	if (!unitQuaternion())
	{
		FatalErrorInFunction
			<< "Attempt to get the quaternion for a non-spherical joint"
			<< abort(FatalError);
	}

	return quaternion::unit(q.block<vector>(qIndex_));
}


inline void tnbLib::RBD::joint::unitQuaternion
(
	const quaternion& quat,
	scalarField& q
) const
{
	if (!unitQuaternion())
	{
		FatalErrorInFunction
			<< "Attempt to set quaternion for a non-spherical joint"
			<< abort(FatalError);
	}

	q[qIndex_] = quat.v().x();
	q[qIndex_ + 1] = quat.v().y();
	q[qIndex_ + 2] = quat.v().z();
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joint::iNew::operator()
(
	Istream& is
	) const
{
	dictionary dict(is);
	return New(model_, dict);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::RBD::operator<<(Ostream& os, const joint& j)
{
	os << indent << token::BEGIN_BLOCK << incrIndent << endl;
	j.write(os);
	os << decrIndent << indent << token::END_BLOCK;

	return os;
}


// ************************************************************************* //
