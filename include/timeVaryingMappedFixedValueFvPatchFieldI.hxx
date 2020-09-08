#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::
timeVaryingMappedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	fieldMapper_(p, iF.name())
{}


template<class Type>
tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::
timeVaryingMappedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict, false),
	fieldMapper_(p, dict, iF.name())
{
	if (dict.found("value"))
	{
		fvPatchField<Type>::operator==(Field<Type>("value", dict, p.size()));
	}
	else
	{
		// Note: we use evaluate() here to trigger updateCoeffs followed
		//       by re-setting of fvatchfield::updated_ flag. This is
		//       so if first use is in the next time step it retriggers
		//       a new update.
		this->evaluate(Pstream::commsTypes::blocking);
	}
}


template<class Type>
tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::
timeVaryingMappedFixedValueFvPatchField
(
	const timeVaryingMappedFixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	fieldMapper_(ptf.fieldMapper_)
{}


template<class Type>
tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::
timeVaryingMappedFixedValueFvPatchField
(
	const timeVaryingMappedFixedValueFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	fieldMapper_(ptf.fieldMapper_)
{}


template<class Type>
tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::
timeVaryingMappedFixedValueFvPatchField
(
	const timeVaryingMappedFixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	fieldMapper_(ptf.fieldMapper_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fixedValueFvPatchField<Type>::autoMap(m);
	fieldMapper_.autoMap(m);
}


template<class Type>
void tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	fixedValueFvPatchField<Type>::rmap(ptf, addr);
	fieldMapper_.rmap
	(
		refCast
		<
		const timeVaryingMappedFixedValueFvPatchField<Type>
		>(ptf).fieldMapper_,
		addr
	);
}


template<class Type>
void tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	this->operator==(fieldMapper_.map());

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::timeVaryingMappedFixedValueFvPatchField<Type>::write
(
	Ostream& os
) const
{
	fvPatchField<Type>::write(os);
	fieldMapper_.write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //