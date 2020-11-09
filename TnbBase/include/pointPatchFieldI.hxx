#pragma once
#include <pointMesh.hxx>
#include <dictionary.hxx>
#include <calculatedPointPatchField.hxx>

template<class Type>
const tnbLib::word& tnbLib::pointPatchField<Type>::calculatedType()
{
	return calculatedPointPatchField<Type>::typeName;
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::pointPatchField<Type>::pointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	patch_(p),
	internalField_(iF),
	updated_(false),
	patchType_(word::null)
{}


template<class Type>
tnbLib::pointPatchField<Type>::pointPatchField
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
	:
	patch_(p),
	internalField_(iF),
	updated_(false),
	patchType_(dict.lookupOrDefault<word>("patchType", word::null))
{}


template<class Type>
tnbLib::pointPatchField<Type>::pointPatchField
(
	const pointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper&
)
	:
	patch_(p),
	internalField_(iF),
	updated_(false),
	patchType_(ptf.patchType_)
{}


template<class Type>
tnbLib::pointPatchField<Type>::pointPatchField
(
	const pointPatchField<Type>& ptf
)
	:
	patch_(ptf.patch_),
	internalField_(ptf.internalField_),
	updated_(false),
	patchType_(ptf.patchType_)
{}


template<class Type>
tnbLib::pointPatchField<Type>::pointPatchField
(
	const pointPatchField<Type>& ptf,
	const DimensionedField<Type, pointMesh>& iF
)
	:
	patch_(ptf.patch_),
	internalField_(iF),
	updated_(false),
	patchType_(ptf.patchType_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::objectRegistry& tnbLib::pointPatchField<Type>::db() const
{
	return patch_.boundaryMesh().mesh()();
}


template<class Type>
void tnbLib::pointPatchField<Type>::write(Ostream& os) const
{
	writeEntry(os, "type", type());

	if (patchType_.size())
	{
		writeEntry(os, "patchType", patchType_);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::pointPatchField<Type>::patchInternalField() const
{
	return patchInternalField(primitiveField());
}


template<class Type>
template<class Type1>
tnbLib::tmp<tnbLib::Field<Type1>>
tnbLib::pointPatchField<Type>::patchInternalField
(
	const Field<Type1>& iF,
	const labelList& meshPoints
) const
{
	// Check size
	if (iF.size() != primitiveField().size())
	{
		FatalErrorInFunction
			<< "given internal field does not correspond to the mesh. "
			<< "Field size: " << iF.size()
			<< " mesh size: " << primitiveField().size()
			<< abort(FatalError);
	}

	return tmp<Field<Type1>>(new Field<Type1>(iF, meshPoints));
}


template<class Type>
template<class Type1>
tnbLib::tmp<tnbLib::Field<Type1>>
tnbLib::pointPatchField<Type>::patchInternalField
(
	const Field<Type1>& iF
) const
{
	return patchInternalField(iF, patch().meshPoints());
}


template<class Type>
template<class Type1>
void tnbLib::pointPatchField<Type>::addToInternalField
(
	Field<Type1>& iF,
	const Field<Type1>& pF
) const
{
	// Check size
	if (iF.size() != primitiveField().size())
	{
		FatalErrorInFunction
			<< "given internal field does not correspond to the mesh. "
			<< "Field size: " << iF.size()
			<< " mesh size: " << primitiveField().size()
			<< abort(FatalError);
	}

	if (pF.size() != size())
	{
		FatalErrorInFunction
			<< "given patch field does not correspond to the mesh. "
			<< "Field size: " << pF.size()
			<< " mesh size: " << size()
			<< abort(FatalError);
	}

	// Get the addressing
	const labelList& mp = patch().meshPoints();

	forAll(mp, pointi)
	{
		iF[mp[pointi]] += pF[pointi];
	}
}


template<class Type>
template<class Type1>
void tnbLib::pointPatchField<Type>::addToInternalField
(
	Field<Type1>& iF,
	const Field<Type1>& pF,
	const labelList& points
) const
{
	// Check size
	if (iF.size() != primitiveField().size())
	{
		FatalErrorInFunction
			<< "given internal field does not correspond to the mesh. "
			<< "Field size: " << iF.size()
			<< " mesh size: " << primitiveField().size()
			<< abort(FatalError);
	}

	if (pF.size() != size())
	{
		FatalErrorInFunction
			<< "given patch field does not correspond to the mesh. "
			<< "Field size: " << pF.size()
			<< " mesh size: " << size()
			<< abort(FatalError);
	}

	// Get the addressing
	const labelList& mp = patch().meshPoints();

	forAll(points, i)
	{
		label pointi = points[i];
		iF[mp[pointi]] += pF[pointi];
	}
}


template<class Type>
template<class Type1>
void tnbLib::pointPatchField<Type>::setInInternalField
(
	Field<Type1>& iF,
	const Field<Type1>& pF,
	const labelList& meshPoints
) const
{
	// Check size
	if (iF.size() != primitiveField().size())
	{
		FatalErrorInFunction
			<< "given internal field does not correspond to the mesh. "
			<< "Field size: " << iF.size()
			<< " mesh size: " << primitiveField().size()
			<< abort(FatalError);
	}

	if (pF.size() != meshPoints.size())
	{
		FatalErrorInFunction
			<< "given patch field does not correspond to the meshPoints. "
			<< "Field size: " << pF.size()
			<< " meshPoints size: " << size()
			<< abort(FatalError);
	}

	forAll(meshPoints, pointi)
	{
		iF[meshPoints[pointi]] = pF[pointi];
	}
}


template<class Type>
template<class Type1>
void tnbLib::pointPatchField<Type>::setInInternalField
(
	Field<Type1>& iF,
	const Field<Type1>& pF
) const
{
	setInInternalField(iF, pF, patch().meshPoints());
}


template<class Type>
void tnbLib::pointPatchField<Type>::evaluate(const Pstream::commsTypes)
{
	if (!updated_)
	{
		updateCoeffs();
	}

	updated_ = false;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const pointPatchField<Type>& ptf
	)
{
	ptf.write(os);

	os.check("Ostream& operator<<(Ostream&, const pointPatchField<Type>&)");

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //