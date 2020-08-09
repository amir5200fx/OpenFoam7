#include <nutUTabulatedWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	tmp<scalarField> nutUTabulatedWallFunctionFvPatchScalarField::nut() const
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
		const fvPatchVectorField& Uw = turbModel.U().boundaryField()[patchi];
		const scalarField magUp(mag(Uw.patchInternalField() - Uw));
		const scalarField magGradU(mag(Uw.snGrad()));
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();

		return
			max
			(
				scalar(0),
				sqr(magUp / (calcUPlus(magUp*y / nuw) + rootVSmall))
				/ (magGradU + rootVSmall)
				- nuw
			);
	}


	tmp<scalarField> nutUTabulatedWallFunctionFvPatchScalarField::calcUPlus
	(
		const scalarField& Rey
	) const
	{
		tmp<scalarField> tuPlus(new scalarField(patch().size(), 0.0));
		scalarField& uPlus = tuPlus.ref();

		forAll(uPlus, facei)
		{
			uPlus[facei] = uPlusTable_.interpolateLog10(Rey[facei]);
		}

		return tuPlus;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	nutUTabulatedWallFunctionFvPatchScalarField::
		nutUTabulatedWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutWallFunctionFvPatchScalarField(p, iF),
		uPlusTableName_("undefined-uPlusTableName"),
		uPlusTable_
		(
			IOobject
			(
				uPlusTableName_,
				patch().boundaryMesh().mesh().time().constant(),
				patch().boundaryMesh().mesh(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			false
		)
	{}


	nutUTabulatedWallFunctionFvPatchScalarField::
		nutUTabulatedWallFunctionFvPatchScalarField
		(
			const nutUTabulatedWallFunctionFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		nutWallFunctionFvPatchScalarField(ptf, p, iF, mapper),
		uPlusTableName_(ptf.uPlusTableName_),
		uPlusTable_(ptf.uPlusTable_)
	{}


	nutUTabulatedWallFunctionFvPatchScalarField::
		nutUTabulatedWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		nutWallFunctionFvPatchScalarField(p, iF, dict),
		uPlusTableName_(dict.lookup("uPlusTable")),
		uPlusTable_
		(
			IOobject
			(
				uPlusTableName_,
				patch().boundaryMesh().mesh().time().constant(),
				patch().boundaryMesh().mesh(),
				IOobject::MUST_READ_IF_MODIFIED,
				IOobject::NO_WRITE,
				false
			),
			true
		)
	{}


	nutUTabulatedWallFunctionFvPatchScalarField::
		nutUTabulatedWallFunctionFvPatchScalarField
		(
			const nutUTabulatedWallFunctionFvPatchScalarField& wfpsf
		)
		:
		nutWallFunctionFvPatchScalarField(wfpsf),
		uPlusTableName_(wfpsf.uPlusTableName_),
		uPlusTable_(wfpsf.uPlusTable_)
	{}


	nutUTabulatedWallFunctionFvPatchScalarField::
		nutUTabulatedWallFunctionFvPatchScalarField
		(
			const nutUTabulatedWallFunctionFvPatchScalarField& wfpsf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutWallFunctionFvPatchScalarField(wfpsf, iF),
		uPlusTableName_(wfpsf.uPlusTableName_),
		uPlusTable_(wfpsf.uPlusTable_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	tmp<scalarField> nutUTabulatedWallFunctionFvPatchScalarField::yPlus() const
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
		const fvPatchVectorField& Uw = turbModel.U().boundaryField()[patchi];
		const scalarField magUp(mag(Uw.patchInternalField() - Uw));
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();
		const scalarField Rey(magUp*y / nuw);

		return Rey / (calcUPlus(Rey) + rootVSmall);
	}


	void nutUTabulatedWallFunctionFvPatchScalarField::write(Ostream& os) const
	{
		fvPatchField<scalar>::write(os);
		writeEntry(os, "uPlusTable", uPlusTableName_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		nutUTabulatedWallFunctionFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //