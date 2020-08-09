#include <waveTransmissiveFvPatchField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <EulerDdtScheme.hxx>
#include <CrankNicolsonDdtScheme.hxx>
#include <backwardDdtScheme.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::waveTransmissiveFvPatchField<Type>::waveTransmissiveFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	advectiveFvPatchField<Type>(p, iF),
	psiName_("thermo:psi"),
	gamma_(0.0)
{}


template<class Type>
tnbLib::waveTransmissiveFvPatchField<Type>::waveTransmissiveFvPatchField
(
	const waveTransmissiveFvPatchField& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	advectiveFvPatchField<Type>(ptf, p, iF, mapper),
	psiName_(ptf.psiName_),
	gamma_(ptf.gamma_)
{}


template<class Type>
tnbLib::waveTransmissiveFvPatchField<Type>::waveTransmissiveFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	advectiveFvPatchField<Type>(p, iF, dict),
	psiName_(dict.lookupOrDefault<word>("psi", "thermo:psi")),
	gamma_(readScalar(dict.lookup("gamma")))
{}


template<class Type>
tnbLib::waveTransmissiveFvPatchField<Type>::waveTransmissiveFvPatchField
(
	const waveTransmissiveFvPatchField& ptpsf
)
	:
	advectiveFvPatchField<Type>(ptpsf),
	psiName_(ptpsf.psiName_),
	gamma_(ptpsf.gamma_)
{}


template<class Type>
tnbLib::waveTransmissiveFvPatchField<Type>::waveTransmissiveFvPatchField
(
	const waveTransmissiveFvPatchField& ptpsf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	advectiveFvPatchField<Type>(ptpsf, iF),
	psiName_(ptpsf.psiName_),
	gamma_(ptpsf.gamma_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::waveTransmissiveFvPatchField<Type>::advectionSpeed() const
{
	// Lookup the velocity and compressibility of the patch
	const fvPatchField<scalar>& psip =
		this->patch().template
		lookupPatchField<volScalarField, scalar>(psiName_);

	const surfaceScalarField& phi =
		this->db().template lookupObject<surfaceScalarField>(this->phiName_);

	fvsPatchField<scalar> phip =
		this->patch().template
		lookupPatchField<surfaceScalarField, scalar>(this->phiName_);

	if (phi.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const fvPatchScalarField& rhop =
			this->patch().template
			lookupPatchField<volScalarField, scalar>(this->rhoName_);

		phip /= rhop;
	}

	// Calculate the speed of the field wave w
	// by summing the component of the velocity normal to the boundary
	// and the speed of sound (sqrt(gamma_/psi)).
	return phip / this->patch().magSf() + sqrt(gamma_ / psip);
}


template<class Type>
void tnbLib::waveTransmissiveFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);

	writeEntryIfDifferent<word>(os, "phi", "phi", this->phiName_);
	writeEntryIfDifferent<word>(os, "rho", "rho", this->rhoName_);
	writeEntryIfDifferent<word>(os, "psi", "thermo:psi", psiName_);

	writeEntry(os, "gamma", gamma_);

	if (this->lInf_ > small)
	{
		writeEntry(os, "fieldInf", this->fieldInf_);
		writeEntry(os, "lInf", this->lInf_);
	}

	writeEntry(os, "value", *this);
}


// ************************************************************************* //