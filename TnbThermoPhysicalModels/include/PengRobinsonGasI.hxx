#pragma once
#include <mathematicalConstants.hxx>
#include <thermodynamicConstants.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Specie>
inline tnbLib::PengRobinsonGas<Specie>::PengRobinsonGas
(
	const Specie& sp,
	const scalar& Tc,
	const scalar& Vc,
	const scalar& Zc,
	const scalar& Pc,
	const scalar& omega
)
	:
	Specie(sp),
	Tc_(Tc),
	Vc_(Vc),
	Zc_(Zc),
	Pc_(Pc),
	omega_(omega)
{}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::PengRobinsonGas<Specie>::PengRobinsonGas
(
	const word& name,
	const PengRobinsonGas& pg
)
	:
	Specie(name, pg),
	Tc_(pg.Tc_),
	Vc_(pg.Vc_),
	Zc_(pg.Zc_),
	Pc_(pg.Pc_),
	omega_(pg.omega_)
{}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::PengRobinsonGas <Specie>>
tnbLib::PengRobinsonGas<Specie>::clone() const
{
	return autoPtr<PengRobinsonGas<Specie>>
		(
			new PengRobinsonGas<Specie>(*this)
			);
}


template<class Specie>
inline tnbLib::autoPtr<tnbLib::PengRobinsonGas<Specie>>
tnbLib::PengRobinsonGas<Specie>::New
(
	const dictionary& dict
)
{
	return autoPtr<PengRobinsonGas<Specie>>
		(
			new PengRobinsonGas<Specie>(dict)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::rho
(
	scalar p,
	scalar T
) const
{
	const scalar Z = this->Z(p, T);
	return p / (Z*this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::H(scalar p, scalar T) const
{
	const scalar Pr = p / Pc_;
	const scalar Tr = T / Tc_;
	const scalar B = 0.07780*Pr / Tr;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);
	const scalar alpha = sqr(1 + kappa * (1 - sqrt(Tr)));

	const scalar Z = this->Z(p, T);

	return
		this->R()
		*Tc_
		*(
			Tr*(Z - 1)
			- 2.078*(1 + kappa)*sqrt(alpha)
			*log((Z + 2.414*B) / (Z - 0.414*B))
			);
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::Cp(scalar p, scalar T) const
{
	const scalar Tr = T / Tc_;
	const scalar a = 0.45724*sqr(constant::thermodynamic::RR*Tc_) / Pc_;
	const scalar b = 0.07780*constant::thermodynamic::RR*Tc_ / Pc_;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);
	const scalar alpha = sqr(1 + kappa * (1 - sqrt(Tr)));

	const scalar A = a * alpha*p / sqr(constant::thermodynamic::RR*T);
	const scalar B = b * p / (constant::thermodynamic::RR*T);

	const scalar Z = this->Z(p, T);

	const scalar ap = kappa * a*(kappa / Tc_ - (1 + kappa) / sqrt(T*Tc_));
	const scalar app = kappa * a*(1 + kappa) / (2 * sqrt(pow3(T)*Tc_));

	const scalar M = (sqr(Z) + 2 * B*Z - sqr(B)) / (Z - B);
	const scalar N = ap * B / (b*constant::thermodynamic::RR);

	const scalar root2 = sqrt(2.0);

	return
		(
			app*(T / (2 * root2*b))*log((Z + (root2 + 1)*B) / (Z - (root2 - 1)*B))
			+ constant::thermodynamic::RR * sqr(M - N) / (sqr(M) - 2 * A*(Z + B))
			- constant::thermodynamic::RR
			) / this->W();
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::E(scalar p, scalar T) const
{
	const scalar Pr = p / Pc_;
	const scalar Tr = T / Tc_;
	const scalar B = 0.07780*Pr / Tr;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);
	const scalar alpha = sqr(1 + kappa * (1 - sqrt(Tr)));

	const scalar Z = this->Z(p, T);

	return
		this->R()
		*Tc_
		*(
			-2.078*(1 + kappa)*sqrt(alpha)
			*log((Z + 2.414*B) / (Z - 0.414*B))
			);
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::Cv(scalar p, scalar T) const
{
	const scalar a = 0.45724*sqr(constant::thermodynamic::RR*Tc_) / Pc_;
	const scalar b = 0.07780*constant::thermodynamic::RR*Tc_ / Pc_;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);

	const scalar B = b * p / (constant::thermodynamic::RR*T);

	const scalar Z = this->Z(p, T);

	const scalar app = kappa * a*(1 + kappa) / (2 * sqrt(pow3(T)*Tc_));

	const scalar root2 = sqrt(2.0);

	return
		(
			app*(T / (2 * root2*b))*log((Z + (root2 + 1)*B) / (Z - (root2 - 1)*B))
			- constant::thermodynamic::RR
			) / this->W();
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::S
(
	scalar p,
	scalar T
) const
{
	const scalar Pr = p / Pc_;
	const scalar Tr = T / Tc_;
	const scalar B = 0.07780*Pr / Tr;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);

	const scalar Z = this->Z(p, T);

	return
		this->R()
		*(
			-log(p / constant::thermodynamic::Pstd)
			+ (
				log(Z - B)
				- 2.078*kappa*((1 + kappa) / sqrt(Tr) - kappa)
				*log((Z + 2.414*B) / (Z - 0.414*B))
				)
			);
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::psi
(
	scalar p,
	scalar T
) const
{
	const scalar Z = this->Z(p, T);

	return 1.0 / (Z*this->R()*T);
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::Z
(
	scalar p,
	scalar T
) const
{
	const scalar Tr = T / Tc_;
	const scalar a = 0.45724*sqr(constant::thermodynamic::RR*Tc_) / Pc_;
	const scalar b = 0.07780*constant::thermodynamic::RR*Tc_ / Pc_;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);
	const scalar alpha = sqr(1 + kappa * (1 - sqrt(Tr)));

	const scalar A = a * alpha*p / sqr(constant::thermodynamic::RR*T);
	const scalar B = b * p / (constant::thermodynamic::RR*T);

	const scalar a2 = B - 1;
	const scalar a1 = A - 2 * B - 3 * sqr(B);
	const scalar a0 = -A * B + sqr(B) + pow3(B);

	const scalar Q = (3 * a1 - a2 * a2) / 9.0;
	const scalar Rl = (9 * a2*a1 - 27 * a0 - 2 * a2*a2*a2) / 54.0;

	const scalar Q3 = Q * Q*Q;
	const scalar D = Q3 + Rl * Rl;

	scalar root = -1;

	if (D <= 0)
	{
		const scalar th = ::acos(Rl / sqrt(-Q3));
		const scalar qm = 2 * sqrt(-Q);
		const scalar r1 = qm * cos(th / 3.0) - a2 / 3.0;
		const scalar r2 =
			qm * cos((th + 2 * constant::mathematical::pi) / 3.0) - a2 / 3.0;
		const scalar r3 =
			qm * cos((th + 4 * constant::mathematical::pi) / 3.0) - a2 / 3.0;

		root = max(r1, max(r2, r3));
	}
	else
	{
		// One root is real
		const scalar D05 = sqrt(D);
		const scalar S = pow(Rl + D05, 1.0 / 3.0);
		scalar Tl = 0;
		if (D05 > Rl)
		{
			Tl = -pow(mag(Rl - D05), 1.0 / 3.0);
		}
		else
		{
			Tl = pow(Rl - D05, 1.0 / 3.0);
		}

		root = S + Tl - a2 / 3.0;
	}

	return root;
}


template<class Specie>
inline tnbLib::scalar tnbLib::PengRobinsonGas<Specie>::CpMCv
(
	scalar p,
	scalar T
) const
{
	const scalar Tr = T / Tc_;
	const scalar a = 0.45724*sqr(constant::thermodynamic::RR*Tc_) / Pc_;
	const scalar b = 0.07780*constant::thermodynamic::RR*Tc_ / Pc_;
	const scalar kappa = 0.37464 + 1.54226*omega_ - 0.26992*sqr(omega_);
	const scalar alpha = sqr(1 + kappa * (1 - sqrt(Tr)));

	const scalar A = alpha * a*p / sqr(constant::thermodynamic::RR*T);
	const scalar B = b * p / (constant::thermodynamic::RR*T);

	const scalar Z = this->Z(p, T);

	const scalar ap = kappa * a*(kappa / Tc_ - (1 + kappa) / sqrt(T*Tc_));
	const scalar M = (sqr(Z) + 2 * B*Z - sqr(B)) / (Z - B);
	const scalar N = ap * B / (b*constant::thermodynamic::RR);

	return this->R()*sqr(M - N) / (sqr(M) - 2 * A*(Z + B));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void tnbLib::PengRobinsonGas<Specie>::operator+=
(
	const PengRobinsonGas<Specie>& pg
	)
{
	scalar Y1 = this->Y();
	Specie::operator+=(pg);

	if (mag(this->Y()) > small)
	{
		Y1 /= this->Y();
		const scalar Y2 = pg.Y() / this->Y();

		Tc_ = Y1 * Tc_ + Y2 * pg.Tc_;
		Vc_ = Y1 * Vc_ + Y2 * pg.Vc_;
		Zc_ = Y1 * Zc_ + Y2 * pg.Zc_;
		Pc_ = constant::thermodynamic::RR * Zc_*Tc_ / Vc_;
		omega_ = Y1 * omega_ + Y2 * pg.omega_;
	}
}


template<class Specie>
inline void tnbLib::PengRobinsonGas<Specie>::operator*=(const scalar s)
{
	Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


template<class Specie>
tnbLib::PengRobinsonGas<Specie> tnbLib::operator+
(
	const PengRobinsonGas<Specie>& pg1,
	const PengRobinsonGas<Specie>& pg2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pg1)
		+ static_cast<const Specie&>(pg2)
	);

	if (mag(sp.Y()) < small)
	{
		return PengRobinsonGas<Specie>
			(
				sp,
				pg1.Tc_,
				pg1.Vc_,
				pg1.Zc_,
				pg1.Pc_,
				pg1.omega_
				);
	}
	else
	{
		const scalar Y1 = pg1.Y() / sp.Y();
		const scalar Y2 = pg2.Y() / sp.Y();

		const scalar Tc = Y1 * pg1.Tc_ + Y2 * pg2.Tc_;
		const scalar Vc = Y1 * pg1.Vc_ + Y2 * pg2.Vc_;
		const scalar Zc = Y1 * pg1.Zc_ + Y2 * pg2.Zc_;

		return PengRobinsonGas<Specie>
			(
				sp,
				Tc,
				Vc,
				Zc,
				constant::thermodynamic::RR*Zc*Tc / Vc,
				Y1*pg1.omega_ + Y2 * pg2.omega_
				);
	}
}


template<class Specie>
tnbLib::PengRobinsonGas<Specie> tnbLib::operator*
(
	const scalar s,
	const PengRobinsonGas<Specie>& pg
	)
{
	return PengRobinsonGas<Specie>
		(
			s*static_cast<const Specie&>(pg),
			pg.Tc_,
			pg.Vc_,
			pg.Zc_,
			pg.Pc_,
			pg.omega_
			);
}


template<class Specie>
tnbLib::PengRobinsonGas<Specie> tnbLib::operator==
(
	const PengRobinsonGas<Specie>& pg1,
	const PengRobinsonGas<Specie>& pg2
	)
{
	Specie sp
	(
		static_cast<const Specie&>(pg1)
		== static_cast<const Specie&>(pg2)
	);

	const scalar Y1 = pg1.Y() / sp.Y();
	const scalar Y2 = pg2.Y() / sp.Y();

	const scalar Tc = Y2 * pg2.Tc_ - Y1 * pg1.Tc_;
	const scalar Vc = Y2 * pg2.Vc_ - Y1 * pg1.Vc_;
	const scalar Zc = Y2 * pg2.Zc_ - Y1 * pg1.Zc_;

	return PengRobinsonGas<Specie>
		(
			sp,
			Tc,
			Vc,
			Zc,
			constant::thermodynamic::RR*Zc*Tc / Vc,
			Y2*pg2.omega_ - Y1 * pg1.omega_
			);
}


// ************************************************************************* //

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir
#include <thermodynamicConstants.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::PengRobinsonGas<Specie>::PengRobinsonGas
(
	const dictionary& dict
)
	:
	Specie(dict),
	Tc_(readScalar(dict.subDict("equationOfState").lookup("Tc"))),
	Vc_(readScalar(dict.subDict("equationOfState").lookup("Vc"))),
	Zc_(1.0),
	Pc_(readScalar(dict.subDict("equationOfState").lookup("Pc"))),
	omega_(readScalar(dict.subDict("equationOfState").lookup("omega")))
{
	Zc_ = Pc_ * Vc_ / (constant::thermodynamic::RR * Tc_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


template<class Specie>
void tnbLib::PengRobinsonGas<Specie>::write(Ostream& os) const
{
	Specie::write(os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const PengRobinsonGas<Specie>& pg
	)
{
	pg.write(os);
	return os;
}


// ************************************************************************* //