#pragma once
#include <dictionary.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::LandauTellerReactionRate::LandauTellerReactionRate
(
	const scalar A,
	const scalar beta,
	const scalar Ta,
	const scalar B,
	const scalar C
)
	:
	A_(A),
	beta_(beta),
	Ta_(Ta),
	B_(B),
	C_(C)
{}


inline tnbLib::LandauTellerReactionRate::LandauTellerReactionRate
(
	const speciesTable&,
	const dictionary& dict
)
	:
	A_(readScalar(dict.lookup("A"))),
	beta_(readScalar(dict.lookup("beta"))),
	Ta_(readScalar(dict.lookup("Ta"))),
	B_(readScalar(dict.lookup("B"))),
	C_(readScalar(dict.lookup("C")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::LandauTellerReactionRate::operator()
(
	const scalar p,
	const scalar T,
	const scalarField&
	) const
{
	scalar lta = A_;

	if (mag(beta_) > vSmall)
	{
		lta *= pow(T, beta_);
	}

	scalar expArg = 0;

	if (mag(Ta_) > vSmall)
	{
		expArg -= Ta_ / T;
	}

	if (mag(B_) > vSmall)
	{
		expArg += B_ / cbrt(T);
	}

	if (mag(C_) > vSmall)
	{
		expArg += C_ / pow(T, 2.0 / 3.0);
	}

	if (mag(expArg) > vSmall)
	{
		lta *= exp(expArg);
	}

	return lta;
}


inline tnbLib::scalar tnbLib::LandauTellerReactionRate::ddT
(
	const scalar p,
	const scalar T,
	const scalarField&
) const
{
	scalar lta = A_;

	if (mag(beta_) > vSmall)
	{
		lta *= pow(T, beta_);
	}

	scalar expArg = 0;
	scalar deriv = 0;

	if (mag(Ta_) > vSmall)
	{
		scalar TaT = Ta_ / T;
		expArg -= TaT;
		deriv += TaT;
	}

	if (mag(B_) > vSmall)
	{
		scalar BT = B_ / cbrt(T);
		expArg += BT;
		deriv -= BT / 3;
	}

	if (mag(C_) > vSmall)
	{
		scalar CT = C_ / pow(T, 2.0 / 3.0);
		expArg += CT;
		deriv -= 2 * CT / 3;
	}

	if (mag(expArg) > vSmall)
	{
		lta *= exp(expArg);
	}

	return lta * (beta_ + deriv) / T;
}


inline const tnbLib::List<tnbLib::Tuple2<tnbLib::label, tnbLib::scalar>>&
tnbLib::LandauTellerReactionRate::beta() const
{
	return NullObjectRef<List<Tuple2<label, scalar>>>();
}


inline void tnbLib::LandauTellerReactionRate::dcidc
(
	const scalar p,
	const scalar T,
	const scalarField& c,
	scalarField& dcidc
) const
{}


inline tnbLib::scalar tnbLib::LandauTellerReactionRate::dcidT
(
	const scalar p,
	const scalar T,
	const scalarField& c
) const
{
	return 0;
}


inline void tnbLib::LandauTellerReactionRate::write(Ostream& os) const
{
	writeEntry(os, "A", A_);
	writeEntry(os, "beta", beta_);
	writeEntry(os, "Ta", Ta_);
	writeEntry(os, "B", B_);
	writeEntry(os, "C", C_);
}


inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const LandauTellerReactionRate& arr
	)
{
	arr.write(os);
	return os;
}


// ************************************************************************* //