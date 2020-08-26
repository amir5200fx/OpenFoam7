#include <wideBandDiffusiveRadiationMixedFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>

#include <fvDOM.hxx>
#include <wideBand.hxx>
#include <constants.hxx>

using namespace tnbLib::constant;
using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::
wideBandDiffusiveRadiationMixedFvPatchScalarField
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


tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::
wideBandDiffusiveRadiationMixedFvPatchScalarField
(
	const wideBandDiffusiveRadiationMixedFvPatchScalarField& ptf,
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


tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::
wideBandDiffusiveRadiationMixedFvPatchScalarField
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
	if (dict.found("value"))
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
		const scalarField& Tp =
			patch().lookupPatchField<volScalarField, scalar>(TName_);

		refValue() =
			4.0*physicoChemical::sigma.value()*pow4(Tp)*emissivity() / pi;
		refGrad() = 0.0;

		fvPatchScalarField::operator=(refValue());
	}
}


tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::
wideBandDiffusiveRadiationMixedFvPatchScalarField
(
	const wideBandDiffusiveRadiationMixedFvPatchScalarField& ptf
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


tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::
wideBandDiffusiveRadiationMixedFvPatchScalarField
(
	const wideBandDiffusiveRadiationMixedFvPatchScalarField& ptf,
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

void tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::autoMap
(
	const fvPatchFieldMapper& m
)
{
	mixedFvPatchScalarField::autoMap(m);
	radiationCoupledBase::autoMap(m);
}


void tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	mixedFvPatchScalarField::rmap(ptf, addr);
	radiationCoupledBase::rmap(ptf, addr);
}


void tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Since we're inside initEvaluate/evaluate there might be processor
	// comms underway. Change the tag we use.
	int oldTag = UPstream::msgType();
	UPstream::msgType() = oldTag + 1;

	const radiationModels::fvDOM& dom =
		db().lookupObject<radiationModels::fvDOM>("radiationProperties");

	label rayId = -1;
	label lambdaId = -1;
	dom.setRayIdLambdaId(internalField().name(), rayId, lambdaId);

	const label patchi = patch().index();

	if (dom.nLambda() == 0)
	{
		FatalErrorInFunction
			<< " a non-grey boundary condition is used with a grey "
			<< "absorption model" << nl << exit(FatalError);
	}

	scalarField& Iw = *this;
	const vectorField n(patch().Sf() / patch().magSf());

	radiationModels::radiativeIntensityRay& ray =
		const_cast<radiationModels::radiativeIntensityRay&>(dom.IRay(rayId));

	const scalarField nAve(n & ray.dAve());

	ray.qr().boundaryFieldRef()[patchi] += Iw * nAve;

	const scalarField Eb
	(
		dom.blackBody().bLambda(lambdaId).boundaryField()[patchi]
	);

	scalarField temissivity = emissivity();

	scalarField& qem = ray.qem().boundaryFieldRef()[patchi];
	scalarField& qin = ray.qin().boundaryFieldRef()[patchi];

	// Use updated Ir while iterating over rays
	// avoids to used lagged qin
	scalarField Ir = dom.IRay(0).qin().boundaryField()[patchi];

	for (label rayI = 1; rayI < dom.nRay(); rayI++)
	{
		Ir += dom.IRay(rayI).qin().boundaryField()[patchi];
	}

	forAll(Iw, facei)
	{
		const vector& d = dom.IRay(rayId).d();

		if ((-n[facei] & d) > 0.0)
		{
			// direction out of the wall
			refGrad()[facei] = 0.0;
			valueFraction()[facei] = 1.0;
			refValue()[facei] =
				(
					Ir[facei] * (1.0 - temissivity[facei])
					+ temissivity[facei] * Eb[facei]
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


void tnbLib::wideBandDiffusiveRadiationMixedFvPatchScalarField::write
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
		wideBandDiffusiveRadiationMixedFvPatchScalarField
	);
}


// ************************************************************************* //