#include <constrainPressure.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <geometricOneField.hxx>
#include <fixedFluxPressureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class RhoType, class RAUType, class MRFType>
void tnbLib::constrainPressure
(
	volScalarField& p,
	const RhoType& rho,
	const volVectorField& U,
	const surfaceScalarField& phiHbyA,
	const RAUType& rhorAU,
	const MRFType& MRF
)
{
	const fvMesh& mesh = p.mesh();

	volScalarField::Boundary& pBf = p.boundaryFieldRef();

	const volVectorField::Boundary& UBf = U.boundaryField();
	const surfaceScalarField::Boundary& phiHbyABf =
		phiHbyA.boundaryField();
	const typename RAUType::Boundary& rhorAUBf =
		rhorAU.boundaryField();
	const surfaceVectorField::Boundary& SfBf =
		mesh.Sf().boundaryField();
	const surfaceScalarField::Boundary& magSfBf =
		mesh.magSf().boundaryField();

	forAll(pBf, patchi)
	{
		if (isA<fixedFluxPressureFvPatchScalarField>(pBf[patchi]))
		{
			refCast<fixedFluxPressureFvPatchScalarField>
				(
					pBf[patchi]
					).updateCoeffs
					(
				(
					phiHbyABf[patchi]
					- rho.boundaryField()[patchi]
					* MRF.relative(SfBf[patchi] & UBf[patchi], patchi)
					)
						/ (magSfBf[patchi] * rhorAUBf[patchi])
					);
		}
	}
}


template<class RAUType>
void tnbLib::constrainPressure
(
	volScalarField& p,
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& phiHbyA,
	const RAUType& rAU
)
{
	constrainPressure(p, rho, U, phiHbyA, rAU, NullMRF());
}


template<class RAUType, class MRFType>
void tnbLib::constrainPressure
(
	volScalarField& p,
	const volVectorField& U,
	const surfaceScalarField& phiHbyA,
	const RAUType& rAU,
	const MRFType& MRF
)
{
	constrainPressure(p, geometricOneField(), U, phiHbyA, rAU, MRF);
}


template<class RAUType>
void tnbLib::constrainPressure
(
	volScalarField& p,
	const volVectorField& U,
	const surfaceScalarField& phiHbyA,
	const RAUType& rAU
)
{
	constrainPressure(p, U, phiHbyA, rAU, NullMRF());
}


// ************************************************************************* //