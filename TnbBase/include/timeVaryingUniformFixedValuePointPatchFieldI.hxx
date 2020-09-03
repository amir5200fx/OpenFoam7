#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::
timeVaryingUniformFixedValuePointPatchField<Type>::
timeVaryingUniformFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::
timeVaryingUniformFixedValuePointPatchField<Type>::
timeVaryingUniformFixedValuePointPatchField
(
	const timeVaryingUniformFixedValuePointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& mapper
)
	:
	fixedValuePointPatchField<Type>(ptf, p, iF, mapper),
	timeSeries_(ptf.timeSeries_)
{
	this->operator==(timeSeries_(this->db().time().timeOutputValue()));
}


template<class Type>
tnbLib::
timeVaryingUniformFixedValuePointPatchField<Type>::
timeVaryingUniformFixedValuePointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	fixedValuePointPatchField<Type>(p, iF),
	timeSeries_(dict)
{
	this->operator==(timeSeries_(this->db().time().timeOutputValue()));
}


template<class Type>
tnbLib::
timeVaryingUniformFixedValuePointPatchField<Type>::
timeVaryingUniformFixedValuePointPatchField
(
	const timeVaryingUniformFixedValuePointPatchField<Type>& ptf
)
	:
	fixedValuePointPatchField<Type>(ptf),
	timeSeries_(ptf.timeSeries_)
{}


template<class Type>
tnbLib::
timeVaryingUniformFixedValuePointPatchField<Type>::
timeVaryingUniformFixedValuePointPatchField
(
	const timeVaryingUniformFixedValuePointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	fixedValuePointPatchField<Type>(ptf, iF),
	timeSeries_(ptf.timeSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::timeVaryingUniformFixedValuePointPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	this->operator==(timeSeries_(this->db().time().timeOutputValue()));
	fixedValuePointPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::timeVaryingUniformFixedValuePointPatchField<Type>::write
(
	Ostream& os
) const
{
	fixedValuePointPatchField<Type>::write(os);
	timeSeries_.write(os);
}


// ************************************************************************* //