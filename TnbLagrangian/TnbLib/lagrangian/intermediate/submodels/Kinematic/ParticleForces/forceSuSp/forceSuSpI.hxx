#pragma once
// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

inline tnbLib::forceSuSp::forceSuSp()
{}


inline tnbLib::forceSuSp::forceSuSp
(
	const Tuple2<vector, scalar>& fs
)
	:
	Tuple2<vector, scalar>(fs)
{}


inline tnbLib::forceSuSp::forceSuSp(const vector& Su, const scalar Sp)
{
	first() = Su;
	second() = Sp;
}


inline tnbLib::forceSuSp::forceSuSp(Istream& is)
	:
	Tuple2<vector, scalar>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::vector& tnbLib::forceSuSp::Su() const
{
	return first();
}


inline tnbLib::scalar tnbLib::forceSuSp::Sp() const
{
	return second();
}


inline tnbLib::vector& tnbLib::forceSuSp::Su()
{
	return first();
}


inline tnbLib::scalar& tnbLib::forceSuSp::Sp()
{
	return second();
}


// * * * * * * * * * * * * * * * Operators * * * * * * * * * * * * * * * * * //

inline void tnbLib::forceSuSp::operator+=(const forceSuSp& susp)
{
	first() += susp.first();
	second() += susp.second();
}


inline void tnbLib::forceSuSp::operator-=(const forceSuSp& susp)
{
	first() -= susp.first();
	second() -= susp.second();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline tnbLib::forceSuSp tnbLib::operator+
(
	const forceSuSp& susp1,
	const forceSuSp& susp2
	)
{
	return forceSuSp
	(
		susp1.first() + susp2.first(),
		susp1.second() + susp2.second()
	);
}


inline tnbLib::forceSuSp tnbLib::operator*
(
	const scalar s,
	const forceSuSp& susp
	)
{
	return forceSuSp(susp.first()*s, susp.second()*s);
}


// ************************************************************************* //