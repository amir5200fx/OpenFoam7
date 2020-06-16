#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline tnbLib::Random::type tnbLib::Random::sample()
{
	x_ = (A*x_ + C) % M;

	return x_ >> 17;
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::Random::Random(const label s)
	:
	x_((type(s) << 16) + 0x330E),
	scalarNormalStored_(false),
	scalarNormalValue_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

inline tnbLib::Random::~Random()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::Random::scalar01()
{
	return scalar(sample()) / (M >> 17);
}


inline tnbLib::scalar tnbLib::Random::scalarAB(const scalar a, const scalar b)
{
	return a + scalar01()*(b - a);
}


template<class Type>
inline Type tnbLib::Random::sample01()
{
	Type value;

	for (direction i = 0; i < pTraits<Type>::nComponents; ++i)
	{
		value.component(i) = scalar01();
	}

	return value;
}


template<>
inline tnbLib::scalar tnbLib::Random::sample01()
{
	return scalar01();
}


template<>
inline tnbLib::label tnbLib::Random::sample01()
{
	return sample() % 2;
}


template<class Type>
inline Type tnbLib::Random::sampleAB(const Type& a, const Type& b)
{
	return a + cmptMultiply(sample01<Type>(), b - a);
}


template<>
inline tnbLib::scalar tnbLib::Random::sampleAB(const scalar& a, const scalar& b)
{
	return scalarAB(a, b);
}


template<>
inline tnbLib::label tnbLib::Random::sampleAB(const label& a, const label& b)
{
	return a + sample() % (b - a);
}


template<class Type>
inline Type tnbLib::Random::sampleNormal()
{
	Type value;

	for (direction i = 0; i < pTraits<Type>::nComponents; ++i)
	{
		value.component(i) = scalarNormal();
	}

	return value;
}


template<>
inline tnbLib::scalar tnbLib::Random::sampleNormal()
{
	return scalarNormal();
}


// ************************************************************************* //