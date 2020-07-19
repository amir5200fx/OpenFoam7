#include <fixedGradientFvPatchField.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedGradientFvPatchField<Type>::fixedGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(p, iF),
	gradient_(p.size(), Zero)
{}


template<class Type>
tnbLib::fixedGradientFvPatchField<Type>::fixedGradientFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fvPatchField<Type>(p, iF, dict, false),
	gradient_("gradient", dict, p.size())
{
	evaluate();
}


template<class Type>
tnbLib::fixedGradientFvPatchField<Type>::fixedGradientFvPatchField
(
	const fixedGradientFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fvPatchField<Type>(ptf, p, iF, mapper),
	gradient_(mapper(ptf.gradient_))
{
	if (notNull(iF) && mapper.hasUnmapped())
	{
		WarningInFunction
			<< "On field " << iF.name() << " patch " << p.name()
			<< " patchField " << this->type()
			<< " : mapper does not map all values." << nl
			<< "    To avoid this warning fully specify the mapping in derived"
			<< " patch fields." << endl;
	}
}


template<class Type>
tnbLib::fixedGradientFvPatchField<Type>::fixedGradientFvPatchField
(
	const fixedGradientFvPatchField<Type>& ptf
)
	:
	fvPatchField<Type>(ptf),
	gradient_(ptf.gradient_)
{}


template<class Type>
tnbLib::fixedGradientFvPatchField<Type>::fixedGradientFvPatchField
(
	const fixedGradientFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fvPatchField<Type>(ptf, iF),
	gradient_(ptf.gradient_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedGradientFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fvPatchField<Type>::autoMap(m);
	m(gradient_, gradient_);
}


template<class Type>
void tnbLib::fixedGradientFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	fvPatchField<Type>::rmap(ptf, addr);

	const fixedGradientFvPatchField<Type>& fgptf =
		refCast<const fixedGradientFvPatchField<Type>>(ptf);

	gradient_.rmap(fgptf.gradient_, addr);
}


template<class Type>
void tnbLib::fixedGradientFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	Field<Type>::operator=
		(
			this->patchInternalField() + gradient_ / this->patch().deltaCoeffs()
			);

	fvPatchField<Type>::evaluate();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedGradientFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	return tmp<Field<Type>>(new Field<Type>(this->size(), pTraits<Type>::one));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedGradientFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>&
) const
{
	return gradient() / this->patch().deltaCoeffs();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedGradientFvPatchField<Type>::gradientInternalCoeffs() const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(this->size(), Zero)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::fixedGradientFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	return gradient();
}


template<class Type>
void tnbLib::fixedGradientFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "gradient", gradient_);
}


// ************************************************************************* //