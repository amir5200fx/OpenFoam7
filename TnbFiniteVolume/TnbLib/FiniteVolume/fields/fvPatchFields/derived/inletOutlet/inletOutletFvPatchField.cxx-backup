#include <inletOutletFvPatchField.hxx>

#include <dictionary.hxx>  // added by amir
#include <surfaceFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::inletOutletFvPatchField<Type>::inletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(p, iF),
	phiName_("phi")
{
	this->refValue() = Zero;
	this->refGrad() = Zero;
	this->valueFraction() = 0.0;
}


template<class Type>
tnbLib::inletOutletFvPatchField<Type>::inletOutletFvPatchField
(
	const inletOutletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<Type>(ptf, p, iF, mapper),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::inletOutletFvPatchField<Type>::inletOutletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<Type>(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
	this->refValue() = Field<Type>("inletValue", dict, p.size());

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
tnbLib::inletOutletFvPatchField<Type>::inletOutletFvPatchField
(
	const inletOutletFvPatchField<Type>& ptf
)
	:
	mixedFvPatchField<Type>(ptf),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::inletOutletFvPatchField<Type>::inletOutletFvPatchField
(
	const inletOutletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(ptf, iF),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::inletOutletFvPatchField<Type>::updateCoeffs()
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

	this->valueFraction() = 1.0 - pos0(phip);

	mixedFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::inletOutletFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	if (phiName_ != "phi")
	{
		writeEntry(os, "phi", phiName_);
	}
	writeEntry(os, "inletValue", this->refValue());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::inletOutletFvPatchField<Type>::operator=
(
	const fvPatchField<Type>& ptf
	)
{
	fvPatchField<Type>::operator=
		(
			this->valueFraction()*this->refValue()
			+ (1 - this->valueFraction())*ptf
			);
}


// ************************************************************************* //