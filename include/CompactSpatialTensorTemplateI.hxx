#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::CompactSpatialTensor<Cmpt>::CompactSpatialTensor()
{}


template<class Cmpt>
inline tnbLib::CompactSpatialTensor<Cmpt>::CompactSpatialTensor
(
	const tnbLib::zero
)
	:
	CompactSpatialTensor::msType(Zero)
{}


template<class Cmpt>
inline tnbLib::CompactSpatialTensor<Cmpt>::CompactSpatialTensor
(
	const typename CompactSpatialTensor::msType& ms
)
	:
	CompactSpatialTensor::msType(ms)
{}


template<class Cmpt>
inline tnbLib::CompactSpatialTensor<Cmpt>::CompactSpatialTensor
(
	const Cmpt& t00, const Cmpt& t01, const Cmpt& t02,
	const Cmpt& t10, const Cmpt& t11, const Cmpt& t12,
	const Cmpt& t20, const Cmpt& t21, const Cmpt& t22,
	const Cmpt& t30, const Cmpt& t31, const Cmpt& t32,
	const Cmpt& t40, const Cmpt& t41, const Cmpt& t42,
	const Cmpt& t50, const Cmpt& t51, const Cmpt& t52
)
{
	this->v_[0] = t00;
	this->v_[1] = t01;
	this->v_[2] = t02;

	this->v_[3 + 0] = t10;
	this->v_[3 + 1] = t11;
	this->v_[3 + 2] = t12;

	this->v_[6 + 0] = t20;
	this->v_[6 + 1] = t21;
	this->v_[6 + 2] = t22;

	this->v_[9 + 0] = t30;
	this->v_[9 + 1] = t31;
	this->v_[9 + 2] = t32;

	this->v_[12 + 0] = t40;
	this->v_[12 + 1] = t41;
	this->v_[12 + 2] = t42;

	this->v_[15 + 0] = t50;
	this->v_[15 + 1] = t51;
	this->v_[15 + 2] = t52;
}


template<class Cmpt>
inline tnbLib::CompactSpatialTensor<Cmpt>::CompactSpatialTensor(Istream& is)
	:
	CompactSpatialTensor::msType(is)
{}


// ************************************************************************* //