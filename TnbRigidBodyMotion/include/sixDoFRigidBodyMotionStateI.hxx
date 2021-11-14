#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::point&
tnbLib::sixDoFRigidBodyMotionState::centreOfRotation() const
{
	return centreOfRotation_;
}


inline const tnbLib::tensor& tnbLib::sixDoFRigidBodyMotionState::Q() const
{
	return Q_;
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::v() const
{
	return v_;
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::a() const
{
	return a_;
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::pi() const
{
	return pi_;
}


inline const tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::tau() const
{
	return tau_;
}


inline tnbLib::point& tnbLib::sixDoFRigidBodyMotionState::centreOfRotation()
{
	return centreOfRotation_;
}


inline tnbLib::tensor& tnbLib::sixDoFRigidBodyMotionState::Q()
{
	return Q_;
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::v()
{
	return v_;
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::a()
{
	return a_;
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::pi()
{
	return pi_;
}


inline tnbLib::vector& tnbLib::sixDoFRigidBodyMotionState::tau()
{
	return tau_;
}


// ************************************************************************* //