#include <fvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makeFvPatchField(fvPatchScalarField)
		makeFvPatchField(fvPatchVectorField)
		makeFvPatchField(fvPatchSphericalTensorField)
		makeFvPatchField(fvPatchSymmTensorField)
		makeFvPatchField(fvPatchTensorField)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //