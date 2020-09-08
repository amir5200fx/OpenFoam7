#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::fvPatch::patchInternalField
(
	const UList<Type>& f
) const
{
	tmp<Field<Type>> tpif(new Field<Type>(size()));
	Field<Type>& pif = tpif.ref();

	const labelUList& faceCells = this->faceCells();

	forAll(pif, facei)
	{
		pif[facei] = f[faceCells[facei]];
	}

	return tpif;
}


template<class Type>
void tnbLib::fvPatch::patchInternalField
(
	const UList<Type>& f,
	Field<Type>& pif
) const
{
	pif.setSize(size());

	const labelUList& faceCells = this->faceCells();

	forAll(pif, facei)
	{
		pif[facei] = f[faceCells[facei]];
	}
}


template<class GeometricField, class Type>
const typename GeometricField::Patch& tnbLib::fvPatch::patchField
(
	const GeometricField& gf
) const
{
	return gf.boundaryField()[index()];
}


template<class GeometricField, class Type>
typename GeometricField::Patch& tnbLib::fvPatch::patchField
(
	GeometricField& gf
) const
{
	return gf.boundaryFieldRef()[index()];
}


// ************************************************************************* //