#include <wedgeFvPatchField.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	tmp<scalarField> wedgeFvPatchField<scalar>::snGrad() const
	{
		return tmp<scalarField >(new scalarField(size(), 0.0));
	}


	template<>
	void wedgeFvPatchField<scalar>::evaluate(const Pstream::commsTypes)
	{
		if (!updated())
		{
			updateCoeffs();
		}

		this->operator==(patchInternalField());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //