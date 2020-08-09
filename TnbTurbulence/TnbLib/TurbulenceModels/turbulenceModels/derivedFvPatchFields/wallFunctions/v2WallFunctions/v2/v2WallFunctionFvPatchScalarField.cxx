#include <v2WallFunctionFvPatchScalarField.hxx>

#include <nutWallFunctionFvPatchScalarField.hxx>
#include <turbulenceModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		v2WallFunctionFvPatchScalarField::v2WallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
			:
			fixedValueFvPatchField<scalar>(p, iF)
		{}


		v2WallFunctionFvPatchScalarField::v2WallFunctionFvPatchScalarField
		(
			const v2WallFunctionFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
			:
			fixedValueFvPatchField<scalar>(ptf, p, iF, mapper)
		{}


		v2WallFunctionFvPatchScalarField::v2WallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
			:
			fixedValueFvPatchField<scalar>(p, iF, dict)
		{}


		v2WallFunctionFvPatchScalarField::v2WallFunctionFvPatchScalarField
		(
			const v2WallFunctionFvPatchScalarField& v2wfpsf
		)
			:
			fixedValueFvPatchField<scalar>(v2wfpsf)
		{}


		v2WallFunctionFvPatchScalarField::v2WallFunctionFvPatchScalarField
		(
			const v2WallFunctionFvPatchScalarField& v2wfpsf,
			const DimensionedField<scalar, volMesh>& iF
		)
			:
			fixedValueFvPatchField<scalar>(v2wfpsf, iF)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void v2WallFunctionFvPatchScalarField::updateCoeffs()
		{
			if (updated())
			{
				return;
			}

			const label patchi = patch().index();

			const turbulenceModel& turbModel = db().lookupObject<turbulenceModel>
				(
					IOobject::groupName
					(
						turbulenceModel::propertiesName,
						internalField().group()
					)
					);

			const nutWallFunctionFvPatchScalarField& nutw =
				nutWallFunctionFvPatchScalarField::nutw(turbModel, patchi);

			const scalarField& y = turbModel.y()[patchi];

			const tmp<volScalarField> tk = turbModel.k();
			const volScalarField& k = tk();

			const tmp<scalarField> tnuw = turbModel.nu(patchi);
			const scalarField& nuw = tnuw();

			const scalar Cmu25 = pow025(nutw.Cmu());

			scalarField& v2 = *this;

			// Set v2 wall values
			forAll(v2, facei)
			{
				label celli = patch().faceCells()[facei];

				scalar uTau = Cmu25 * sqrt(k[celli]);

				scalar yPlus = uTau * y[facei] / nuw[facei];

				if (yPlus > nutw.yPlusLam())
				{
					scalar Cv2 = 0.193;
					scalar Bv2 = -0.94;
					v2[facei] = Cv2 / nutw.kappa()*log(yPlus) + Bv2;
				}
				else
				{
					scalar Cv2 = 0.193;
					v2[facei] = Cv2 * pow4(yPlus);
				}

				v2[facei] *= sqr(uTau);
			}

			fixedValueFvPatchField<scalar>::updateCoeffs();

			// TODO: perform averaging for cells sharing more than one boundary face
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makePatchTypeField
		(
			fvPatchScalarField,
			v2WallFunctionFvPatchScalarField
		);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// ************************************************************************* //