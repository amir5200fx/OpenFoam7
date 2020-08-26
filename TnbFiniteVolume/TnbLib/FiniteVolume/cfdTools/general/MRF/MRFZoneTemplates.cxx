#include <MRFZone.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::MRFZone::makeRelativeRhoFlux
(
	const RhoFieldType& rho,
	surfaceScalarField& phi
) const
{
	if (!active_)
	{
		return;
	}

	const surfaceVectorField& Cf = mesh_.Cf();
	const surfaceVectorField& Sf = mesh_.Sf();

	const vector Omega = omega_->value(mesh_.time().timeOutputValue())*axis_;

	const vectorField& Cfi = Cf;
	const vectorField& Sfi = Sf;
	scalarField& phii = phi.primitiveFieldRef();

	// Internal faces
	forAll(internalFaces_, i)
	{
		label facei = internalFaces_[i];
		phii[facei] -= rho[facei] * (Omega ^ (Cfi[facei] - origin_)) & Sfi[facei];
	}

	makeRelativeRhoFlux(rho.boundaryField(), phi.boundaryFieldRef());
}


template<class RhoFieldType>
void tnbLib::MRFZone::makeRelativeRhoFlux
(
	const RhoFieldType& rho,
	FieldField<fvsPatchField, scalar>& phi
) const
{
	if (!active_)
	{
		return;
	}

	const surfaceVectorField& Cf = mesh_.Cf();
	const surfaceVectorField& Sf = mesh_.Sf();

	const vector Omega = omega_->value(mesh_.time().timeOutputValue())*axis_;

	// Included patches
	forAll(includedFaces_, patchi)
	{
		forAll(includedFaces_[patchi], i)
		{
			label patchFacei = includedFaces_[patchi][i];

			phi[patchi][patchFacei] = 0.0;
		}
	}

	// Excluded patches
	forAll(excludedFaces_, patchi)
	{
		forAll(excludedFaces_[patchi], i)
		{
			label patchFacei = excludedFaces_[patchi][i];

			phi[patchi][patchFacei] -=
				rho[patchi][patchFacei]
				* (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin_))
				& Sf.boundaryField()[patchi][patchFacei];
		}
	}
}


template<class RhoFieldType>
void tnbLib::MRFZone::makeRelativeRhoFlux
(
	const RhoFieldType& rho,
	Field<scalar>& phi,
	const label patchi
) const
{
	if (!active_)
	{
		return;
	}

	const surfaceVectorField& Cf = mesh_.Cf();
	const surfaceVectorField& Sf = mesh_.Sf();

	const vector Omega = omega_->value(mesh_.time().timeOutputValue())*axis_;

	// Included patches
	forAll(includedFaces_[patchi], i)
	{
		label patchFacei = includedFaces_[patchi][i];

		phi[patchFacei] = 0.0;
	}

	// Excluded patches
	forAll(excludedFaces_[patchi], i)
	{
		label patchFacei = excludedFaces_[patchi][i];

		phi[patchFacei] -=
			rho[patchFacei]
			* (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin_))
			& Sf.boundaryField()[patchi][patchFacei];
	}
}


template<class RhoFieldType>
void tnbLib::MRFZone::makeAbsoluteRhoFlux
(
	const RhoFieldType& rho,
	surfaceScalarField& phi
) const
{
	if (!active_)
	{
		return;
	}

	const surfaceVectorField& Cf = mesh_.Cf();
	const surfaceVectorField& Sf = mesh_.Sf();

	const vector Omega = omega_->value(mesh_.time().timeOutputValue())*axis_;

	const vectorField& Cfi = Cf;
	const vectorField& Sfi = Sf;
	scalarField& phii = phi.primitiveFieldRef();

	// Internal faces
	forAll(internalFaces_, i)
	{
		label facei = internalFaces_[i];
		phii[facei] += rho[facei] * (Omega ^ (Cfi[facei] - origin_)) & Sfi[facei];
	}

	surfaceScalarField::Boundary& phibf = phi.boundaryFieldRef();


	// Included patches
	forAll(includedFaces_, patchi)
	{
		forAll(includedFaces_[patchi], i)
		{
			label patchFacei = includedFaces_[patchi][i];

			phibf[patchi][patchFacei] +=
				rho.boundaryField()[patchi][patchFacei]
				* (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin_))
				& Sf.boundaryField()[patchi][patchFacei];
		}
	}

	// Excluded patches
	forAll(excludedFaces_, patchi)
	{
		forAll(excludedFaces_[patchi], i)
		{
			label patchFacei = excludedFaces_[patchi][i];

			phibf[patchi][patchFacei] +=
				rho.boundaryField()[patchi][patchFacei]
				* (Omega ^ (Cf.boundaryField()[patchi][patchFacei] - origin_))
				& Sf.boundaryField()[patchi][patchFacei];
		}
	}
}


template<class Type>
void tnbLib::MRFZone::zero
(
	GeometricField<Type, fvsPatchField, surfaceMesh>& phi
) const
{
	if (!active_)
	{
		return;
	}

	Field<Type>& phii = phi.primitiveFieldRef();

	forAll(internalFaces_, i)
	{
		phii[internalFaces_[i]] = Zero;
	}

	typename GeometricField<Type, fvsPatchField, surfaceMesh>::Boundary& phibf =
		phi.boundaryFieldRef();

	forAll(includedFaces_, patchi)
	{
		forAll(includedFaces_[patchi], i)
		{
			phibf[patchi][includedFaces_[patchi][i]] = Zero;
		}
	}

	forAll(excludedFaces_, patchi)
	{
		forAll(excludedFaces_[patchi], i)
		{
			phibf[patchi][excludedFaces_[patchi][i]] = Zero;
		}
	}
}


// ************************************************************************* //