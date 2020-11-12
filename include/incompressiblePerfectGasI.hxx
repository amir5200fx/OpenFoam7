#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::incompressiblePerfectGas<Specie>::incompressiblePerfectGas
(
	const Specie& sp, const scalar pRef
)
	:
	Specie(sp),
	pRef_(pRef)
{}


template<class Specie>
inline tnbLib::incompressiblePerfectGas<Specie>::incompressiblePerfectGas
(
	const word& name,
	const incompressiblePerfectGas<Specie>& ipg
)
	:
	Specie(name, ipg),
	pRef_(ipg.pRef_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::incompressiblePerfectGas<Specie>>
tnbLib::incompressiblePerfectGas<Specie>::clone() const
{
	return autoPtr<incompressiblePerfectGas<Specie>>
		(
			new incompressiblePerfectGas<Specie>(*this)
			);
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::incompressiblePerfectGas<Specie>>
tnbLib::incompressiblePerfectGas<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<incompressiblePerfectGas<Specie>>
		(
			new incompressiblePerfectGas<Specie>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::rho
(
	scalar p,
	scalar T
) const
{
	return pRef_ / (this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::H
(
	scalar p,
	scalar T
) const
{
	return p / this->rho(p, T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::Cp
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::E
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::Cv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::S
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::psi
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::Z
(
	scalar p,
	scalar T
) const
{
	return 0;
}


template<class Specie>
inline tnbLib::scalar tnbLib::incompressiblePerfectGas<Specie>::CpMCv
(
	scalar p,
	scalar T
) const
{
	return 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::incompressiblePerfectGas<Specie>::operator+=
(
	const incompressiblePerfectGas<Specie>& ipg
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(ipg);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = ipg.Y() / this->Y();

		pRef_ = Y1 * pRef_ + Y2 * ipg.pRef_;
	}
}


template<class Specie>
inline void tnbLib::incompressiblePerfectGas<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::incompressiblePerfectGas<Specie> tnbLib::operator+
(
	const incompressiblePerfectGas<Specie>& ipg1,
	const incompressiblePerfectGas<Specie>& ipg2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ipg1)
		+ static_cast<const Specie&>(ipg2)
	);

	if (mag(sp.Y()) < small)
	{
		return incompressiblePerfectGas<Specie>
			(
				sp,
				ipg1.pRef_
				);
	}
	else
	{
		const scalar Y1 = ipg1.Y() / sp.Y();
		const scalar Y2 = ipg2.Y() / sp.Y();

		return incompressiblePerfectGas<Specie>
			(
				sp,
				Y1*ipg1.pRef_ + Y2 * ipg2.pRef_
				);
	}
}


template<class Specie>
inline tnbLib::incompressiblePerfectGas<Specie> tnbLib::operator*
(
	const scalar s,
	const incompressiblePerfectGas<Specie>& ipg
	)
{
	return incompressiblePerfectGas<Specie>
		(
			s*static_cast<const Specie&>(ipg),
			ipg.pRef_
			);
}


template<class Specie>
inline tnbLib::incompressiblePerfectGas<Specie> tnbLib::operator==
(
	const incompressiblePerfectGas<Specie>& ipg1,
	const incompressiblePerfectGas<Specie>& ipg2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(ipg1)
		== static_cast<const Specie&>(ipg2)
	);

	const scalar Y1 = ipg1.Y() / sp.Y();
	const scalar Y2 = ipg2.Y() / sp.Y();

	return incompressiblePerfectGas<Specie>
		(
			sp,
			Y2*ipg2.pRef_ - Y1 * ipg1.pRef_
			);
}


// ************************************************************************* //

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::incompressiblePerfectGas<Specie>::incompressiblePerfectGas
(
	const dictionary& dict
)
	:
	Specie(dict),
	pRef_(readScalar(dict.subDict("equationOfState").lookup("pRef")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::incompressiblePerfectGas<Specie>::write(Ostream& os) const
{
	Specie::write(os);
	dictionary dict("equationOfState");
	dict.add("pRef", pRef_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const incompressiblePerfectGas<Specie>& pg
	)
{
	pg.write(os);
	return os;
}


// ************************************************************************* //