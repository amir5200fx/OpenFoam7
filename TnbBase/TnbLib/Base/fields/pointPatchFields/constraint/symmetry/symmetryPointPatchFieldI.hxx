#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::symmetryPointPatchField<Type>::symmetryPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	basicSymmetryPointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::symmetryPointPatchField<Type>::symmetryPointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	basicSymmetryPointPatchField<Type>(p, iF, dict)
{
	if (!isType<symmetryPointPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not symmetry type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::symmetryPointPatchField<Type>::symmetryPointPatchField
(
	const symmetryPointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	basicSymmetryPointPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<symmetryPointPatch>(this->patch()))
	{
		FatalErrorInFunction
			<< "Field type does not correspond to patch type for patch "
			<< this->patch().index() << "." << endl
			<< "Field type: " << typeName << endl
			<< "Patch type: " << this->patch().type()
			<< exit(FatalError);
	}
}


template<class Type>
tnbLib::symmetryPointPatchField<Type>::symmetryPointPatchField
(
	const symmetryPointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	basicSymmetryPointPatchField<Type>(ptf, iF)
{}


// ************************************************************************* //