#include <emptyFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::emptyFvPatchField<Type>::emptyFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF, Field<Type>(0))
{}


template<class Type>
tnbLib::emptyFvPatchField<Type>::emptyFvPatchField
(
	const emptyFvPatchField<Type>&,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper&
)
	:
	fvPatchField<Type>(p, iF, Field<Type>(0))
{
	if (!isType<emptyFvPatch>(p))
	{
		FatalErrorInFunction
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::emptyFvPatchField<Type>::emptyFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fvPatchField<Type>(p, iF, Field<Type>(0))
{
	if (!isType<emptyFvPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "\n    patch type '" << p.type()
			<< "' not constraint type '" << typeName << "'"
			<< "\n    for patch " << p.name()
			<< " of field " << this->internalField().name()
			<< " in file " << this->internalField().objectPath()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::emptyFvPatchField<Type>::emptyFvPatchField
(
	const emptyFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>
	(
		ptf.patch(),
		ptf.internalField(),
		Field<Type>(0)
		)
{}


template<class Type>
tnbLib::emptyFvPatchField<Type>::emptyFvPatchField
(
	const emptyFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf.patch(), iF, Field<Type>(0))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::emptyFvPatchField<Type>::updateCoeffs()
{
	// Check moved to checkMesh.
	// Test here fails if multiple empty patches.
}


// ************************************************************************* //