#pragma once

template<class Type>
tnbLib::tmp<Field<Type>> tnbLib::surfaceMeshWriter::getFaceField
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sfld
) const
{
	const polyBoundaryMesh& patches = sfld.mesh().boundaryMesh();

	tmp<Field<Type>> tfld(new Field<Type>(pp_.size()));
	Field<Type>& fld = tfld.ref();

	forAll(pp_.addressing(), i)
	{
		label facei = pp_.addressing()[i];

		label patchi = patches.whichPatch(facei);

		if (patchi == -1)
		{
			fld[i] = sfld[facei];
		}
		else
		{
			label localFacei = facei - patches[patchi].start();
			fld[i] = sfld.boundaryField()[patchi][localFacei];
		}
	}

	return tfld;
}


template<class Type>
void tnbLib::surfaceMeshWriter::write
(
	const UPtrList
	<
	const GeometricField<Type, fvsPatchField, surfaceMesh>
	>& sflds
)
{
	forAll(sflds, fieldi)
	{
		const GeometricField<Type, fvsPatchField, surfaceMesh>& fld =
			sflds[fieldi];

		os_ << fld.name() << ' ' << pTraits<Type>::nComponents << ' '
			<< pp_.size() << " float" << std::endl;

		DynamicList<floatScalar> fField(pTraits<Type>::nComponents * pp_.size());
		writeFuns::insert(getFaceField(fld)(), fField);
		writeFuns::write(os_, binary_, fField);
	}
}