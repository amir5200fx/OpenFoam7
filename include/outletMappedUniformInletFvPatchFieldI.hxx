#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::outletMappedUniformInletFvPatchField<Type>::
outletMappedUniformInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	outletPatchName_(),
	phiName_("phi")
{}


template<class Type>
tnbLib::outletMappedUniformInletFvPatchField<Type>::
outletMappedUniformInletFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict),
	outletPatchName_(dict.lookup("outletPatch")),
	phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{}


template<class Type>
tnbLib::outletMappedUniformInletFvPatchField<Type>::
outletMappedUniformInletFvPatchField
(
	const outletMappedUniformInletFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	outletPatchName_(ptf.outletPatchName_),
	phiName_(ptf.phiName_)
{}


template<class Type>
tnbLib::outletMappedUniformInletFvPatchField<Type>::
outletMappedUniformInletFvPatchField
(
	const outletMappedUniformInletFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	outletPatchName_(ptf.outletPatchName_),
	phiName_(ptf.phiName_)
{}



template<class Type>
tnbLib::outletMappedUniformInletFvPatchField<Type>::
outletMappedUniformInletFvPatchField
(
	const outletMappedUniformInletFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	outletPatchName_(ptf.outletPatchName_),
	phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::outletMappedUniformInletFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	const GeometricField<Type, fvPatchField, volMesh>& f
	(
		dynamic_cast<const GeometricField<Type, fvPatchField, volMesh>&>
		(
			this->internalField()
			)
	);

	const fvPatch& p = this->patch();
	label outletPatchID =
		p.patch().boundaryMesh().findPatchID(outletPatchName_);

	if (outletPatchID < 0)
	{
		FatalErrorInFunction
			<< "Unable to find outlet patch " << outletPatchName_
			<< abort(FatalError);
	}

	const fvPatch& outletPatch = p.boundaryMesh()[outletPatchID];

	const fvPatchField<Type>& outletPatchField =
		f.boundaryField()[outletPatchID];

	const surfaceScalarField& phi =
		this->db().objectRegistry::template lookupObject<surfaceScalarField>
		(phiName_);

	const scalarField& outletPatchPhi = phi.boundaryField()[outletPatchID];
	scalar sumOutletPatchPhi = gSum(outletPatchPhi);

	if (sumOutletPatchPhi > small)
	{
		Type averageOutletField =
			gSum(outletPatchPhi*outletPatchField)
			/ sumOutletPatchPhi;

		this->operator==(averageOutletField);
	}
	else
	{
		Type averageOutletField =
			gSum(outletPatch.magSf()*outletPatchField)
			/ gSum(outletPatch.magSf());

		this->operator==(averageOutletField);
	}

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::outletMappedUniformInletFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	writeEntry(os, "outletPatch", outletPatchName_);
	if (phiName_ != "phi")
	{
		writeEntry(os, "phi", phiName_);
	}
	writeEntry(os, "value", *this);
}


// ************************************************************************* //