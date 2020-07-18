#include <coupledFvPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(p)),
	fvPatchField<Type>(p, iF)
{}


template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const Field<Type>& f
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(p)),
	fvPatchField<Type>(p, iF, f)
{}


template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const coupledFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper,
	const bool mappingRequired
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(p)),
	fvPatchField<Type>(ptf, p, iF, mapper, mappingRequired)
{}


template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict,
	const bool valueRequired
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(p)),
	fvPatchField<Type>(p, iF, dict, valueRequired)
{}


template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const coupledFvPatchField<Type>& ptf
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(ptf.patch())),
	fvPatchField<Type>(ptf)
{}


template<class Type>
tnbLib::coupledFvPatchField<Type>::coupledFvPatchField
(
	const coupledFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	LduInterfaceField<Type>(refCast<const lduInterface>(ptf.patch())),
	fvPatchField<Type>(ptf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::coupledFvPatchField<Type>::snGrad
(
	const scalarField& deltaCoeffs
) const
{
	return
		deltaCoeffs
		* (this->patchNeighbourField() - this->patchInternalField());
}


template<class Type>
void tnbLib::coupledFvPatchField<Type>::initEvaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}
}


template<class Type>
void tnbLib::coupledFvPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	Field<Type>::operator=
		(
			this->patch().weights()*this->patchInternalField()
			+ (1.0 - this->patch().weights())*this->patchNeighbourField()
			);

	fvPatchField<Type>::evaluate();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::valueInternalCoeffs
(
	const tmp<scalarField>& w
) const
{
	return Type(pTraits<Type>::one)*w;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::valueBoundaryCoeffs
(
	const tmp<scalarField>& w
) const
{
	return Type(pTraits<Type>::one)*(1.0 - w);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::gradientInternalCoeffs
(
	const scalarField& deltaCoeffs
) const
{
	return -Type(pTraits<Type>::one)*deltaCoeffs;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::gradientInternalCoeffs() const
{
	NotImplemented;
	return -Type(pTraits<Type>::one)*this->patch().deltaCoeffs();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::gradientBoundaryCoeffs
(
	const scalarField& deltaCoeffs
) const
{
	return -this->gradientInternalCoeffs(deltaCoeffs);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::coupledFvPatchField<Type>::gradientBoundaryCoeffs() const
{
	NotImplemented;
	return -this->gradientInternalCoeffs();
}


template<class Type>
void tnbLib::coupledFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "value", *this);
}


// ************************************************************************* //