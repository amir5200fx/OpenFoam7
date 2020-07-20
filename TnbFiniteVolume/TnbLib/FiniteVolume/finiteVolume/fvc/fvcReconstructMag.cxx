#include <fvcReconstruct.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fvc
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		tmp<volScalarField> reconstructMag(const surfaceScalarField& ssf)
		{
			const fvMesh& mesh = ssf.mesh();

			const labelUList& owner = mesh.owner();
			const labelUList& neighbour = mesh.neighbour();

			const volVectorField& C = mesh.C();
			const surfaceVectorField& Cf = mesh.Cf();
			const surfaceVectorField& Sf = mesh.Sf();
			const surfaceScalarField& magSf = mesh.magSf();

			tmp<volScalarField> treconField
			(
				volScalarField::New
				(
					"reconstruct(" + ssf.name() + ')',
					mesh,
					dimensionedScalar
					(
						ssf.dimensions() / dimArea,
						scalar(0)
					),
					extrapolatedCalculatedFvPatchScalarField::typeName
				)
			);
			scalarField& rf = treconField.ref();

			forAll(owner, facei)
			{
				label own = owner[facei];
				label nei = neighbour[facei];

				rf[own] += (Sf[facei] & (Cf[facei] - C[own]))*ssf[facei] / magSf[facei];
				rf[nei] -= (Sf[facei] & (Cf[facei] - C[nei]))*ssf[facei] / magSf[facei];
			}

			const surfaceScalarField::Boundary& bsf = ssf.boundaryField();

			forAll(bsf, patchi)
			{
				const fvsPatchScalarField& psf = bsf[patchi];

				const labelUList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];
				const vectorField& pSf = Sf.boundaryField()[patchi];
				const scalarField& pMagSf = magSf.boundaryField()[patchi];

				forAll(pOwner, pFacei)
				{
					label own = pOwner[pFacei];
					rf[own] +=
						(pSf[pFacei] & (pCf[pFacei] - C[own]))
						*psf[pFacei] / pMagSf[pFacei];
				}
			}

			rf /= mesh.V();

			treconField.ref().correctBoundaryConditions();

			return treconField;
		}


		tmp<volScalarField> reconstructMag(const tmp<surfaceScalarField>& tssf)
		{
			tmp<volScalarField> tvf
			(
				fvc::reconstructMag(tssf())
			);
			tssf.clear();
			return tvf;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fvc

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //