#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	dimensionedScalar operator+(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 + dimensionedScalar(s2);
	}


	dimensionedScalar operator+(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) + ds2;
	}


	dimensionedScalar operator-(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 - dimensionedScalar(s2);
	}


	dimensionedScalar operator-(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) - ds2;
	}


	dimensionedScalar operator*(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 * dimensionedScalar(s2);
	}


	dimensionedScalar operator/(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) / ds2;
	}



	dimensionedScalar pow
	(
		const dimensionedScalar& ds,
		const dimensionedScalar& expt
	)
	{
		return dimensionedScalar
		(
			"pow(" + ds.name() + ',' + expt.name() + ')',
			pow(ds.dimensions(), expt),
			::pow(ds.value(), expt.value())
		);
	}


	dimensionedScalar pow3(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow3(" + ds.name() + ')',
			pow3(ds.dimensions()),
			pow3(ds.value())
		);
	}


	dimensionedScalar pow4(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow4(" + ds.name() + ')',
			pow4(ds.dimensions()),
			pow4(ds.value())
		);
	}


	dimensionedScalar pow5(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow5(" + ds.name() + ')',
			pow5(ds.dimensions()),
			pow5(ds.value())
		);
	}


	dimensionedScalar pow6(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow6(" + ds.name() + ')',
			pow6(ds.dimensions()),
			pow6(ds.value())
		);
	}


	dimensionedScalar pow025(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow025(" + ds.name() + ')',
			pow025(ds.dimensions()),
			pow025(ds.value())
		);
	}


	dimensionedScalar sqrt(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"sqrt(" + ds.name() + ')',
			pow(ds.dimensions(), dimensionedScalar("0.5", dimless, 0.5)),
			::sqrt(ds.value())
		);
	}


	dimensionedScalar cbrt(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"cbrt(" + ds.name() + ')',
			pow(ds.dimensions(), dimensionedScalar("(1|3)", dimless, 1.0 / 3.0)),
			::cbrt(ds.value())
		);
	}


	dimensionedScalar hypot
	(
		const dimensionedScalar& x,
		const dimensionedScalar& y
	)
	{
		return dimensionedScalar
		(
			"hypot(" + x.name() + ',' + y.name() + ')',
			x.dimensions() + y.dimensions(),
			::hypot(x.value(), y.value())
		);
	}


	dimensionedScalar sign(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"sign(" + ds.name() + ')',
			sign(ds.dimensions()),
			::tnbLib::sign(ds.value())
		);
	}


	dimensionedScalar pos(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pos(" + ds.name() + ')',
			pos(ds.dimensions()),
			::tnbLib::pos(ds.value())
		);
	}


	dimensionedScalar pos0(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pos0(" + ds.name() + ')',
			pos0(ds.dimensions()),
			::tnbLib::pos0(ds.value())
		);
	}


	dimensionedScalar neg(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"neg(" + ds.name() + ')',
			neg(ds.dimensions()),
			::tnbLib::neg(ds.value())
		);
	}


	dimensionedScalar neg0(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"neg0(" + ds.name() + ')',
			neg0(ds.dimensions()),
			::tnbLib::neg0(ds.value())
		);
	}


	dimensionedScalar posPart(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"posPart(" + ds.name() + ')',
			posPart(ds.dimensions()),
			::tnbLib::pos0(ds.value())
		);
	}


	dimensionedScalar negPart(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"negPart(" + ds.name() + ')',
			negPart(ds.dimensions()),
			::tnbLib::neg(ds.value())
		);
	}


#define transFunc(func)                                                        \
dimensionedScalar func(const dimensionedScalar& ds)                            \
{                                                                              \
    if (!ds.dimensions().dimensionless())                                      \
    {                                                                          \
        FatalErrorInFunction                                                   \
            << "ds not dimensionless"                                          \
            << abort(FatalError);                                              \
    }                                                                          \
                                                                               \
    return dimensionedScalar                                                   \
    (                                                                          \
        #func "(" + ds.name() + ')',                                           \
        dimless,                                                               \
        ::func(ds.value())                                                     \
    );                                                                         \
}

	transFunc(exp)
		transFunc(log)
		transFunc(log10)
		transFunc(sin)
		transFunc(cos)
		transFunc(tan)
		transFunc(asin)
		transFunc(acos)
		transFunc(atan)
		transFunc(sinh)
		transFunc(cosh)
		transFunc(tanh)
		transFunc(asinh)
		transFunc(acosh)
		transFunc(atanh)
		transFunc(erf)
		transFunc(erfc)
		transFunc(lgamma)
		transFunc(j0)
		transFunc(j1)
		transFunc(y0)
		transFunc(y1)

#undef transFunc


#define transFunc(func)                                                        \
dimensionedScalar func(const int n, const dimensionedScalar& ds)               \
{                                                                              \
    if (!ds.dimensions().dimensionless())                                      \
    {                                                                          \
        FatalErrorInFunction                                                   \
            << "ds not dimensionless"                                          \
            << abort(FatalError);                                              \
    }                                                                          \
                                                                               \
    return dimensionedScalar                                                   \
    (                                                                          \
        #func "(" + name(n) + ',' + ds.name() + ')',                           \
        dimless,                                                               \
        ::func(n, ds.value())                                                  \
    );                                                                         \
}

		transFunc(jn)
		transFunc(yn)

#undef transFunc


		dimensionedScalar atan2
		(
			const dimensionedScalar& x,
			const dimensionedScalar& y
		)
	{
		return dimensionedScalar
		(
			"atan2(" + x.name() + ',' + y.name() + ')',
			atan2(x.dimensions(), y.dimensions()),
			::atan2(x.value(), y.value())
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //