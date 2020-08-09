#include <nutLowReWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	tmp<scalarField> nutLowReWallFunctionFvPatchScalarField::nut() const
	{
		return tmp<scalarField>(new scalarField(patch().size(), 0.0));
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	nutLowReWallFunctionFvPatchScalarField::nutLowReWallFunctionFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		nutWallFunctionFvPatchScalarField(p, iF)
	{}


	nutLowReWallFunctionFvPatchScalarField::nutLowReWallFunctionFvPatchScalarField
	(
		const nutLowReWallFunctionFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		nutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
	{}


	nutLowReWallFunctionFvPatchScalarField::nutLowReWallFunctionFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		nutWallFunctionFvPatchScalarField(p, iF, dict)
	{}


	nutLowReWallFunctionFvPatchScalarField::nutLowReWallFunctionFvPatchScalarField
	(
		const nutLowReWallFunctionFvPatchScalarField& nlrwfpsf
	)
		:
		nutWallFunctionFvPatchScalarField(nlrwfpsf)
	{}


	nutLowReWallFunctionFvPatchScalarField::nutLowReWallFunctionFvPatchScalarField
	(
		const nutLowReWallFunctionFvPatchScalarField& nlrwfpsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		nutWallFunctionFvPatchScalarField(nlrwfpsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	tmp<scalarField> nutLowReWallFunctionFvPatchScalarField::yPlus() const
	{
		const label patchi = patch().index();
		const turbulenceModel& turbModel = db().lookupObject<turbulenceModel>
			(
				IOobject::groupName
				(
					turbulenceModel::propertiesName,
					internalField().group()
				)
				);
		const scalarField& y = turbModel.y()[patchi];
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();
		const fvPatchVectorField& Uw = turbModel.U().boundaryField()[patchi];

		return y * sqrt(nuw*mag(Uw.snGrad())) / nuw;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		nutLowReWallFunctionFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //