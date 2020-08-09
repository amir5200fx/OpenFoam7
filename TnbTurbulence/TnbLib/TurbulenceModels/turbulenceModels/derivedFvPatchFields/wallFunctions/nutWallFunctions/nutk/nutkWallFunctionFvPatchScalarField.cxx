#include <nutkWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <wallFvPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	tmp<scalarField> nutkWallFunctionFvPatchScalarField::nut() const
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
		const tmp<volScalarField> tk = turbModel.k();
		const volScalarField& k = tk();
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();

		const scalar Cmu25 = pow025(Cmu_);

		tmp<scalarField> tnutw(new scalarField(patch().size(), 0.0));
		scalarField& nutw = tnutw.ref();

		forAll(nutw, facei)
		{
			label celli = patch().faceCells()[facei];

			scalar yPlus = Cmu25 * y[facei] * sqrt(k[celli]) / nuw[facei];

			if (yPlus > yPlusLam_)
			{
				nutw[facei] = nuw[facei] * (yPlus*kappa_ / log(E_*yPlus) - 1.0);
			}
		}

		return tnutw;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	nutkWallFunctionFvPatchScalarField::nutkWallFunctionFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		nutWallFunctionFvPatchScalarField(p, iF)
	{}


	nutkWallFunctionFvPatchScalarField::nutkWallFunctionFvPatchScalarField
	(
		const nutkWallFunctionFvPatchScalarField& ptf,
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		nutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
	{}


	nutkWallFunctionFvPatchScalarField::nutkWallFunctionFvPatchScalarField
	(
		const fvPatch& p,
		const DimensionedField<scalar, volMesh>& iF,
		const dictionary& dict
	)
		:
		nutWallFunctionFvPatchScalarField(p, iF, dict)
	{}


	nutkWallFunctionFvPatchScalarField::nutkWallFunctionFvPatchScalarField
	(
		const nutkWallFunctionFvPatchScalarField& wfpsf
	)
		:
		nutWallFunctionFvPatchScalarField(wfpsf)
	{}


	nutkWallFunctionFvPatchScalarField::nutkWallFunctionFvPatchScalarField
	(
		const nutkWallFunctionFvPatchScalarField& wfpsf,
		const DimensionedField<scalar, volMesh>& iF
	)
		:
		nutWallFunctionFvPatchScalarField(wfpsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	tmp<scalarField> nutkWallFunctionFvPatchScalarField::yPlus() const
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

		const tmp<volScalarField> tk = turbModel.k();
		const volScalarField& k = tk();
		tmp<scalarField> kwc = k.boundaryField()[patchi].patchInternalField();
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();

		return pow025(Cmu_)*y*sqrt(kwc) / nuw;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		nutkWallFunctionFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //