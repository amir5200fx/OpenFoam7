#include <greyDiffusiveViewFactorFixedValueFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::
greyDiffusiveViewFactorFixedValueFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(p, iF),
	radiationCoupledBase(patch(), "undefined", scalarField::null()),
	qro_(p.size(), 0.0)
{}


tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::
greyDiffusiveViewFactorFixedValueFvPatchScalarField
(
	const greyDiffusiveViewFactorFixedValueFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchScalarField(ptf, p, iF, mapper),
	radiationCoupledBase
	(
		patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_,
		mapper
	),
	qro_(mapper(ptf.qro_))
{}


tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::
greyDiffusiveViewFactorFixedValueFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchScalarField(p, iF, dict, false),
	radiationCoupledBase(p, dict),
	qro_("qro", dict, p.size())
{
	if (dict.found("value"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);

	}
	else
	{
		fvPatchScalarField::operator=(0.0);
	}
}


tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::
greyDiffusiveViewFactorFixedValueFvPatchScalarField
(
	const greyDiffusiveViewFactorFixedValueFvPatchScalarField& ptf
)
	:
	fixedValueFvPatchScalarField(ptf),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	qro_(ptf.qro_)
{}


tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::
greyDiffusiveViewFactorFixedValueFvPatchScalarField
(
	const greyDiffusiveViewFactorFixedValueFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	fixedValueFvPatchScalarField(ptf, iF),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	qro_(ptf.qro_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchScalarField::autoMap(m);
	radiationCoupledBase::autoMap(m);
	m(qro_, qro_);
}


void tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchScalarField::rmap(ptf, addr);
	radiationCoupledBase::rmap(ptf, addr);
	const greyDiffusiveViewFactorFixedValueFvPatchScalarField& mrptf =
		refCast<const greyDiffusiveViewFactorFixedValueFvPatchScalarField>(ptf);

	qro_.rmap(mrptf.qro_, addr);
}

void tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	if (debug)
	{
		scalar Q = gSum((*this)*patch().magSf());

		Info << patch().boundaryMesh().mesh().name() << ':'
			<< patch().name() << ':'
			<< this->internalField().name() << " <- "
			<< " heat transfer rate:" << Q
			<< " wall radiative heat flux "
			<< " min:" << gMin(*this)
			<< " max:" << gMax(*this)
			<< " avg:" << gAverage(*this)
			<< endl;
	}

	fixedValueFvPatchScalarField::updateCoeffs();
}


void tnbLib::greyDiffusiveViewFactorFixedValueFvPatchScalarField::write
(
	Ostream& os
) const
{
	fixedValueFvPatchScalarField::write(os);
	radiationCoupledBase::write(os);
	writeEntry(os, "qro", qro_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		greyDiffusiveViewFactorFixedValueFvPatchScalarField
	);
}


// ************************************************************************* //