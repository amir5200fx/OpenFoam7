#include <TroeFallOffFunction.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::TroeFallOffFunction::TroeFallOffFunction
(
	const scalar alpha,
	const scalar Tsss,
	const scalar Ts,
	const scalar Tss
)
	:
	alpha_(alpha),
	Tsss_(Tsss),
	Ts_(Ts),
	Tss_(Tss)
{}


inline tnbLib::TroeFallOffFunction::TroeFallOffFunction(const dictionary& dict)
	:
	alpha_(readScalar(dict.lookup("alpha"))),
	Tsss_(readScalar(dict.lookup("Tsss"))),
	Ts_(readScalar(dict.lookup("Ts"))),
	Tss_(readScalar(dict.lookup("Tss")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::TroeFallOffFunction::operator()
(
	const scalar T,
	const scalar Pr
	) const
{
	scalar logFcent = log10
	(
		max
		(
		(1 - alpha_)*exp(-T / Tsss_) + alpha_ * exp(-T / Ts_) + exp(-Tss_ / T),
			small
		)
	);

	scalar c = -0.4 - 0.67*logFcent;
	static const scalar d = 0.14;
	scalar n = 0.75 - 1.27*logFcent;

	scalar logPr = log10(max(Pr, small));
	return pow(10, logFcent / (1 + sqr((logPr + c) / (n - d * (logPr + c)))));
}


inline tnbLib::scalar tnbLib::TroeFallOffFunction::ddT
(
	const scalar Pr,
	const scalar F,
	const scalar dPrdT,
	const scalar T
) const
{
	scalar logPr = log10(max(Pr, small));
	scalar logTen = log(10.0);
	scalar Fcent =
		(
			max
			(
			(1 - alpha_)*exp(-T / Tsss_) + alpha_ * exp(-T / Ts_) + exp(-Tss_ / T),
				small
			)
			);
	scalar logFcent = log10(Fcent);

	scalar dFcentdT =
		(
		(alpha_ - 1)*exp(-T / Tsss_) / Tsss_
			- alpha_ * exp(-T / Ts_) / Ts_
			+ Tss_ * exp(-Tss_ / T) / sqr(T)
			);

	scalar d = 0.14;
	scalar dlogFcentdT = dFcentdT / Fcent / logTen;
	scalar c = -0.4 - 0.67*logFcent;
	scalar dcdT = -0.67*dlogFcentdT;
	scalar n = 0.75 - 1.27*logFcent;
	scalar dndT = -1.27*dlogFcentdT;

	scalar dlogPrdT = dPrdT / Pr / logTen;

	scalar dParentdT =
		2.0*(logPr + c) / sqr(n - d * (logPr + c))
		*(
		(dlogPrdT + dcdT)
			- (logPr + c)*(dndT - d * (dlogPrdT + dcdT)) / (n - d * (logPr + c))
			);

	return
		(
			F*logTen
			*(
				dlogFcentdT / (1.0 + sqr((logPr + c) / (n - d * (logPr + c))))
				- logFcent * dParentdT / sqr(1.0 + sqr((logPr + c) / (n - d * (logPr + c))))
				)
			);
}


inline tnbLib::scalar tnbLib::TroeFallOffFunction::ddc
(
	const scalar Pr,
	const scalar F,
	const scalar dPrdc,
	const scalar T
) const
{
	scalar logPr = log10(max(Pr, small));
	scalar logTen = log(10.0);
	scalar logFcent = log10
	(
		max
		(
		(1 - alpha_)*exp(-T / Tsss_) + alpha_ * exp(-T / Ts_) + exp(-Tss_ / T),
			small
		)
	);

	scalar dlogPrdc = dPrdc / Pr / logTen;
	scalar d = 0.14;
	scalar c = -0.4 - 0.67*logFcent;
	scalar n = 0.75 - 1.27*logFcent;

	scalar dParentdc =
		2.0*(logPr + c) / sqr(n - d * (logPr + c))
		*(
		(dlogPrdc)
			-(logPr + c)*(-d * (dlogPrdc)) / (n - d * (logPr + c))
			);

	return
		(
			F*logTen
			*(
				-logFcent * dParentdc / sqr(1.0 + sqr((logPr + c) / (n - d * (logPr + c))))
				)
			);
}


inline void tnbLib::TroeFallOffFunction::write(Ostream& os) const
{
	writeEntry(os, "alpha", alpha_);
	writeEntry(os, "Tsss", Tsss_);
	writeEntry(os, "Ts", Ts_);
	writeEntry(os, "Tss", Tss_);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::TroeFallOffFunction& tfof
	)
{
	tfof.write(os);
	return os;
}


// ************************************************************************* //