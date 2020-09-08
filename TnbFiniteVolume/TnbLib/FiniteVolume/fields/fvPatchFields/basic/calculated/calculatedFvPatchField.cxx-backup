#include <calculatedFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word& tnbLib::fvPatchField<Type>::calculatedType()
{
	return calculatedFvPatchField<Type>::typeName;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::calculatedFvPatchField<Type>::calculatedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::calculatedFvPatchField<Type>::calculatedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict,
	const bool valueRequired
)
	:
	fvPatchField<Type>(p, iF, dict, valueRequired)
{}


template<class Type>
tnbLib::calculatedFvPatchField<Type>::calculatedFvPatchField
(
	const calculatedFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper,
	const bool mappingRequired
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper, mappingRequired)
{}


template<class Type>
tnbLib::calculatedFvPatchField<Type>::calculatedFvPatchField
(
	const calculatedFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::calculatedFvPatchField<Type>::calculatedFvPatchField
(
	const calculatedFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf, iF)
{}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>>
tnbLib::fvPatchField<Type>::NewCalculatedType
(
	const fvPatch& p
)
{
	typename patchConstructorTable::iterator patchTypeCstrIter =
		patchConstructorTablePtr_->find(p.type());

	if (patchTypeCstrIter != patchConstructorTablePtr_->end())
	{
		return patchTypeCstrIter()
			(
				p,
				DimensionedField<Type, volMesh>::null()
				);
	}
	else
	{
		return tmp<fvPatchField<Type>>
			(
				new calculatedFvPatchField<Type>
				(
					p,
					DimensionedField<Type, volMesh>::null()
					)
				);
	}
}


template<class Type>
template<class Type2>
tnbLib::tmp<tnbLib::fvPatchField<Type>> tnbLib::fvPatchField<Type>::NewCalculatedType
(
	const fvPatchField<Type2>& pf
)
{
	return NewCalculatedType(pf.patch());
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::calculatedFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	FatalErrorInFunction
		<< "cannot be called for a calculatedFvPatchField"
		<< "\n    on patch " << this->patch().name()
		<< " of field " << this->internalField().name()
		<< " in file " << this->internalField().objectPath()
		<< "\n    You are probably trying to solve for a field with a "
		"default boundary condition."
		<< abort(FatalError);

	return *this;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::calculatedFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	FatalErrorInFunction
		<< "cannot be called for a calculatedFvPatchField"
		<< "\n    on patch " << this->patch().name()
		<< " of field " << this->internalField().name()
		<< " in file " << this->internalField().objectPath()
		<< "\n    You are probably trying to solve for a field with a "
		"default boundary condition."
		<< abort(FatalError);

	return *this;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::calculatedFvPatchField<Type>::gradientInternalCoeffs() const
{
	FatalErrorInFunction
		<< "cannot be called for a calculatedFvPatchField"
		<< "\n    on patch " << this->patch().name()
		<< " of field " << this->internalField().name()
		<< " in file " << this->internalField().objectPath()
		<< "\n    You are probably trying to solve for a field with a "
		"default boundary condition."
		<< abort(FatalError);

	return *this;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::calculatedFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	FatalErrorInFunction
		<< "cannot be called for a calculatedFvPatchField"
		<< "\n    on patch " << this->patch().name()
		<< " of field " << this->internalField().name()
		<< " in file " << this->internalField().objectPath()
		<< "\n    You are probably trying to solve for a field with a "
		"default boundary condition."
		<< abort(FatalError);

	return *this;
}


template<class Type>
void tnbLib::calculatedFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //