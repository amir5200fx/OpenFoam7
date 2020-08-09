#include <nutWallFunctionFvPatchScalarField.hxx>

#include <turbulenceModel.hxx>
#include <fvPatchFieldMapper.hxx>
#include <wallFvPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nutWallFunctionFvPatchScalarField, 0);
}

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::nutWallFunctionFvPatchScalarField::checkType()
{
	if (!isA<wallFvPatch>(patch()))
	{
		FatalErrorInFunction
			<< "Invalid wall function specification" << nl
			<< "    Patch type for patch " << patch().name()
			<< " must be wall" << nl
			<< "    Current patch type is " << patch().type() << nl << endl
			<< abort(FatalError);
	}
}


void tnbLib::nutWallFunctionFvPatchScalarField::writeLocalEntries
(
	Ostream& os
) const
{
	writeEntry(os, "Cmu", Cmu_);
	writeEntry(os, "kappa", kappa_);
	writeEntry(os, "E", E_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nutWallFunctionFvPatchScalarField::nutWallFunctionFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	Cmu_(0.09),
	kappa_(0.41),
	E_(9.8),
	yPlusLam_(yPlusLam(kappa_, E_))
{
	checkType();
}


tnbLib::nutWallFunctionFvPatchScalarField::nutWallFunctionFvPatchScalarField
(
	const nutWallFunctionFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	Cmu_(ptf.Cmu_),
	kappa_(ptf.kappa_),
	E_(ptf.E_),
	yPlusLam_(ptf.yPlusLam_)
{
	checkType();
}


tnbLib::nutWallFunctionFvPatchScalarField::nutWallFunctionFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict),
	Cmu_(dict.lookupOrDefault<scalar>("Cmu", 0.09)),
	kappa_(dict.lookupOrDefault<scalar>("kappa", 0.41)),
	E_(dict.lookupOrDefault<scalar>("E", 9.8)),
	yPlusLam_(yPlusLam(kappa_, E_))
{
	checkType();
}


tnbLib::nutWallFunctionFvPatchScalarField::nutWallFunctionFvPatchScalarField
(
	const nutWallFunctionFvPatchScalarField& wfpsf
)
	:
	fixedValueFvPatchScalarField(wfpsf),
	Cmu_(wfpsf.Cmu_),
	kappa_(wfpsf.kappa_),
	E_(wfpsf.E_),
	yPlusLam_(wfpsf.yPlusLam_)
{
	checkType();
}


tnbLib::nutWallFunctionFvPatchScalarField::nutWallFunctionFvPatchScalarField
(
	const nutWallFunctionFvPatchScalarField& wfpsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(wfpsf, iF),
	Cmu_(wfpsf.Cmu_),
	kappa_(wfpsf.kappa_),
	E_(wfpsf.E_),
	yPlusLam_(wfpsf.yPlusLam_)
{
	checkType();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::nutWallFunctionFvPatchScalarField&
tnbLib::nutWallFunctionFvPatchScalarField::nutw
(
	const turbulenceModel& turbModel,
	const label patchi
)
{
	return
		refCast<const nutWallFunctionFvPatchScalarField>
		(
			turbModel.nut()().boundaryField()[patchi]
			);
}


tnbLib::scalar tnbLib::nutWallFunctionFvPatchScalarField::yPlusLam
(
	const scalar kappa,
	const scalar E
)
{
	scalar ypl = 11.0;

	for (int i = 0; i < 10; i++)
	{
		ypl = log(max(E*ypl, 1)) / kappa;
	}

	return ypl;
}


tnbLib::scalar tnbLib::nutWallFunctionFvPatchScalarField::yPlusLam() const
{
	return yPlusLam_;
}


void tnbLib::nutWallFunctionFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	operator==(nut());

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::nutWallFunctionFvPatchScalarField::write(Ostream& os) const
{
	fvPatchField<scalar>::write(os);
	writeLocalEntries(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //