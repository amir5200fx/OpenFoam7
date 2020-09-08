#include <fixedProfileFvPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	profile_(),
	dir_(Zero),
	origin_(0)
{}


template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& fld
)
	:
	fixedValueFvPatchField<Type>(p, iF, fld),
	profile_(),
	dir_(Zero),
	origin_(0)
{}


template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict, false),
	profile_(Function1<Type>::New("profile", dict)),
	dir_(dict.lookup("direction")),
	origin_(readScalar(dict.lookup("origin")))
{
	if (mag(dir_) < small)
	{
		FatalErrorInFunction
			<< "magnitude Direction must be greater than zero"
			<< abort(FatalError);
	}

	// Ensure direction vector is normalized
	dir_ /= mag(dir_);

	// Evaluate profile
	this->evaluate();
}


template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fixedProfileFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(p, iF),  // Don't map
	profile_(ptf.profile_, false),
	dir_(ptf.dir_),
	origin_(ptf.origin_)
{
	// Evaluate profile since value not mapped
	this->evaluate();
}


template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fixedProfileFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	profile_(ptf.profile_, false),
	dir_(ptf.dir_),
	origin_(ptf.origin_)
{}


template<class Type>
tnbLib::fixedProfileFvPatchField<Type>::fixedProfileFvPatchField
(
	const fixedProfileFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	profile_(ptf.profile_, false),
	dir_(ptf.dir_),
	origin_(ptf.origin_)
{
	// Evaluate the profile if defined
	if (ptf.profile_.valid())
	{
		this->evaluate();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedProfileFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const scalarField dirCmpt((dir_ & this->patch().Cf()) - origin_);
	fvPatchField<Type>::operator==(profile_->value(dirCmpt));

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::fixedProfileFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, profile_());
	writeEntry(os, "direction", dir_);
	writeEntry(os, "origin", origin_);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //