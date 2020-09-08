#include <outletInletFvPatchField.hxx>

#include <dictionary.hxx>  // added by amir
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::outletInletFvPatchField<Type>::outletInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(p, iF),
	phiName_("phi")
{
	this->refValue() = *this;
	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


template<class Type>
tnbLib::outletInletFvPatchField<Type>::outletInletFvPatchField
(
	const outletInletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<Type>(ptf, p, iF, mapper),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::outletInletFvPatchField<Type>::outletInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<Type>(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	this->refValue() = Field<Type>("outletValue", dict, p.size());

	if (dict.found("value"))
	{
		fvPatchField<Type>::operator=
			(
				Field<Type>("value", dict, p.size())
				);
	}
	else
	{
		fvPatchField<Type>::operator=(this->refValue());
	}

	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


template<class Type>
tnbLib::outletInletFvPatchField<Type>::outletInletFvPatchField
(
	const outletInletFvPatchField<Type>& ptf
)
	:
	mixedFvPatchField<Type>(ptf),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::outletInletFvPatchField<Type>::outletInletFvPatchField
(
	const outletInletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(ptf, iF),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::outletInletFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const Field<scalar>& phip =
		this->patch().template lookupPatchField<surfaceScalarField, scalar>
		(
			phiName_
			);

	this->valueFraction() = pos0(phip);

	mixedFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::outletInletFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	if (phiName_ != "phi")
	{
		writeEntry(os, "phi", phiName_);
	}
	writeEntry(os, "outletValue", this->refValue());
	writeEntry(os, "value", *this);
}


// ************************************************************************* //