#include <nutUSpaldingWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	tmp<scalarField> nutUSpaldingWallFunctionFvPatchScalarField::nut() const
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
		const fvPatchVectorField& Uw = turbModel.U().boundaryField()[patchi];
		const scalarField magGradU(mag(Uw.snGrad()));
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();

		return max
		(
			scalar(0),
			sqr(calcUTau(magGradU)) / (magGradU + rootVSmall) - nuw
		);
	}


	tmp<scalarField> nutUSpaldingWallFunctionFvPatchScalarField::calcUTau
	(
		const scalarField& magGradU
	) const
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

		const scalarField& nutw = *this;

		tmp<scalarField> tuTau(new scalarField(patch().size(), 0.0));
		scalarField& uTau = tuTau.ref();

		forAll(uTau, facei)
		{
			scalar ut = sqrt((nutw[facei] + nuw[facei])*magGradU[facei]);

			if (ut > rootVSmall)
			{
				int iter = 0;
				scalar err = great;

				do
				{
					scalar kUu = min(kappa_*magUp[facei] / ut, 50);
					scalar fkUu = exp(kUu) - 1 - kUu * (1 + 0.5*kUu);

					scalar f =
						-ut * y[facei] / nuw[facei]
						+ magUp[facei] / ut
						+ 1 / E_ * (fkUu - 1.0 / 6.0*kUu*sqr(kUu));

					scalar df =
						y[facei] / nuw[facei]
						+ magUp[facei] / sqr(ut)
						+ 1 / E_ * kUu*fkUu / ut;

					scalar uTauNew = ut + f / df;
					err = mag((ut - uTauNew) / ut);
					ut = uTauNew;

				} while (ut > rootVSmall && err > 0.01 && ++iter < 10);

				uTau[facei] = max(0.0, ut);
			}
		}

		return tuTau;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	nutUSpaldingWallFunctionFvPatchScalarField::
		nutUSpaldingWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutWallFunctionFvPatchScalarField(p, iF)
	{}


	nutUSpaldingWallFunctionFvPatchScalarField::
		nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		nutWallFunctionFvPatchScalarField(ptf, p, iF, mapper)
	{}


	nutUSpaldingWallFunctionFvPatchScalarField::
		nutUSpaldingWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		nutWallFunctionFvPatchScalarField(p, iF, dict)
	{}


	nutUSpaldingWallFunctionFvPatchScalarField::
		nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField& wfpsf
		)
		:
		nutWallFunctionFvPatchScalarField(wfpsf)
	{}


	nutUSpaldingWallFunctionFvPatchScalarField::
		nutUSpaldingWallFunctionFvPatchScalarField
		(
			const nutUSpaldingWallFunctionFvPatchScalarField& wfpsf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutWallFunctionFvPatchScalarField(wfpsf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	tmp<scalarField> nutUSpaldingWallFunctionFvPatchScalarField::yPlus() const
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
		const tmp<scalarField> tnuw = turbModel.nu(patchi);
		const scalarField& nuw = tnuw();

		return y * calcUTau(mag(Uw.snGrad())) / nuw;
	}


	void nutUSpaldingWallFunctionFvPatchScalarField::write(Ostream& os) const
	{
		fvPatchField<scalar>::write(os);
		writeLocalEntries(os);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		nutUSpaldingWallFunctionFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //