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

inline tnbLib::RBD::subBody::subBody
(
	const autoPtr<rigidBody>& bodyPtr,
	const word& masterName,
	const label masterID,
	const spatialTransform& masterXT
)
	:
	body_(bodyPtr),
	masterName_(masterName),
	masterID_(masterID),
	masterXT_(masterXT)
{}


inline tnbLib::autoPtr<tnbLib::RBD::subBody> tnbLib::RBD::subBody::clone() const
{
	return autoPtr<subBody>(new subBody(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::RBD::rigidBody& tnbLib::RBD::subBody::body() const
{
	return body_();
}


inline const tnbLib::word& tnbLib::RBD::subBody::name() const
{
	return body_->name();
}


inline const tnbLib::word& tnbLib::RBD::subBody::masterName() const
{
	return masterName_;
}


inline tnbLib::label tnbLib::RBD::subBody::masterID() const
{
	return masterID_;
}


inline const tnbLib::spatialTransform& tnbLib::RBD::subBody::masterXT() const
{
	return masterXT_;
}


// ************************************************************************* //
