#pragma once
#include <pointPatchFieldMapper.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::valuePointPatchField<Type>::checkFieldSize() const
{
	if (this->size() != this->patch().size())
	{
		FatalErrorInFunction
			<< "field does not correspond to patch. " << endl
			<< "Field size: " << size() << " patch size: "
			<< this->patch().size()
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::valuePointPatchField<Type>::valuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(p, iF),
	Field<Type>(p.size())
{}


template<class Type>
tnbLib::valuePointPatchField<Type>::valuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict,
	const bool valueRequired
)
	:
	pointPatchField<Type>(p, iF, dict),
	Field<Type>(p.size())
{
	if (dict.found("value"))
	{
		Field<Type>::operator=
			(
				Field<Type>("value", dict, p.size())
				);
	}
	else if (!valueRequired)
	{
		Field<Type>::operator=(Zero);
	}
	else
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Essential entry 'value' missing"
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::valuePointPatchField<Type>::valuePointPatchField
(
	const valuePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	pointPatchField<Type>(ptf, p, iF, mapper),
	Field<Type>(mapper(ptf))
{}


template<class Type>
tnbLib::valuePointPatchField<Type>::valuePointPatchField
(
	const valuePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	pointPatchField<Type>(ptf, iF),
	Field<Type>(ptf)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::valuePointPatchField<Type>::autoMap
(
	const pointPatchFieldMapper& m
)
{
	m(*this, *this);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::rmap
(
	const pointPatchField<Type>& ptf,
	const labelList& addr
)
{
	Field<Type>::rmap
	(
		refCast<const valuePointPatchField<Type>>
		(
			ptf
			),
		addr
	);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Get internal field to insert values into
	Field<Type>& iF = const_cast<Field<Type>&>(this->primitiveField());

	this->setInInternalField(iF, *this);

	pointPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	// Get internal field to insert values into
	Field<Type>& iF = const_cast<Field<Type>&>(this->primitiveField());

	this->setInInternalField(iF, *this);

	pointPatchField<Type>::evaluate();
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::write(Ostream& os) const
{
	pointPatchField<Type>::write(os);
	writeEntry(os, "value", static_cast<const Field<Type>&>(*this));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::valuePointPatchField<Type>::operator=
(
	const valuePointPatchField<Type>& ptf
	)
{
	Field<Type>::operator=(ptf);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator=
(
	const pointPatchField<Type>& ptf
	)
{
	Field<Type>::operator=(this->patchInternalField());
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator=
(
	const Field<Type>& tf
	)
{
	Field<Type>::operator=(tf);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator=
(
	const Type& t
	)
{
	Field<Type>::operator=(t);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator==
(
	const valuePointPatchField<Type>& ptf
	)
{
	Field<Type>::operator=(ptf);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator==
(
	const pointPatchField<Type>& ptf
	)
{
	Field<Type>::operator=(this->patchInternalField());
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator==
(
	const Field<Type>& tf
	)
{
	Field<Type>::operator=(tf);
}


template<class Type>
void tnbLib::valuePointPatchField<Type>::operator==
(
	const Type& t
	)
{
	Field<Type>::operator=(t);
}


// ************************************************************************* //