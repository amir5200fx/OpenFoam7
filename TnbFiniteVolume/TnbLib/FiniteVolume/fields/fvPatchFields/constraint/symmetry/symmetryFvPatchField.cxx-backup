#include <symmetryFvPatchField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::symmetryFvPatchField<Type>::symmetryFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	basicSymmetryFvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::symmetryFvPatchField<Type>::symmetryFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	basicSymmetryFvPatchField<Type>(p, iF, dict)
{
	if (!isType<symmetryFvPatch>(p))
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
tnbLib::symmetryFvPatchField<Type>::symmetryFvPatchField
(
	const symmetryFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	basicSymmetryFvPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<symmetryFvPatch>(this->patch()))
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
tnbLib::symmetryFvPatchField<Type>::symmetryFvPatchField
(
	const symmetryFvPatchField<Type>& ptf
)
	:
	basicSymmetryFvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::symmetryFvPatchField<Type>::symmetryFvPatchField
(
	const symmetryFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	basicSymmetryFvPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //