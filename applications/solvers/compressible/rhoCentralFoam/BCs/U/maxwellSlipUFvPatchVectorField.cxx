#include <maxwellSlipUFvPatchVectorField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <mathematicalConstants.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::maxwellSlipUFvPatchVectorField::maxwellSlipUFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFixedValueSlipFvPatchVectorField(p, iF),
	TName_("T"),
	rhoName_("rho"),
	psiName_("thermo:psi"),
	muName_("thermo:mu"),
	tauMCName_("tauMC"),
	accommodationCoeff_(1.0),
	Uwall_(p.size(), vector(0.0, 0.0, 0.0)),
	thermalCreep_(true),
	curvature_(true)
{}


tnbLib::maxwellSlipUFvPatchVectorField::maxwellSlipUFvPatchVectorField
(
	const maxwellSlipUFvPatchVectorField& mspvf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFixedValueSlipFvPatchVectorField(mspvf, p, iF, mapper),
	TName_(mspvf.TName_),
	rhoName_(mspvf.rhoName_),
	psiName_(mspvf.psiName_),
	muName_(mspvf.muName_),
	tauMCName_(mspvf.tauMCName_),
	accommodationCoeff_(mspvf.accommodationCoeff_),
	Uwall_(mspvf.Uwall_),
	thermalCreep_(mspvf.thermalCreep_),
	curvature_(mspvf.curvature_)
{}


tnbLib::maxwellSlipUFvPatchVectorField::maxwellSlipUFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFixedValueSlipFvPatchVectorField(p, iF),
	TName_(dict.lookupOrDefault<word>("T", "T")),
	rhoName_(dict.lookupOrDefault<word>("rho", "rho")),
	psiName_(dict.lookupOrDefault<word>("psi", "thermo:psi")),
	muName_(dict.lookupOrDefault<word>("mu", "thermo:mu")),
	tauMCName_(dict.lookupOrDefault<word>("tauMC", "tauMC")),
	accommodationCoeff_(readScalar(dict.lookup("accommodationCoeff"))),
	Uwall_("Uwall", dict, p.size()),
	thermalCreep_(dict.lookupOrDefault("thermalCreep", true)),
	curvature_(dict.lookupOrDefault("curvature", true))
{
	if
		(
			mag(accommodationCoeff_) < small
			|| mag(accommodationCoeff_) > 2.0
			)
	{
		FatalIOErrorInFunction
		(
			dict
		) << "unphysical accommodationCoeff_ specified"
			<< "(0 < accommodationCoeff_ <= 1)" << endl
			<< exit(FatalIOError);
	}

	if (dict.found("value"))
	{
		fvPatchField<vector>::operator=
			(
				vectorField("value", dict, p.size())
				);

		if (dict.found("refValue") && dict.found("valueFraction"))
		{
			this->refValue() = vectorField("refValue", dict, p.size());
			this->valueFraction() =
				scalarField("valueFraction", dict, p.size());
		}
		else
		{
			this->refValue() = *this;
			this->valueFraction() = scalar(1);
		}
	}
}


tnbLib::maxwellSlipUFvPatchVectorField::maxwellSlipUFvPatchVectorField
(
	const maxwellSlipUFvPatchVectorField& mspvf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	mixedFixedValueSlipFvPatchVectorField(mspvf, iF),
	TName_(mspvf.TName_),
	rhoName_(mspvf.rhoName_),
	psiName_(mspvf.psiName_),
	muName_(mspvf.muName_),
	tauMCName_(mspvf.tauMCName_),
	accommodationCoeff_(mspvf.accommodationCoeff_),
	Uwall_(mspvf.Uwall_),
	thermalCreep_(mspvf.thermalCreep_),
	curvature_(mspvf.curvature_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::maxwellSlipUFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchScalarField& pmu =
		patch().lookupPatchField<volScalarField, scalar>(muName_);
	const fvPatchScalarField& prho =
		patch().lookupPatchField<volScalarField, scalar>(rhoName_);
	const fvPatchField<scalar>& ppsi =
		patch().lookupPatchField<volScalarField, scalar>(psiName_);

	Field<scalar> C1
	(
		sqrt(ppsi*constant::mathematical::piByTwo)
		* (2.0 - accommodationCoeff_) / accommodationCoeff_
	);

	Field<scalar> pnu(pmu / prho);
	valueFraction() = (1.0 / (1.0 + patch().deltaCoeffs()*C1*pnu));

	refValue() = Uwall_;

	if (thermalCreep_)
	{
		const volScalarField& vsfT =
			this->db().objectRegistry::lookupObject<volScalarField>(TName_);
		label patchi = this->patch().index();
		const fvPatchScalarField& pT = vsfT.boundaryField()[patchi];
		Field<vector> gradpT(fvc::grad(vsfT)().boundaryField()[patchi]);
		vectorField n(patch().nf());

		refValue() -= 3.0*pnu / (4.0*pT)*transform(I - n * n, gradpT);
	}

	if (curvature_)
	{
		const fvPatchTensorField& ptauMC =
			patch().lookupPatchField<volTensorField, tensor>(tauMCName_);
		vectorField n(patch().nf());

		refValue() -= C1 / prho * transform(I - n * n, (n & ptauMC));
	}

	mixedFixedValueSlipFvPatchVectorField::updateCoeffs();
}


void tnbLib::maxwellSlipUFvPatchVectorField::write(Ostream& os) const
{
	fvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "T", "T", TName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", rhoName_);
	writeEntryIfDifferent<word>(os, "psi", "thermo:psi", psiName_);
	writeEntryIfDifferent<word>(os, "mu", "thermo:mu", muName_);
	writeEntryIfDifferent<word>(os, "tauMC", "tauMC", tauMCName_);

	writeEntry(os, "accommodationCoeff", accommodationCoeff_);
	writeEntry(os, "Uwall", Uwall_);
	writeEntry(os, "thermalCreep", thermalCreep_);
	writeEntry(os, "curvature", curvature_);

	writeEntry(os, "refValue", refValue());
	writeEntry(os, "valueFraction", valueFraction());

	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		maxwellSlipUFvPatchVectorField
	);
}

// ************************************************************************* //