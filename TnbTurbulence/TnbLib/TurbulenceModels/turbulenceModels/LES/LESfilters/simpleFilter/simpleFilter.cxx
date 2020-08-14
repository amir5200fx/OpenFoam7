#include <simpleFilter.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvc.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(simpleFilter, 0);
	addToRunTimeSelectionTable(LESfilter, simpleFilter, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::simpleFilter::simpleFilter
(
	const fvMesh& mesh
)
	:
	LESfilter(mesh)
{}


tnbLib::simpleFilter::simpleFilter(const fvMesh& mesh, const dictionary&)
	:
	LESfilter(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::simpleFilter::read(const dictionary&)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::simpleFilter::operator()
(
	const tmp<volScalarField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volScalarField> filteredField = fvc::surfaceSum
	(
		mesh().magSf()*fvc::interpolate(unFilteredField)
	) / fvc::surfaceSum(mesh().magSf());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::simpleFilter::operator()
(
	const tmp<volVectorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volVectorField> filteredField = fvc::surfaceSum
	(
		mesh().magSf()*fvc::interpolate(unFilteredField)
	) / fvc::surfaceSum(mesh().magSf());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volSymmTensorField> tnbLib::simpleFilter::operator()
(
	const tmp<volSymmTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volSymmTensorField> filteredField = fvc::surfaceSum
	(
		mesh().magSf()*fvc::interpolate(unFilteredField)
	) / fvc::surfaceSum(mesh().magSf());

	unFilteredField.clear();

	return filteredField;
}


tnbLib::tmp<tnbLib::volTensorField> tnbLib::simpleFilter::operator()
(
	const tmp<volTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volTensorField> filteredField = fvc::surfaceSum
	(
		mesh().magSf()*fvc::interpolate(unFilteredField)
	) / fvc::surfaceSum(mesh().magSf());

	unFilteredField.clear();

	return filteredField;
}


// ************************************************************************* //