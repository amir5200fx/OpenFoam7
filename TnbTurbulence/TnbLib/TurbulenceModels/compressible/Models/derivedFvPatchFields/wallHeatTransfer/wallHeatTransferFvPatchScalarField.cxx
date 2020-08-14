#include <wallHeatTransferFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <turbulentFluidThermoModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	Tinf_(p.size(), 0.0),
	alphaWall_(p.size(), 0.0)
{
	refValue() = 0.0;
	refGrad() = 0.0;
	valueFraction() = 0.0;
}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	Tinf_(mapper(ptf.Tinf_)),
	alphaWall_(mapper(ptf.alphaWall_))
{}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	Tinf_("Tinf", dict, p.size()),
	alphaWall_("alphaWall", dict, p.size())
{
	refValue() = Tinf_;
	refGrad() = 0.0;
	valueFraction() = 0.0;

	if (dict.found("value"))
	{
		fvPatchField<scalar>::operator=
			(
				scalarField("value", dict, p.size())
				);
	}
	else
	{
		evaluate();
	}
}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& tppsf
)
	:
	mixedFvPatchScalarField(tppsf),
	Tinf_(tppsf.Tinf_),
	alphaWall_(tppsf.alphaWall_)
{}


tnbLib::wallHeatTransferFvPatchScalarField::wallHeatTransferFvPatchScalarField
(
	const wallHeatTransferFvPatchScalarField& tppsf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(tppsf, iF),
	Tinf_(tppsf.Tinf_),
	alphaWall_(tppsf.alphaWall_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::wallHeatTransferFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
	m(Tinf_, Tinf_);
	m(alphaWall_, alphaWall_);
}


void tnbLib::wallHeatTransferFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);

	const wallHeatTransferFvPatchScalarField& tiptf =
		refCast<const wallHeatTransferFvPatchScalarField>(ptf);

	Tinf_.rmap(tiptf.Tinf_, addr);
	alphaWall_.rmap(tiptf.alphaWall_, addr);
}


void tnbLib::wallHeatTransferFvPatchScalarField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const compressible::turbulenceModel& turbModel =
		db().lookupObject<compressible::turbulenceModel>
		(
			IOobject::groupName
			(
				turbulenceModel::propertiesName,
				internalField().group()
			)
			);

	const label patchi = patch().index();

	valueFraction() =
		1.0 /
		(
			1.0
			+ turbModel.kappaEff(patchi)*patch().deltaCoeffs() / alphaWall_
			);

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::wallHeatTransferFvPatchScalarField::write(Ostream& os) const
{
	fvPatchScalarField::write(os);
	writeEntry(os, "Tinf", Tinf_);
	writeEntry(os, "alphaWall", alphaWall_);
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		wallHeatTransferFvPatchScalarField
	);
}

// ************************************************************************* //