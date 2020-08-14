#include <convectiveHeatTransferFvPatchScalarField.hxx>

#include <turbulentFluidThermoModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <compressibleTurbulenceModel.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		convectiveHeatTransferFvPatchScalarField::
			convectiveHeatTransferFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			fixedValueFvPatchScalarField(p, iF),
			L_(1.0)
		{}


		convectiveHeatTransferFvPatchScalarField::
			convectiveHeatTransferFvPatchScalarField
			(
				const convectiveHeatTransferFvPatchScalarField& ptf,
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const fvPatchFieldMapper& mapper
			)
			:
			fixedValueFvPatchScalarField(ptf, p, iF, mapper),
			L_(ptf.L_)
		{}


		convectiveHeatTransferFvPatchScalarField::
			convectiveHeatTransferFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const dictionary& dict
			)
			:
			fixedValueFvPatchScalarField(p, iF, dict),
			L_(readScalar(dict.lookup("L")))
		{}


		convectiveHeatTransferFvPatchScalarField::
			convectiveHeatTransferFvPatchScalarField
			(
				const convectiveHeatTransferFvPatchScalarField& htcpsf
			)
			:
			fixedValueFvPatchScalarField(htcpsf),
			L_(htcpsf.L_)
		{}


		convectiveHeatTransferFvPatchScalarField::
			convectiveHeatTransferFvPatchScalarField
			(
				const convectiveHeatTransferFvPatchScalarField& htcpsf,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			fixedValueFvPatchScalarField(htcpsf, iF),
			L_(htcpsf.L_)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void convectiveHeatTransferFvPatchScalarField::updateCoeffs()
		{
			if (updated())
			{
				return;
			}

			const label patchi = patch().index();

			const compressible::turbulenceModel& turbModel =
				db().lookupObject<compressible::turbulenceModel>
				(
					IOobject::groupName
					(
						compressible::turbulenceModel::propertiesName,
						internalField().group()
					)
					);

			const scalarField alphaEffw(turbModel.alphaEff(patchi));

			const tmp<scalarField> tmuw = turbModel.mu(patchi);
			const scalarField& muw = tmuw();

			const scalarField& rhow = turbModel.rho().boundaryField()[patchi];
			const vectorField& Uc = turbModel.U();
			const vectorField& Uw = turbModel.U().boundaryField()[patchi];
			const scalarField& Tw = turbModel.transport().T().boundaryField()[patchi];
			const scalarField& pw = turbModel.transport().p().boundaryField()[patchi];
			const scalarField Cpw(turbModel.transport().Cp(pw, Tw, patchi));

			const scalarField kappaw(Cpw*alphaEffw);
			const scalarField Pr(muw*Cpw / kappaw);

			scalarField& htc = *this;
			forAll(htc, facei)
			{
				label celli = patch().faceCells()[facei];

				scalar Re = rhow[facei] * mag(Uc[celli] - Uw[facei])*L_ / muw[facei];

				if (Re < 5.0E+05)
				{
					htc[facei] = 0.664*sqrt(Re)*cbrt(Pr[facei])*kappaw[facei] / L_;
				}
				else
				{
					htc[facei] = 0.037*pow(Re, 0.8)*cbrt(Pr[facei])*kappaw[facei] / L_;
				}
			}

			fixedValueFvPatchScalarField::updateCoeffs();
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		void convectiveHeatTransferFvPatchScalarField::write(Ostream& os) const
		{
			fvPatchField<scalar>::write(os);
			writeEntry(os, "L", L_);
			writeEntry(os, "value", *this);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makePatchTypeField
		(
			fvPatchScalarField,
			convectiveHeatTransferFvPatchScalarField
		);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib

// ************************************************************************* //