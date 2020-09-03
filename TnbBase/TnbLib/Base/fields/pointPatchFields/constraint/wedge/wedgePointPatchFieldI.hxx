#pragma once
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::wedgePointPatchField<Type>::wedgePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::wedgePointPatchField<Type>::wedgePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	pointPatchField<Type>(p, iF, dict)
{
	if (!isType<wedgePointPatch>(p))
	{
		FatalIOErrorInFunction
		(
			dict
		) << "patch " << this->patch().index() << " not wedge type. "
			<< "Patch type = " << p.type()
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::wedgePointPatchField<Type>::wedgePointPatchField
(
	const wedgePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper)
{
	if (!isType<wedgePointPatch>(this->patch()))
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
tnbLib::wedgePointPatchField<Type>::wedgePointPatchField
(
	const wedgePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::wedgePointPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	// In order to ensure that the wedge patch is always flat, take the
	// normal vector from the first point
	const vector& nHat = this->patch().pointNormals()[0];

	tmp<Field<Type>> tvalues =
		transform(I - nHat * nHat, this->patchInternalField());

	// Get internal field to insert values into
	Field<Type>& iF = const_cast<Field<Type>&>(this->primitiveField());

	this->setInInternalField(iF, tvalues());
}


// ************************************************************************* //