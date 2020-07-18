#include <basicSymmetryFvPatchField.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::basicSymmetryFvPatchField<tnbLib::scalar>::snGrad() const
{
	return tmp<scalarField >(new scalarField(size(), 0.0));
}


template<>
void tnbLib::basicSymmetryFvPatchField<tnbLib::scalar>::evaluate
(
	const Pstream::commsTypes
)
{
	if (!updated())
	{
		updateCoeffs();
	}

	scalarField::operator=(patchInternalField());
	transformFvPatchField<scalar>::evaluate();
}


// ************************************************************************* //
