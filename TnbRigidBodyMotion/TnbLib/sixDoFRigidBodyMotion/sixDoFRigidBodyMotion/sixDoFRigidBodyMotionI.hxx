#pragma once
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

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::tensor tnbLib::sixDoFRigidBodyMotion::rotationTensorX
(
	scalar phi
) const
{
	return tensor
	(
		1, 0, 0,
		0, tnbLib::cos(phi), -tnbLib::sin(phi),
		0, tnbLib::sin(phi), tnbLib::cos(phi)
	);
}


inline tnbLib::tensor tnbLib::sixDoFRigidBodyMotion::rotationTensorY
(
	scalar phi
) const
{
	return tensor
	(
		tnbLib::cos(phi), 0, tnbLib::sin(phi),
		0, 1, 0,
		-tnbLib::sin(phi), 0, tnbLib::cos(phi)
	);
}


inline tnbLib::tensor tnbLib::sixDoFRigidBodyMotion::rotationTensorZ
(
	scalar phi
) const
{
	return tensor
	(
		tnbLib::cos(phi), -tnbLib::sin(phi), 0,
		tnbLib::sin(phi), tnbLib::cos(phi), 0,
		0, 0, 1
	);
}


inline tnbLib::Tuple2<tnbLib::tensor, tnbLib::vector>
tnbLib::sixDoFRigidBodyMotion::rotate
(
	const tensor& Q0,
	const vector& pi0,
	const scalar deltaT
) const
{
	Tuple2<tensor, vector> Qpi(Q0, pi0);
	tensor& Q = Qpi.first();
	vector& pi = Qpi.second();

	tensor R = rotationTensorX(0.5*deltaT*pi.x() / momentOfInertia_.xx());
	pi = pi & R;
	Q = Q & R;

	R = rotationTensorY(0.5*deltaT*pi.y() / momentOfInertia_.yy());
	pi = pi & R;
	Q = Q & R;

	R = rotationTensorZ(deltaT*pi.z() / momentOfInertia_.zz());
	pi = pi & R;
	Q = Q & R;

	R = rotationTensorY(0.5*deltaT*pi.y() / momentOfInertia_.yy());
	pi = pi & R;
	Q = Q & R;

	R = rotationTensorX(0.5*deltaT*pi.x() / momentOfInertia_.xx());
	pi = pi & R;
	Q = Q & R;

	return Qpi;
}


inline const tnbLib::PtrList<tnbLib::sixDoFRigidBodyMotionRestraint>&
tnbLib::sixDoFRigidBodyMotion::restraints() const
{
	return restraints_;
}


inline const tnbLib::PtrList<tnbLib::sixDoFRigidBodyMotionConstraint>&
tnbLib::sixDoFRigidBodyMotion::constraints() const
{
	return constraints_;
}


inline const tnbLib::point&
tnbLib::sixDoFRigidBodyMotion::initialCentreOfRotation() const
{
	return initialCentreOfRotation_;
}


inline const tnbLib::tensor&
tnbLib::sixDoFRigidBodyMotion::initialQ() const
{
	return initialQ_;
}


inline const tnbLib::tensor& tnbLib::sixDoFRigidBodyMotion::Q() const
{
	return motionState_.Q();
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::v() const
{
	return motionState_.v();
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::a() const
{
	return motionState_.a();
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::pi() const
{
	return motionState_.pi();
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::tau() const
{
	return motionState_.tau();
}


inline tnbLib::point& tnbLib::sixDoFRigidBodyMotion::initialCentreOfRotation()
{
	return initialCentreOfRotation_;
}


inline tnbLib::tensor& tnbLib::sixDoFRigidBodyMotion::initialQ()
{
	return initialQ_;
}


inline tnbLib::tensor& tnbLib::sixDoFRigidBodyMotion::Q()
{
	return motionState_.Q();
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::v()
{
	return motionState_.v();
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::a()
{
	return motionState_.a();
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::pi()
{
	return motionState_.pi();
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotion::tau()
{
	return motionState_.tau();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::sixDoFRigidBodyMotion::mass() const
{
	return mass_;
}


inline const tnbLib::diagTensor&
tnbLib::sixDoFRigidBodyMotion::momentOfInertia() const
{
	return momentOfInertia_;
}


inline const tnbLib::sixDoFRigidBodyMotionState&
tnbLib::sixDoFRigidBodyMotion::state() const
{
	return motionState_;
}


inline const tnbLib::point& tnbLib::sixDoFRigidBodyMotion::centreOfRotation() const
{
	return motionState_.centreOfRotation();
}


inline const tnbLib::point&
tnbLib::sixDoFRigidBodyMotion::initialCentreOfMass() const
{
	return initialCentreOfMass_;
}


inline tnbLib::point tnbLib::sixDoFRigidBodyMotion::centreOfMass() const
{
	return transform(initialCentreOfMass_);
}


inline tnbLib::vector tnbLib::sixDoFRigidBodyMotion::momentArm() const
{
	return centreOfMass() - motionState_.centreOfRotation();
}


inline const tnbLib::tensor&
tnbLib::sixDoFRigidBodyMotion::orientation() const
{
	return Q();
}


inline tnbLib::vector tnbLib::sixDoFRigidBodyMotion::omega() const
{
	return  Q() & (inv(momentOfInertia_) & pi());
}


inline bool tnbLib::sixDoFRigidBodyMotion::report() const
{
	return report_;
}


inline void tnbLib::sixDoFRigidBodyMotion::newTime()
{
	motionState0_ = motionState_;
}


inline tnbLib::point& tnbLib::sixDoFRigidBodyMotion::centreOfRotation()
{
	return motionState_.centreOfRotation();
}


inline tnbLib::point tnbLib::sixDoFRigidBodyMotion::velocity
(
	const point& pt
) const
{
	return (omega() ^ (pt - centreOfRotation())) + v();
}


inline tnbLib::point tnbLib::sixDoFRigidBodyMotion::transform
(
	const point& initialPoint
) const
{
	return
		(
			centreOfRotation()
			+ (Q() & initialQ_.T() & (initialPoint - initialCentreOfRotation_))
			);
}

// ************************************************************************* //
