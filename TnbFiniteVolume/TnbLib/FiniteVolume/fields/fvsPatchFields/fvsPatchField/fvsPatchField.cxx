#include <fvsPatchField.hxx>

#include <dictionary.hxx>
#include <fvMesh.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	Field<Type>(p.size()),
	patch_(p),
	internalField_(iF)
{}


template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const Field<Type>& f
)
	:
	Field<Type>(f),
	patch_(p),
	internalField_(iF)
{}


template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvsPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	Field<Type>(mapper(ptf)),
	patch_(p),
	internalField_(iF)
{}


template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, surfaceMesh>& iF,
	const dictionary& dict
)
	:
	Field<Type>(p.size()),
	patch_(p),
	internalField_(iF)
{
	if (dict.found("value"))
	{
		fvsPatchField<Type>::operator=
			(
				Field<Type>("value", dict, p.size())
				);
	}
	else
	{
		FatalIOErrorInFunction
		(
			dict
		) << "essential value entry not provided"
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvsPatchField<Type>& ptf
)
	:
	Field<Type>(ptf),
	patch_(ptf.patch_),
	internalField_(ptf.internalField_)
{}


template<class Type>
tnbLib::fvsPatchField<Type>::fvsPatchField
(
	const fvsPatchField<Type>& ptf,
	const DimensionedField<Type, surfaceMesh>& iF
)
	:
	Field<Type>(ptf),
	patch_(ptf.patch_),
	internalField_(iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::objectRegistry& tnbLib::fvsPatchField<Type>::db() const
{
	return patch_.boundaryMesh().mesh();
}


template<class Type>
void tnbLib::fvsPatchField<Type>::check(const fvsPatchField<Type>& ptf) const
{
	if (&patch_ != &(ptf.patch_))
	{
		FatalErrorInFunction
			<< "different patches for fvsPatchField<Type>s"
			<< abort(FatalError);
	}
}


template<class Type>
void tnbLib::fvsPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	m(*this, *this);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::rmap
(
	const fvsPatchField<Type>& ptf,
	const labelList& addr
)
{
	Field<Type>::rmap(ptf, addr);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::write(Ostream& os) const
{
	writeEntry(os, "type", type());
	writeEntry(os, "value", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fvsPatchField<Type>::operator=
(
	const UList<Type>& ul
	)
{
	Field<Type>::operator=(ul);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator=
(
	const fvsPatchField<Type>& ptf
	)
{
	check(ptf);
	Field<Type>::operator=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator+=
(
	const fvsPatchField<Type>& ptf
	)
{
	check(ptf);
	Field<Type>::operator+=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator-=
(
	const fvsPatchField<Type>& ptf
	)
{
	check(ptf);
	Field<Type>::operator-=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator*=
(
	const fvsPatchField<scalar>& ptf
	)
{
	if (&patch_ != &ptf.patch())
	{
		FatalErrorInFunction
			<< "incompatible patches for patch fields"
			<< abort(FatalError);
	}

	Field<Type>::operator*=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator/=
(
	const fvsPatchField<scalar>& ptf
	)
{
	if (&patch_ != &ptf.patch())
	{
		FatalErrorInFunction
			<< abort(FatalError);
	}

	Field<Type>::operator/=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator+=
(
	const Field<Type>& tf
	)
{
	Field<Type>::operator+=(tf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator-=
(
	const Field<Type>& tf
	)
{
	Field<Type>::operator-=(tf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator*=
(
	const scalarField& tf
	)
{
	Field<Type>::operator*=(tf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator/=
(
	const scalarField& tf
	)
{
	Field<Type>::operator/=(tf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator=
(
	const Type& t
	)
{
	Field<Type>::operator=(t);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator+=
(
	const Type& t
	)
{
	Field<Type>::operator+=(t);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator-=
(
	const Type& t
	)
{
	Field<Type>::operator-=(t);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator*=
(
	const scalar s
	)
{
	Field<Type>::operator*=(s);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator/=
(
	const scalar s
	)
{
	Field<Type>::operator/=(s);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator==
(
	const fvsPatchField<Type>& ptf
	)
{
	Field<Type>::operator=(ptf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator==
(
	const Field<Type>& tf
	)
{
	Field<Type>::operator=(tf);
}


template<class Type>
void tnbLib::fvsPatchField<Type>::operator==
(
	const Type& t
	)
{
	Field<Type>::operator=(t);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const fvsPatchField<Type>& ptf)
{
	ptf.write(os);

	os.check("Ostream& operator<<(Ostream&, const fvsPatchField<Type>&");

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <fvsPatchFieldNew.cxx>

// ************************************************************************* //