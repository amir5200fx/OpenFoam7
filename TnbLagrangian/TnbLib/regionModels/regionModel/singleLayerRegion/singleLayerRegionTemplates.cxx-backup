#include <singleLayerRegion.hxx>

#include <zeroGradientFvPatchFields.hxx>
#include <mappedFixedInternalValueFvPatchFields.hxx>
#include <mappedFixedPushedInternalValueFvPatchFields.hxx>

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<class Type>
tnbLib::wordList
tnbLib::regionModels::singleLayerRegion::mappedFieldAndInternalPatchTypes() const
{
	wordList bTypes(regionMesh().boundaryMesh().size());

	bTypes = zeroGradientFvPatchField<Type>::typeName;

	forAll(intCoupledPatchIDs_, i)
	{
		const label patchi = intCoupledPatchIDs_[i];
		bTypes[patchi] = mappedFixedInternalValueFvPatchField<Type>::typeName;
	}

	return bTypes;
}


template<class Type>
tnbLib::wordList
tnbLib::regionModels::singleLayerRegion::mappedPushedFieldPatchTypes() const
{
	wordList bTypes(regionMesh().boundaryMesh().size());

	bTypes = zeroGradientFvPatchField<Type>::typeName;

	forAll(intCoupledPatchIDs_, i)
	{
		const label patchi = intCoupledPatchIDs_[i];
		bTypes[patchi] =
			mappedFixedPushedInternalValueFvPatchField<Type>::typeName;
	}

	return bTypes;
}


// ************************************************************************* //