#include <greyDiffusiveRadiationMixedFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>

#include <fvDOM.hxx>
#include <constants.hxx>

using namespace tnbLib::constant;
using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::
greyDiffusiveRadiationMixedFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(p, iF),
	radiationCoupledBase(p, "undefined", scalarField::null()),
	TName_("T")
{
	refValue() = 0.0;
	refGrad() = 0.0;
	valueFraction() = 1.0;
}


tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::
greyDiffusiveRadiationMixedFvPatchScalarField
(
	const greyDiffusiveRadiationMixedFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchScalarField(ptf, p, iF, mapper),
	radiationCoupledBase
	(
		p,
		ptf.emissivityMethod(),
		ptf.emissivity_,
		mapper
	),
	TName_(ptf.TName_)
{}


tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::
greyDiffusiveRadiationMixedFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchScalarField(p, iF),
	radiationCoupledBase(p, dict),
	TName_(dict.lookupOrDefault<word>("T", "T"))
{
	if (dict.found("refValue"))
	{
		fvPatchScalarField::operator=
			(
				scalarField("value", dict, p.size())
				);
		refValue() = scalarField("refValue", dict, p.size());
		refGrad() = scalarField("refGradient", dict, p.size());
		valueFraction() = scalarField("valueFraction", dict, p.size());
	}
	else
	{
		refValue() = 0.0;
		refGrad() = 0.0;
		valueFraction() = 1.0;

		fvPatchScalarField::operator=(refValue());
	}
}


tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::
greyDiffusiveRadiationMixedFvPatchScalarField
(
	const greyDiffusiveRadiationMixedFvPatchScalarField& ptf
)
	:
	mixedFvPatchScalarField(ptf),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	TName_(ptf.TName_)
{}


tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::
greyDiffusiveRadiationMixedFvPatchScalarField
(
	const greyDiffusiveRadiationMixedFvPatchScalarField& ptf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	mixedFvPatchScalarField(ptf, iF),
	radiationCoupledBase
	(
		ptf.patch(),
		ptf.emissivityMethod(),
		ptf.emissivity_
	),
	TName_(ptf.TName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	mixedFvPatchScalarField::autoMap(m);
	radiationCoupledBase::autoMap(m);
}


void tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);
	radiationCoupledBase::rmap(ptf, addr);
}


void tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	const scalarField& Tp =
		patch().lookupPatchField<volScalarField, scalar>(TName_);

	const radiationModels::fvDOM& dom =
		db().lookupObject<radiationModels::fvDOM>("radiationProperties");

	label rayId = -1;
	label lambdaId = -1;
	dom.setRayIdLambdaId(internalField().name(), rayId, lambdaId);

	const label patchi = patch().index();

	if (dom.nLambda() != 1)
	{
		FatalErrorInFunction
			<< " a grey boundary condition is used with a non-grey "
			<< "absorption model" << nl << exit(FatalError);
	}

	scalarField& Iw = *this;
	const vectorField n(patch().nf());

	radiationModels::radiativeIntensityRay& ray =
		const_cast<radiationModels::radiativeIntensityRay&>(dom.IRay(rayId));

	const scalarField nAve(n & ray.dAve());

	ray.qr().boundaryFieldRef()[patchi] += Iw * nAve;

	const scalarField temissivity = emissivity();

	scalarField& qem = ray.qem().boundaryFieldRef()[patchi];
	scalarField& qin = ray.qin().boundaryFieldRef()[patchi];

	const vector& myRayId = dom.IRay(rayId).dAve();

	// Use updated Ir while iterating over rays
	// avoids to used lagged qin
	scalarField Ir = dom.IRay(0).qin().boundaryField()[patchi];

	for (label rayI = 1; rayI < dom.nRay(); rayI++)
	{
		Ir += dom.IRay(rayI).qin().boundaryField()[patchi];
	}

	forAll(Iw, facei)
	{
		if ((-n[facei] & myRayId) > 0.0)
		{
			// direction out of the wall
			refGrad()[facei] = 0.0;
			valueFraction()[facei] = 1.0;
			refValue()[facei] =
				(
					Ir[facei] * (scalar(1) - temissivity[facei])
					+ temissivity[facei] * physicoChemical::sigma.value()
					* pow4(Tp[facei])
					) / pi;

			// Emitted heat flux from this ray direction
			qem[facei] = refValue()[facei] * nAve[facei];
		}
		else
		{
			// direction into the wall
			valueFraction()[facei] = 0.0;
			refGrad()[facei] = 0.0;
			refValue()[facei] = 0.0; // not used

			// Incident heat flux on this ray direction
			qin[facei] = Iw[facei] * nAve[facei];
		}
	}

	// Restore tag
	UPstream::msgType() = oldTag;

	mixedFvPatchScalarField::updateCoeffs();
}


void tnbLib::greyDiffusiveRadiationMixedFvPatchScalarField::write
(
	Ostream& os
) const
{
	mixedFvPatchScalarField::write(os);
	radiationCoupledBase::write(os);
	writeEntryIfDifferent<word>(os, "T", "T", TName_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		greyDiffusiveRadiationMixedFvPatchScalarField
	);
}


// ************************************************************************* //