#include <LimitFuncs.hxx>

#include <objectRegistry.hxx>  // added by amir
#include <volFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::magSqr<Type>::operator()
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
	) const
{
	return tnbLib::magSqr(phi);
}


template<>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::magSqr<tnbLib::scalar>::operator()
(
	const volScalarField& phi
	) const
{
	return phi;
}


template<>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::magSqr<tnbLib::symmTensor>::operator()
(
	const volSymmTensorField& phi
	) const
{
	return tnbLib::tr(phi);
}


template<>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::magSqr<tnbLib::tensor>::operator()
(
	const volTensorField& phi
	) const
{
	return tnbLib::tr(phi);
}


template<class Type>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::rhoMagSqr<Type>::operator()
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
	) const
{
	const volScalarField& rho =
		phi.db().objectRegistry::template lookupObject<volScalarField>("rho");
	return tnbLib::magSqr(phi / rho);
}


template<>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::limitFuncs::rhoMagSqr<tnbLib::scalar>::operator()
(
	const volScalarField& phi
	) const
{
	const volScalarField& rho =
		phi.db().objectRegistry::lookupObject<volScalarField>("rho");
	return phi / rho;
}


// ************************************************************************* //