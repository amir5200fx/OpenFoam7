#include <strainRateFunction.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{
		namespace generalizedNewtonianViscosityModels
		{
			defineTypeNameAndDebug(strainRateFunction, 0);

			addToRunTimeSelectionTable
			(
				generalizedNewtonianViscosityModel,
				strainRateFunction,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarModels::generalizedNewtonianViscosityModels::strainRateFunction::
strainRateFunction
(
	const dictionary& viscosityProperties
)
	:
	generalizedNewtonianViscosityModel(viscosityProperties),
	strainRateFunction_
	(
		Function1<scalar>::New
		(
			"function",
			viscosityProperties.optionalSubDict(typeName + "Coeffs")
		)
	)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::laminarModels::generalizedNewtonianViscosityModels::
strainRateFunction::read
(
	const dictionary& viscosityProperties
)
{
	generalizedNewtonianViscosityModel::read(viscosityProperties);

	strainRateFunction_.clear();
	strainRateFunction_ = Function1<scalar>::New
	(
		"function",
		viscosityProperties.optionalSubDict
		(
			typeName + "Coeffs"
		)
	);

	return true;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModels::generalizedNewtonianViscosityModels::strainRateFunction::
nu
(
	const volScalarField& nu0,
	const volScalarField& strainRate
) const
{
	tmp<volScalarField> tnu
	(
		volScalarField::New
		(
			IOobject::groupName(type() + ":nu", nu0.group()),
			nu0.mesh(),
			dimensionedScalar(dimViscosity, 0)
		)
	);

	tnu.ref().primitiveFieldRef() = strainRateFunction_->value(strainRate);

	volScalarField::Boundary& nuBf = tnu.ref().boundaryFieldRef();
	const volScalarField::Boundary& sigmaBf = strainRate.boundaryField();

	forAll(nuBf, patchi)
	{
		nuBf[patchi] = strainRateFunction_->value(sigmaBf[patchi]);
	}

	return tnu;
}


// ************************************************************************* //