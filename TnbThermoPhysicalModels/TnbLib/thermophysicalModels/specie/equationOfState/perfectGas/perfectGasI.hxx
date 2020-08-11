#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectGas<Specie>::perfectGas(const Specie& sp)
	:
	Specie(sp)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectGas<Specie>::perfectGas
(
	const word& name,
	const perfectGas<Specie>& pg
)
	:
	Specie(name, pg)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::perfectGas<Specie>>
tnbLib::perfectGas<Specie>::clone() const
{
	return autoPtr<perfectGas<Specie>>(new perfectGas<Specie>(*this));
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::perfectGas<Specie>> tnbLib::perfectGas<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<perfectGas<Specie>>(new perfectGas<Specie>(dict));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::rho(scalar p, scalar T) const
{
	return p / (this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::H(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::Cp(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::E(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::Cv(scalar p, scalar T) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::S(scalar p, scalar T) const
{
	return -this->R()*log(p / Pstd);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::psi(scalar p, scalar T) const
{
	return 1.0 / (this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::Z(scalar p, scalar T) const
{
	return 1;
}


template<class Specie>
inline tnbLib::scalar tnbLib::perfectGas<Specie>::CpMCv(scalar p, scalar T) const
{
	return this->R();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::perfectGas<Specie>::operator+=(const perfectGas<Specie>& pg)
{
	Specie::operator+=(pg);
}


template<class Specie>
inline void tnbLib::perfectGas<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::perfectGas<Specie> tnbLib::operator+
(
	const perfectGas<Specie>& pg1,
	const perfectGas<Specie>& pg2
	)
{
	return perfectGas<Specie>
		(
			static_cast<const Specie&>(pg1) + static_cast<const Specie&>(pg2)
			);
}


template<class Specie>
inline tnbLib::perfectGas<Specie> tnbLib::operator*
(
	const scalar s,
	const perfectGas<Specie>& pg
	)
{
	return perfectGas<Specie>(s*static_cast<const Specie&>(pg));
}


template<class Specie>
inline tnbLib::perfectGas<Specie> tnbLib::operator==
(
	const perfectGas<Specie>& pg1,
	const perfectGas<Specie>& pg2
	)
{
	return perfectGas<Specie>
		(
			static_cast<const Specie&>(pg1) == static_cast<const Specie&>(pg2)
			);
}


// ************************************************************************* //