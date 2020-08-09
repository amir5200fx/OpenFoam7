#include <skewCorrectionVectors.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(skewCorrectionVectors, 0);
}


// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

tnbLib::skewCorrectionVectors::skewCorrectionVectors(const fvMesh& mesh)
	:
	MeshObject<fvMesh, tnbLib::MoveableMeshObject, skewCorrectionVectors>(mesh),
	skew_(false),
	skewCorrectionVectors_
	(
		IOobject
		(
			"skewCorrectionVectors",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		mesh_,
		dimless
	)
{
	calcSkewCorrectionVectors();
}


tnbLib::skewCorrectionVectors::~skewCorrectionVectors()
{}


void tnbLib::skewCorrectionVectors::calcSkewCorrectionVectors()
{
	if (debug)
	{
		InfoInFunction << "Calculating skew correction vectors" << endl;
	}

	// Set local references to mesh data
	const volVectorField& C = mesh_.C();
	const surfaceVectorField& Cf = mesh_.Cf();
	const surfaceVectorField& Sf = mesh_.Sf();

	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		vector d = C[nei] - C[own];
		vector Cpf = Cf[facei] - C[own];

		skewCorrectionVectors_[facei] =
			Cpf - ((Sf[facei] & Cpf) / (Sf[facei] & d))*d;
	}

	surfaceVectorField::Boundary& skewCorrVecsBf =
		skewCorrectionVectors_.boundaryFieldRef();

	forAll(skewCorrVecsBf, patchi)
	{
		fvsPatchVectorField& patchSkewCorrVecs = skewCorrVecsBf[patchi];

		if (!patchSkewCorrVecs.coupled())
		{
			patchSkewCorrVecs = Zero;
		}
		else
		{
			const fvPatch& p = patchSkewCorrVecs.patch();
			const labelUList& faceCells = p.faceCells();
			const vectorField& patchFaceCentres = Cf.boundaryField()[patchi];
			const vectorField& patchSf = Sf.boundaryField()[patchi];
			const vectorField patchD(p.delta());

			forAll(p, patchFacei)
			{
				vector Cpf =
					patchFaceCentres[patchFacei] - C[faceCells[patchFacei]];

				patchSkewCorrVecs[patchFacei] =
					Cpf
					- (
					(patchSf[patchFacei] & Cpf) /
						(patchSf[patchFacei] & patchD[patchFacei])
						)*patchD[patchFacei];
			}
		}
	}

	scalar skewCoeff = 0.0;

	if (Sf.primitiveField().size())
	{
		skewCoeff =
			max(mag(skewCorrectionVectors_)*mesh_.deltaCoeffs()).value();
	}

	if (debug)
	{
		InfoInFunction << "skew coefficient = " << skewCoeff << endl;
	}

	if (skewCoeff < 1e-5)
	{
		skew_ = false;
	}
	else
	{
		skew_ = true;
	}

	if (debug)
	{
		Info << "    Finished constructing skew correction vectors" << endl;
	}
}


bool tnbLib::skewCorrectionVectors::movePoints()
{
	calcSkewCorrectionVectors();
	return true;
}


// ************************************************************************* //