#include <pressure.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(pressure, 0);
		addToRunTimeSelectionTable(functionObject, pressure, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::word tnbLib::functionObjects::pressure::resultName() const
{
	word rName;

	if (calcTotal_)
	{
		rName = "total(" + fieldName_ + ")";
	}
	else
	{
		rName = "static(" + fieldName_ + ")";
	}

	if (calcCoeff_)
	{
		rName += "_coeff";
	}

	return rName;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::pressure::rhoScale
(
	const volScalarField& p
) const
{
	if (p.dimensions() == dimPressure)
	{
		return p;
	}
	else
	{
		return dimensionedScalar("rhoInf", dimDensity, rhoInf_)*p;
	}
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::pressure::rhoScale
(
	const volScalarField& p,
	const tmp<volScalarField>& tsf
) const
{
	if (p.dimensions() == dimPressure)
	{
		return lookupObject<volScalarField>(rhoName_)*tsf;
	}
	else
	{
		return dimensionedScalar("rhoInf", dimDensity, rhoInf_)*tsf;
	}
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::pressure::pRef
(
	const tmp<volScalarField>& tp
) const
{
	if (calcTotal_)
	{
		return tp + dimensionedScalar("pRef", dimPressure, pRef_);
	}
	else
	{
		return move(tp);
	}
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::pressure::pDyn
(
	const volScalarField& p,
	const tmp<volScalarField>& tp
) const
{
	if (calcTotal_)
	{
		return
			tp
			+ rhoScale(p, 0.5*magSqr(lookupObject<volVectorField>(UName_)));
	}
	else
	{
		return move(tp);
	}
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::functionObjects::pressure::coeff
(
	const tmp<volScalarField>& tp
) const
{
	if (calcCoeff_)
	{
		tmp<volScalarField> tpCoeff(tp.ptr());
		volScalarField& pCoeff = tpCoeff.ref();

		pCoeff -= dimensionedScalar("pInf", dimPressure, pInf_);

		const dimensionedScalar pSmall("pSmall", dimPressure, small);
		const dimensionedVector U("U", dimVelocity, UInf_);
		const dimensionedScalar rho("rho", dimDensity, rhoInf_);

		pCoeff /= 0.5*rho*magSqr(U) + pSmall;

		return tpCoeff;
	}
	else
	{
		return move(tp);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::pressure::calc()
{
	if (foundObject<volScalarField>(fieldName_))
	{
		const volScalarField& p = lookupObject<volScalarField>(fieldName_);

		return store
		(
			resultName_,
			coeff(pRef(pDyn(p, rhoScale(p))))
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::pressure::pressure
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "p"),
	UName_("U"),
	rhoName_("rho"),
	calcTotal_(false),
	pRef_(0),
	calcCoeff_(false),
	pInf_(0),
	UInf_(Zero),
	rhoInf_(1)
{
	read(dict);

	dimensionSet pDims(dimPressure);

	if (calcCoeff_)
	{
		pDims /= dimPressure;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::pressure::~pressure()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::pressure::read(const dictionary& dict)
{
	dict.readIfPresent("U", UName_);
	dict.readIfPresent("rho", rhoName_);

	if (rhoName_ == "rhoInf")
	{
		dict.lookup("rhoInf") >> rhoInf_;
	}

	dict.lookup("calcTotal") >> calcTotal_;
	if (calcTotal_)
	{
		dict.lookup("pRef") >> pRef_;
	}

	dict.lookup("calcCoeff") >> calcCoeff_;
	if (calcCoeff_)
	{
		dict.lookup("pInf") >> pInf_;
		dict.lookup("UInf") >> UInf_;
		dict.lookup("rhoInf") >> rhoInf_;

		scalar zeroCheck = 0.5*rhoInf_*magSqr(UInf_) + pInf_;

		if (mag(zeroCheck) < rootVSmall)
		{
			WarningInFunction
				<< type() << " " << name() << ": "
				<< "Coefficient calculation requested, but reference "
				<< "pressure level is zero.  Please check the supplied "
				<< "values of pInf, UInf and rhoInf" << endl;
		}
	}

	resultName_ = dict.lookupOrDefault<word>("result", resultName());

	return true;
}


// ************************************************************************* //