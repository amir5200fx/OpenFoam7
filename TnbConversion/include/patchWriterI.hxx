#pragma once
template<class Type>
void tnbLib::patchWriter::write
(
	const UPtrList<const GeometricField<Type, fvPatchField, volMesh>>& flds
)
{
	forAll(flds, fieldi)
	{
		const GeometricField<Type, fvPatchField, volMesh>& fld = flds[fieldi];

		os_ << fld.name() << ' ' << pTraits<Type>::nComponents << ' '
			<< nFaces_ << " float" << std::endl;

		DynamicList<floatScalar> fField(pTraits<Type>::nComponents * nFaces_);

		forAll(patchIDs_, j)
		{
			label patchi = patchIDs_[j];

			const fvPatchField<Type>& pfld = fld.boundaryField()[patchi];

			if (nearCellValue_)
			{
				writeFuns::insert(pfld.patchInternalField()(), fField);
			}
			else
			{
				writeFuns::insert(pfld, fField);
			}
		}
		writeFuns::write(os_, binary_, fField);
	}
}


template<class Type>
void tnbLib::patchWriter::write
(
	const UPtrList<const GeometricField<Type, pointPatchField, pointMesh>>& flds
)
{
	forAll(flds, fieldi)
	{
		const GeometricField<Type, pointPatchField, pointMesh>& fld =
			flds[fieldi];

		os_ << fld.name() << ' ' << pTraits<Type>::nComponents << ' '
			<< nPoints_ << " float" << std::endl;

		DynamicList<floatScalar> fField(pTraits<Type>::nComponents * nPoints_);

		forAll(patchIDs_, j)
		{
			label patchi = patchIDs_[j];

			const pointPatchField<Type>& pfld = fld.boundaryField()[patchi];

			writeFuns::insert(pfld.patchInternalField()(), fField);
		}
		writeFuns::write(os_, binary_, fField);
	}
}


template<class Type>
void tnbLib::patchWriter::write
(
	const PrimitivePatchInterpolation<primitivePatch>& pInter,
	const UPtrList<const GeometricField<Type, fvPatchField, volMesh>>& flds
)
{
	forAll(flds, fieldi)
	{
		const GeometricField<Type, fvPatchField, volMesh>& fld = flds[fieldi];

		os_ << fld.name() << ' ' << pTraits<Type>::nComponents << ' '
			<< nPoints_ << " float" << std::endl;

		DynamicList<floatScalar> fField(pTraits<Type>::nComponents * nPoints_);

		forAll(patchIDs_, j)
		{
			label patchi = patchIDs_[j];

			const fvPatchField<Type>& pfld = fld.boundaryField()[patchi];

			if (nearCellValue_)
			{
				writeFuns::insert
				(
					pInter.faceToPointInterpolate
					(
						pfld.patchInternalField()()
					)(),
					fField
				);
			}
			else
			{
				writeFuns::insert
				(
					pInter.faceToPointInterpolate(pfld)(),
					fField
				);
			}
		}
		writeFuns::write(os_, binary_, fField);
	}
}