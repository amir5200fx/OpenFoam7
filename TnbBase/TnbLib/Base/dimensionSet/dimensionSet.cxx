#include <dimensionSet.hxx>

#include <dimensionedScalar.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dimensionSet, 1);
	const scalar dimensionSet::smallExponent = small;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dimensionSet::dimensionSet
(
	const scalar mass,
	const scalar length,
	const scalar time,
	const scalar temperature,
	const scalar moles,
	const scalar current,
	const scalar luminousIntensity
)
{
	exponents_[MASS] = mass;
	exponents_[LENGTH] = length;
	exponents_[TIME] = time;
	exponents_[TEMPERATURE] = temperature;
	exponents_[MOLES] = moles;
	exponents_[CURRENT] = current;
	exponents_[LUMINOUS_INTENSITY] = luminousIntensity;
}


tnbLib::dimensionSet::dimensionSet
(
	const scalar mass,
	const scalar length,
	const scalar time,
	const scalar temperature,
	const scalar moles
)
{
	exponents_[MASS] = mass;
	exponents_[LENGTH] = length;
	exponents_[TIME] = time;
	exponents_[TEMPERATURE] = temperature;
	exponents_[MOLES] = moles;
	exponents_[CURRENT] = 0;
	exponents_[LUMINOUS_INTENSITY] = 0;
}


tnbLib::dimensionSet::dimensionSet(const dimensionSet& ds)
{
	reset(ds);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dimensionSet::dimensionless() const
{
	for (int Dimension = 0; Dimension < nDimensions; ++Dimension)
	{
		// ie, mag(exponents_[Dimension]) > smallExponent
		if
			(
				exponents_[Dimension] > smallExponent
				|| exponents_[Dimension] < -smallExponent
				)
		{
			return false;
		}
	}

	return true;
}


void tnbLib::dimensionSet::reset(const dimensionSet& ds)
{
	for (int Dimension = 0; Dimension < nDimensions; ++Dimension)
	{
		exponents_[Dimension] = ds.exponents_[Dimension];
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::dimensionSet::operator[](const dimensionType type) const
{
	return exponents_[type];
}


tnbLib::scalar& tnbLib::dimensionSet::operator[](const dimensionType type)
{
	return exponents_[type];
}


tnbLib::scalar tnbLib::dimensionSet::operator[](const label type) const
{
	return exponents_[type];
}


tnbLib::scalar& tnbLib::dimensionSet::operator[](const label type)
{
	return exponents_[type];
}


bool tnbLib::dimensionSet::operator==(const dimensionSet& ds) const
{
	for (int Dimension = 0; Dimension < nDimensions; ++Dimension)
	{
		if
			(
				mag(exponents_[Dimension] - ds.exponents_[Dimension])
	> smallExponent
				)
		{
			return false;
		}
	}

	return true;
}


bool tnbLib::dimensionSet::operator!=(const dimensionSet& ds) const
{
	return !(operator==(ds));
}


bool tnbLib::dimensionSet::operator=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorInFunction
			<< "Different dimensions for =" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}


bool tnbLib::dimensionSet::operator+=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorInFunction
			<< "Different dimensions for +=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}


bool tnbLib::dimensionSet::operator-=(const dimensionSet& ds) const
{
	if (dimensionSet::debug && *this != ds)
	{
		FatalErrorInFunction
			<< "Different dimensions for -=" << endl
			<< "     dimensions : " << *this << " = " << ds << endl
			<< abort(FatalError);
	}

	return true;
}


bool tnbLib::dimensionSet::operator*=(const dimensionSet& ds)
{
	reset((*this)*ds);

	return true;
}


bool tnbLib::dimensionSet::operator/=(const dimensionSet& ds)
{
	reset((*this) / ds);

	return true;
}


// * * * * * * * * * * * * * * * Friend functions * * * * * * * * * * * * * * //

tnbLib::dimensionSet tnbLib::max(const dimensionSet& ds1, const dimensionSet& ds2)
{
	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorInFunction
			<< "Arguments of max have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}


tnbLib::dimensionSet tnbLib::min(const dimensionSet& ds1, const dimensionSet& ds2)
{
	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorInFunction
			<< "Arguments of min have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return ds1;
}


tnbLib::dimensionSet tnbLib::cmptMultiply
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
)
{
	return ds1 * ds2;
}


tnbLib::dimensionSet tnbLib::cmptDivide
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
)
{
	return ds1 / ds2;
}


tnbLib::dimensionSet tnbLib::pow(const dimensionSet& ds, const scalar p)
{
	dimensionSet dimPow
	(
		ds[dimensionSet::MASS] * p,
		ds[dimensionSet::LENGTH] * p,
		ds[dimensionSet::TIME] * p,
		ds[dimensionSet::TEMPERATURE] * p,
		ds[dimensionSet::MOLES] * p,
		ds[dimensionSet::CURRENT] * p,
		ds[dimensionSet::LUMINOUS_INTENSITY] * p
	);

	return dimPow;
}


tnbLib::dimensionSet tnbLib::pow
(
	const dimensionSet& ds,
	const dimensionedScalar& dS
)
{
	if (dimensionSet::debug && !dS.dimensions().dimensionless())
	{
		FatalErrorInFunction
			<< "Exponent of pow is not dimensionless"
			<< abort(FatalError);
	}

	dimensionSet dimPow
	(
		ds[dimensionSet::MASS] * dS.value(),
		ds[dimensionSet::LENGTH] * dS.value(),
		ds[dimensionSet::TIME] * dS.value(),
		ds[dimensionSet::TEMPERATURE] * dS.value(),
		ds[dimensionSet::MOLES] * dS.value(),
		ds[dimensionSet::CURRENT] * dS.value(),
		ds[dimensionSet::LUMINOUS_INTENSITY] * dS.value()
	);

	return dimPow;
}


tnbLib::dimensionSet tnbLib::pow
(
	const dimensionedScalar& dS,
	const dimensionSet& ds
)
{
	if
		(
			dimensionSet::debug
			&& !dS.dimensions().dimensionless()
			&& !ds.dimensionless()
			)
	{
		FatalErrorInFunction
			<< "Argument or exponent of pow not dimensionless" << endl
			<< abort(FatalError);
	}

	return ds;
}


tnbLib::dimensionSet tnbLib::sqr(const dimensionSet& ds)
{
	return pow(ds, 2);
}


tnbLib::dimensionSet tnbLib::pow3(const dimensionSet& ds)
{
	return pow(ds, 3);
}


tnbLib::dimensionSet tnbLib::pow4(const dimensionSet& ds)
{
	return pow(ds, 4);
}


tnbLib::dimensionSet tnbLib::pow5(const dimensionSet& ds)
{
	return pow(ds, 5);
}


tnbLib::dimensionSet tnbLib::pow6(const dimensionSet& ds)
{
	return pow(ds, 6);
}


tnbLib::dimensionSet tnbLib::pow025(const dimensionSet& ds)
{
	return sqrt(sqrt(ds));
}


tnbLib::dimensionSet tnbLib::sqrt(const dimensionSet& ds)
{
	return pow(ds, 0.5);
}


tnbLib::dimensionSet tnbLib::cbrt(const dimensionSet& ds)
{
	return pow(ds, 1.0 / 3.0);
}


tnbLib::dimensionSet tnbLib::magSqr(const dimensionSet& ds)
{
	return pow(ds, 2);
}


tnbLib::dimensionSet tnbLib::mag(const dimensionSet& ds)
{
	return ds;
}


tnbLib::dimensionSet tnbLib::sign(const dimensionSet&)
{
	return dimless;
}


tnbLib::dimensionSet tnbLib::pos(const dimensionSet&)
{
	return dimless;
}


tnbLib::dimensionSet tnbLib::pos0(const dimensionSet&)
{
	return dimless;
}


tnbLib::dimensionSet tnbLib::neg(const dimensionSet&)
{
	return dimless;
}


tnbLib::dimensionSet tnbLib::neg0(const dimensionSet&)
{
	return dimless;
}


tnbLib::dimensionSet tnbLib::posPart(const dimensionSet& ds)
{
	return ds;
}


tnbLib::dimensionSet tnbLib::negPart(const dimensionSet& ds)
{
	return ds;
}


tnbLib::dimensionSet tnbLib::inv(const dimensionSet& ds)
{
	return dimless / ds;
}


tnbLib::dimensionSet tnbLib::trans(const dimensionSet& ds)
{
	if (dimensionSet::debug && !ds.dimensionless())
	{
		FatalErrorInFunction
			<< "Argument of trancendental function not dimensionless"
			<< abort(FatalError);
	}

	return ds;
}


tnbLib::dimensionSet tnbLib::atan2(const dimensionSet& ds1, const dimensionSet& ds2)
{
	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorInFunction
			<< "Arguments of atan2 have different dimensions" << endl
			<< "     dimensions : " << ds1 << " and " << ds2 << endl
			<< abort(FatalError);
	}

	return dimless;
}


