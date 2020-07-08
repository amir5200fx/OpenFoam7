#pragma once
#include <UList.hxx>
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <tnbLib::direction N>
inline tnbLib::Roots<N>::Roots()
	:
	types_(0)
{
	for (tnbLib::label i=0; i<(*this).size(); i++)
	{
		type(i, rootType::nan);
	}
}


template <tnbLib::direction N>
inline tnbLib::Roots<N>::Roots(const rootType t, const scalar x)
	:
	types_(0)
{
	for (tnbLib::label i=0; i<(*this).size(); i++)
	{
		this->v_[i] = x;
		type(i, t);
	}
}


template <tnbLib::direction N>
inline tnbLib::Roots<N>::Roots
(
	const rootType t,
	const scalar x,
	const Roots<N - 1>& xs
)
	:
	types_(0)
{
	this->v_[0] = x;
	type(0, t);
	for (tnbLib::label i=0; i<(xs).size(); i++)
	{
		this->v_[i + 1] = xs[i];
		type(i + 1, xs.type(i));
	}
}


template <tnbLib::direction N>
inline tnbLib::Roots<N>::Roots
(
	const Roots<N - 1>& xs,
	const rootType t,
	const scalar x
)
	:
	types_(0)
{
	for (tnbLib::label i=0; i<(xs).size(); i++)
	{
		this->v_[i] = xs[i];
		type(i, xs.type(i));
	}
	this->v_[N - 1] = x;
	type(N - 1, t);
}


template <tnbLib::direction N>
template <tnbLib::direction M>
inline tnbLib::Roots<N>::Roots
(
	const Roots<M>& xs,
	const Roots<N - M>& ys
)
	:
	types_(0)
{
	for (tnbLib::label i=0; i<(xs).size(); i++)
	{
		this->v_[i] = xs[i];
		type(i, xs.type(i));
	}
	for (tnbLib::label i=0; i<(ys).size(); i++)
	{
		this->v_[i + M] = ys[i];
		type(i + M, ys.type(i));
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <tnbLib::direction N>
inline void tnbLib::Roots<N>::type
(
	const direction i,
	const rootType t
)
{
	types_ += (static_cast<int>(t) - static_cast<int>(type(i))) << 3 * i;
}


template <tnbLib::direction N>
inline tnbLib::rootType tnbLib::Roots<N>::type(const direction i) const
{
	return static_cast<rootType>((types_ >> 3 * i) & 7);
}


// ************************************************************************* //