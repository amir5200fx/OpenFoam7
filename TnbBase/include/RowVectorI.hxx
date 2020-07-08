#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Cmpt>
inline tnbLib::RowVector<Cmpt>::RowVector()
{}


template<class Cmpt>
inline tnbLib::RowVector<Cmpt>::RowVector(const tnbLib::zero)
	:
	RowVector::msType(Zero)
{}


template<class Cmpt>
template<class Cmpt2>
inline tnbLib::RowVector<Cmpt>::RowVector
(
	const MatrixSpace<RowVector<Cmpt2>, Cmpt2, 1, 3>& ms
)
	:
	RowVector::msType(ms)
{}


template<class Cmpt>
inline tnbLib::RowVector<Cmpt>::RowVector
(
	const Cmpt& rvx,
	const Cmpt& rvy,
	const Cmpt& rvz
)
{
	this->v_[X] = rvx;
	this->v_[Y] = rvy;
	this->v_[Z] = rvz;
}


template<class Cmpt>
inline tnbLib::RowVector<Cmpt>::RowVector(Istream& is)
	:
	RowVector::msType(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Cmpt>
inline const Cmpt& tnbLib::RowVector<Cmpt>::x() const
{
	return this->v_[X];
}

template<class Cmpt>
inline const Cmpt& tnbLib::RowVector<Cmpt>::y() const
{
	return this->v_[Y];
}

template<class Cmpt>
inline const Cmpt& tnbLib::RowVector<Cmpt>::z() const
{
	return this->v_[Z];
}


template<class Cmpt>
inline Cmpt& tnbLib::RowVector<Cmpt>::x()
{
	return this->v_[X];
}

template<class Cmpt>
inline Cmpt& tnbLib::RowVector<Cmpt>::y()
{
	return this->v_[Y];
}

template<class Cmpt>
inline Cmpt& tnbLib::RowVector<Cmpt>::z()
{
	return this->v_[Z];
}


// ************************************************************************* //