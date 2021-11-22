#pragma once

template<class Type, template<class> class PatchField, class GeoMesh>
void tnbLib::internalWriter::write
(
	const UPtrList<const GeometricField<Type, PatchField, GeoMesh>>& flds
)
{
	forAll(flds, i)
	{
		writeFuns::write(os_, binary_, flds[i], vMesh_);
	}
}


template<class Type>
void tnbLib::internalWriter::write
(
	const volPointInterpolation& pInterp,
	const UPtrList<const GeometricField<Type, fvPatchField, volMesh>>& flds
)
{
	forAll(flds, i)
	{
		writeFuns::write
		(
			os_,
			binary_,
			flds[i],
			pInterp.interpolate(flds[i])(),
			vMesh_
		);
	}
}