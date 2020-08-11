#include <viscosityModelStrainRateFunction.hxx>

#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(strainRateFunction, 0);

		addToRunTimeSelectionTable
		(
			viscosityModel,
			strainRateFunction,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::strainRateFunction::strainRateFunction
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	strainRateFunctionCoeffs_
	(
		viscosityProperties.optionalSubDict(typeName + "Coeffs")
	),
	strainRateFunction_
	(
		Function1<scalar>::New("function", strainRateFunctionCoeffs_)
	),
	nu_
	(
		IOobject
		(
			name,
			U_.time().timeName(),
			U_.db(),
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		U_.mesh(),
		dimensionedScalar(name, dimViscosity, 0)
	)
{
	correct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::strainRateFunction::nu() const
{
	return nu_;
}


tnbLib::tmp<tnbLib::scalarField>
tnbLib::viscosityModels::strainRateFunction::nu(const label patchi) const
{
	return nu_.boundaryField()[patchi];
}


void tnbLib::viscosityModels::strainRateFunction::correct()
{
	tmp<volScalarField> tsigma = strainRate();
	const volScalarField& sigma = tsigma();

	nu_.primitiveFieldRef() = strainRateFunction_->value(sigma());

	volScalarField::Boundary& nuBf = nu_.boundaryFieldRef();
	const volScalarField::Boundary& sigmaBf = sigma.boundaryField();

	forAll(nuBf, patchi)
	{
		nuBf[patchi] = strainRateFunction_->value(sigmaBf[patchi]);
	}
}


bool tnbLib::viscosityModels::strainRateFunction::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	strainRateFunctionCoeffs_ = viscosityProperties.optionalSubDict
	(
		typeName + "Coeffs"
	);

	strainRateFunction_.clear();
	strainRateFunction_ = Function1<scalar>::New
	(
		"function",
		strainRateFunctionCoeffs_
	);

	return true;
}


// ************************************************************************* //