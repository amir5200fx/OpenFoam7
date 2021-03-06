#include <nutkAtmRoughWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	tmp<scalarField> nutkAtmRoughWallFunctionFvPatchScalarField::nut() const
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

		tmp<scalarField> tnutw(new scalarField(*this));
		scalarField& nutw = tnutw.ref();

		forAll(nutw, facei)
		{
			label celli = patch().faceCells()[facei];

			scalar uStar = Cmu25 * sqrt(k[celli]);
			scalar yPlus = uStar * y[facei] / nuw[facei];

			scalar Edash = (y[facei] + z0_[facei]) / z0_[facei];

			nutw[facei] =
				nuw[facei] * (yPlus*kappa_ / log(max(Edash, 1 + 1e-4)) - 1);

			if (debug)
			{
				Info << "yPlus = " << yPlus
					<< ", Edash = " << Edash
					<< ", nutw = " << nutw[facei]
					<< endl;
			}
		}

		return tnutw;
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	nutkAtmRoughWallFunctionFvPatchScalarField::
		nutkAtmRoughWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutkWallFunctionFvPatchScalarField(p, iF),
		z0_(p.size(), 0.0)
	{}


	nutkAtmRoughWallFunctionFvPatchScalarField::
		nutkAtmRoughWallFunctionFvPatchScalarField
		(
			const nutkAtmRoughWallFunctionFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
		:
		nutkWallFunctionFvPatchScalarField(ptf, p, iF, mapper),
		z0_(mapper(ptf.z0_))
	{}


	nutkAtmRoughWallFunctionFvPatchScalarField::
		nutkAtmRoughWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
		:
		nutkWallFunctionFvPatchScalarField(p, iF, dict),
		z0_("z0", dict, p.size())
	{}


	nutkAtmRoughWallFunctionFvPatchScalarField::
		nutkAtmRoughWallFunctionFvPatchScalarField
		(
			const nutkAtmRoughWallFunctionFvPatchScalarField& rwfpsf
		)
		:
		nutkWallFunctionFvPatchScalarField(rwfpsf),
		z0_(rwfpsf.z0_)
	{}


	nutkAtmRoughWallFunctionFvPatchScalarField::
		nutkAtmRoughWallFunctionFvPatchScalarField
		(
			const nutkAtmRoughWallFunctionFvPatchScalarField& rwfpsf,
			const DimensionedField<scalar, volMesh>& iF
		)
		:
		nutkWallFunctionFvPatchScalarField(rwfpsf, iF),
		z0_(rwfpsf.z0_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void nutkAtmRoughWallFunctionFvPatchScalarField::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		nutkWallFunctionFvPatchScalarField::autoMap(m);
		m(z0_, z0_);
	}


	void nutkAtmRoughWallFunctionFvPatchScalarField::rmap
	(
		const fvPatchScalarField& ptf,
		const labelList& addr
	)
	{
		nutkWallFunctionFvPatchScalarField::rmap(ptf, addr);

		const nutkAtmRoughWallFunctionFvPatchScalarField& nrwfpsf =
			refCast<const nutkAtmRoughWallFunctionFvPatchScalarField>(ptf);

		z0_.rmap(nrwfpsf.z0_, addr);
	}


	void nutkAtmRoughWallFunctionFvPatchScalarField::write(Ostream& os) const
	{
		fvPatchField<scalar>::write(os);
		writeLocalEntries(os);
		writeEntry(os, "z0", z0_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePatchTypeField
	(
		fvPatchScalarField,
		nutkAtmRoughWallFunctionFvPatchScalarField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //