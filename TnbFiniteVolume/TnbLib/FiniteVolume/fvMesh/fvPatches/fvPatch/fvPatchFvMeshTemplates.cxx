#include <fvPatch.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class GeometricField, class Type>
const typename GeometricField::Patch& tnbLib::fvPatch::lookupPatchField
(
	const word& name,
	const GeometricField*,
	const Type*
) const
{
	return patchField<GeometricField, Type>
		(
			boundaryMesh().mesh().objectRegistry::template
			lookupObject<GeometricField>(name)
			);
}


// ************************************************************************* //