tnbLib::dimensionSet tnbLib::transform(const dimensionSet& ds)
{
	return ds;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::dimensionSet tnbLib::operator-(const dimensionSet& ds)
{
	return ds;
}


tnbLib::dimensionSet tnbLib::operator+
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimSum(ds1);

	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorInFunction
			<< "LHS and RHS of + have different dimensions" << endl
			<< "     dimensions : " << ds1 << " + " << ds2 << endl
			<< abort(FatalError);
	}

	return dimSum;
}


tnbLib::dimensionSet tnbLib::operator-
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimDifference(ds1);

	if (dimensionSet::debug && ds1 != ds2)
	{
		FatalErrorInFunction
			<< "LHS and RHS of - have different dimensions" << endl
			<< "     dimensions : " << ds1 << " - " << ds2 << endl
			<< abort(FatalError);
	}

	return dimDifference;
}


tnbLib::dimensionSet tnbLib::operator*
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimProduct(ds1);

	for (int Dimension = 0; Dimension < dimensionSet::nDimensions; Dimension++)
	{
		dimProduct.exponents_[Dimension] += ds2.exponents_[Dimension];
	}

	return dimProduct;
}


tnbLib::dimensionSet tnbLib::operator/
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	dimensionSet dimQuotient(ds1);

	for (int Dimension = 0; Dimension < dimensionSet::nDimensions; Dimension++)
	{
		dimQuotient.exponents_[Dimension] -= ds2.exponents_[Dimension];
	}

	return dimQuotient;
}


tnbLib::dimensionSet tnbLib::operator&
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}


tnbLib::dimensionSet tnbLib::operator^
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}


tnbLib::dimensionSet tnbLib::operator&&
(
	const dimensionSet& ds1,
	const dimensionSet& ds2
	)
{
	return ds1 * ds2;
}


// ************************************************************************* //