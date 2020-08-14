#include <anisotropicFilter.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <zeroGradientPointPatchFields.hxx>
#include <wallFvPatch.hxx>
#include <fvc.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(anisotropicFilter, 0);
	addToRunTimeSelectionTable(LESfilter, anisotropicFilter, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::anisotropicFilter::anisotropicFilter
(
	const fvMesh& mesh,
	scalar widthCoeff
)
	:
	LESfilter(mesh),
	widthCoeff_(widthCoeff),
	coeff_
	(
		IOobject
		(
			"anisotropicFilterCoeff",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedVector(dimLength*dimLength, Zero),
		calculatedFvPatchVectorField::typeName
	)
{
	for (direction d = 0; d < vector::nComponents; d++)
	{
		coeff_.primitiveFieldRef().replace
		(
			d,
			(1 / widthCoeff_)*
			sqr
			(
				2.0*mesh.V()
				/ fvc::surfaceSum(mag(mesh.Sf().component(d)))().primitiveField()
			)
		);
	}
}


tnbLib::anisotropicFilter::anisotropicFilter
(
	const fvMesh& mesh,
	const dictionary& bd
)
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
			"anisotropicFilterCoeff",
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedVector(dimLength*dimLength, Zero),
		calculatedFvPatchScalarField::typeName
	)
{
	for (direction d = 0; d < vector::nComponents; d++)
	{
		coeff_.primitiveFieldRef().replace
		(
			d,
			(1 / widthCoeff_)*
			sqr
			(
				2.0*mesh.V()
				/ fvc::surfaceSum(mag(mesh.Sf().component(d)))().primitiveField()
			)
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::anisotropicFilter::read(const dictionary& bd)
{
	bd.optionalSubDict(type() + "Coeffs").lookup("widthCoeff") >> widthCoeff_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::anisotropicFilter::operator()
(
	const tmp<volScalarField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volScalarField> tmpFilteredField =
		unFilteredField
		+ (
			coeff_
			& fvc::surfaceIntegrate
			(
				mesh().Sf()
				*fvc::snGrad(unFilteredField())
			)
			);

	unFilteredField.clear();

	return tmpFilteredField;
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::anisotropicFilter::operator()
(
	const tmp<volVectorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volVectorField> tmpFilteredField =
		unFilteredField
		+ (
			coeff_
			& fvc::surfaceIntegrate
			(
				mesh().Sf()
				*fvc::snGrad(unFilteredField())
			)
			);

	unFilteredField.clear();

	return tmpFilteredField;
}


tnbLib::tmp<tnbLib::volSymmTensorField> tnbLib::anisotropicFilter::operator()
(
	const tmp<volSymmTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volSymmTensorField> tmpFilteredField
	(
		volSymmTensorField::New
		(
			"anisotropicFilteredSymmTensorField",
			mesh(),
			unFilteredField().dimensions()
		)
	);

	for (direction d = 0; d < symmTensor::nComponents; d++)
	{
		tmpFilteredField.ref().replace
		(
			d, anisotropicFilter::operator()(unFilteredField().component(d))
		);
	}

	unFilteredField.clear();

	return tmpFilteredField;
}


tnbLib::tmp<tnbLib::volTensorField> tnbLib::anisotropicFilter::operator()
(
	const tmp<volTensorField>& unFilteredField
	) const
{
	correctBoundaryConditions(unFilteredField);

	tmp<volTensorField> tmpFilteredField
	(
		volTensorField::New
		(
			"anisotropicFilteredTensorField",
			mesh(),
			unFilteredField().dimensions()
		)
	);

	for (direction d = 0; d < tensor::nComponents; d++)
	{
		tmpFilteredField.ref().replace
		(
			d, anisotropicFilter::operator()(unFilteredField().component(d))
		);
	}

	unFilteredField.clear();

	return tmpFilteredField;
}


// ************************************************************************* //