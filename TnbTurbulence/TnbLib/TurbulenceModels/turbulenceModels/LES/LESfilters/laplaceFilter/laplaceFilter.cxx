#include <laplaceFilter.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <calculatedFvPatchFields.hxx>
#include <fvm.hxx>
#include <fvc.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(laplaceFilter, 0);
	addToRunTimeSelectionTable(LESfilter, laplaceFilter, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laplaceFilter::laplaceFilter(const fvMesh& mesh, scalar widthCoeff)
	:
	LESfilter(mesh),
	widthCoeff_(widthCoeff),
	coeff_
	(
		IOobject
		(
			"laplaceFilterCoeff",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar(dimLength*dimLength, 0),
		calculatedFvPatchScalarField::typeName
	)
{
	coeff_.ref() = pow(mesh.V(), 2.0 / 3.0) / widthCoeff_;
}


tnbLib::laplaceFilter::laplaceFilter(const fvMesh& mesh, const dictionary& bd)
	:
	LESfilter(mesh),
	widthCoeff_
	(
		readScalar(bd.optionalSubDict(type() + "Coeffs").lookup("widthCoeff"))
	),
	coeff_
	(
		IOobject
		(
			"laplaceFilterCoeff",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar(dimLength*dimLength, 0),
		calculatedFvPatchScalarField::typeName
	)
{
	coeff_.ref() = pow(mesh.V(), 2.0 / 3.0) / widthCoeff_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::laplaceFilter::read(const dictionary& bd)
{
	bd.optionalSubDict(type() + "Coeffs").lookup("widthCoeff") >> widthCoeff_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::laplaceFilter::operator()
(
	const tmp<volScalarField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volScalarField> filteredField =
		unFilteredField() + fvc::laplacian(coeff_, unFilteredField());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::laplaceFilter::operator()
(
	const tmp<volVectorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volVectorField> filteredField =
		unFilteredField() + fvc::laplacian(coeff_, unFilteredField());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volSymmTensorField> tnbLib::laplaceFilter::operator()
(
	const tmp<volSymmTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volSymmTensorField> filteredField =
		unFilteredField() + fvc::laplacian(coeff_, unFilteredField());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volTensorField> tnbLib::laplaceFilter::operator()
(
	const tmp<volTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volTensorField> filteredField =
		unFilteredField() + fvc::laplacian(coeff_, unFilteredField());

	unFilteredField.clear();

	return filteredField;
}


// ************************************************************************* //