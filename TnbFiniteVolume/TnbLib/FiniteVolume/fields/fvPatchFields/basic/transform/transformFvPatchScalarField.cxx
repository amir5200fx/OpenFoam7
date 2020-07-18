#include <transformFvPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::transformFvPatchField<tnbLib::scalar>::valueInternalCoeffs
(
	const tmp<scalarField>&
) const
{
	return tmp<scalarField>(new scalarField(size(), 1.0));
}


template<>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::transformFvPatchField<tnbLib::scalar>::gradientInternalCoeffs() const
{
	return tmp<scalarField>(new scalarField(size(), 0.0));
}


// ************************************************************************* //