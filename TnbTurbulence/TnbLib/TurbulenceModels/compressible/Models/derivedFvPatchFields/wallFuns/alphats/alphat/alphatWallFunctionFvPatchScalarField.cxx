#include <alphatWallFunctionFvPatchScalarField.hxx>

#include <compressibleTurbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		alphatWallFunctionFvPatchScalarField::alphatWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF
		)
			:
			fixedValueFvPatchScalarField(p, iF),
			Prt_(0.85)
		{}


		alphatWallFunctionFvPatchScalarField::alphatWallFunctionFvPatchScalarField
		(
			const alphatWallFunctionFvPatchScalarField& ptf,
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const fvPatchFieldMapper& mapper
		)
			:
			fixedValueFvPatchScalarField(ptf, p, iF, mapper),
			Prt_(ptf.Prt_)
		{}


		alphatWallFunctionFvPatchScalarField::alphatWallFunctionFvPatchScalarField
		(
			const fvPatch& p,
			const DimensionedField<scalar, volMesh>& iF,
			const dictionary& dict
		)
			:
			fixedValueFvPatchScalarField(p, iF, dict),
			Prt_(dict.lookupOrDefault<scalar>("Prt", 0.85))
		{}


		alphatWallFunctionFvPatchScalarField::alphatWallFunctionFvPatchScalarField
		(
			const alphatWallFunctionFvPatchScalarField& awfpsf
		)
			:
			fixedValueFvPatchScalarField(awfpsf),
			Prt_(awfpsf.Prt_)
		{}


		alphatWallFunctionFvPatchScalarField::alphatWallFunctionFvPatchScalarField
		(
			const alphatWallFunctionFvPatchScalarField& awfpsf,
			const DimensionedField<scalar, volMesh>& iF
		)
			:
			fixedValueFvPatchScalarField(awfpsf, iF),
			Prt_(awfpsf.Prt_)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void alphatWallFunctionFvPatchScalarField::updateCoeffs()
		{
			if (updated())
			{
				return;
			}

			const label patchi = patch().index();

			// Retrieve turbulence properties from model
			const compressibleTurbulenceModel& turbModel =
				db().lookupObject<compressibleTurbulenceModel>
				(
					IOobject::groupName
					(
						compressibleTurbulenceModel::propertiesName,
						internalField().group()
					)
					);

			const scalarField& rhow = turbModel.rho().boundaryField()[patchi];
			const tmp<scalarField> tnutw = turbModel.nut(patchi);

			operator==(rhow*tnutw / Prt_);

			fixedValueFvPatchScalarField::updateCoeffs();
		}


		void alphatWallFunctionFvPatchScalarField::write(Ostream& os) const
		{
			fvPatchField<scalar>::write(os);
			writeEntry(os, "Prt", Prt_);
			writeEntry(os, "value", *this);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makePatchTypeField
		(
			fvPatchScalarField,
			alphatWallFunctionFvPatchScalarField
		);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //