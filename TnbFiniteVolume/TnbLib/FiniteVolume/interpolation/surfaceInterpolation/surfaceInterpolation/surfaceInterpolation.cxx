#include <surfaceInterpolation.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <demandDrivenData.hxx>
#include <coupledFvPatch.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceInterpolation, 0);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::surfaceInterpolation::clearOut()
{
	deleteDemandDrivenData(weights_);
	deleteDemandDrivenData(deltaCoeffs_);
	deleteDemandDrivenData(nonOrthDeltaCoeffs_);
	deleteDemandDrivenData(nonOrthCorrectionVectors_);
}


// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

tnbLib::surfaceInterpolation::surfaceInterpolation(const fvMesh& fvm)
	:
	mesh_(fvm),
	weights_(nullptr),
	deltaCoeffs_(nullptr),
	nonOrthDeltaCoeffs_(nullptr),
	nonOrthCorrectionVectors_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::surfaceInterpolation::~surfaceInterpolation()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::surfaceScalarField&
tnbLib::surfaceInterpolation::weights() const
{
	if (!weights_)
	{
		makeWeights();
	}

	return (*weights_);
}


const tnbLib::surfaceScalarField&
tnbLib::surfaceInterpolation::deltaCoeffs() const
{
	if (!deltaCoeffs_)
	{
		makeDeltaCoeffs();
	}

	return (*deltaCoeffs_);
}


const tnbLib::surfaceScalarField&
tnbLib::surfaceInterpolation::nonOrthDeltaCoeffs() const
{
	if (!nonOrthDeltaCoeffs_)
	{
		makeNonOrthDeltaCoeffs();
	}

	return (*nonOrthDeltaCoeffs_);
}


const tnbLib::surfaceVectorField&
tnbLib::surfaceInterpolation::nonOrthCorrectionVectors() const
{
	if (!nonOrthCorrectionVectors_)
	{
		makeNonOrthCorrectionVectors();
	}

	return (*nonOrthCorrectionVectors_);
}


bool tnbLib::surfaceInterpolation::movePoints()
{
	deleteDemandDrivenData(weights_);
	deleteDemandDrivenData(deltaCoeffs_);
	deleteDemandDrivenData(nonOrthDeltaCoeffs_);
	deleteDemandDrivenData(nonOrthCorrectionVectors_);

	return true;
}


void tnbLib::surfaceInterpolation::makeWeights() const
{
	if (debug)
	{
		Pout << "surfaceInterpolation::makeWeights() : "
			<< "Constructing weighting factors for face interpolation"
			<< endl;
	}

	weights_ = new surfaceScalarField
	(
		IOobject
		(
			"weights",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false // Do not register
		),
		mesh_,
		dimless
	);
	surfaceScalarField& weights = *weights_;

	// Set local references to mesh data
	// (note that we should not use fvMesh sliced fields at this point yet
	//  since this causes a loop when generating weighting factors in
	//  coupledFvPatchField evaluation phase)
	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();

	const vectorField& Cf = mesh_.faceCentres();
	const vectorField& C = mesh_.cellCentres();
	const vectorField& Sf = mesh_.faceAreas();

	// ... and reference to the internal field of the weighting factors
	scalarField& w = weights.primitiveFieldRef();

	forAll(owner, facei)
	{
		// Note: mag in the dot-product.
		// For all valid meshes, the non-orthogonality will be less that
		// 90 deg and the dot-product will be positive.  For invalid
		// meshes (d & s <= 0), this will stabilise the calculation
		// but the result will be poor.
		const scalar SfdOwn = mag(Sf[facei] & (Cf[facei] - C[owner[facei]]));
		const scalar SfdNei = mag(Sf[facei] & (C[neighbour[facei]] - Cf[facei]));
		const scalar SfdOwnNei = SfdOwn + SfdNei;

		if (SfdNei / vGreat < SfdOwnNei)
		{
			w[facei] = SfdNei / SfdOwnNei;
		}
		else
		{
			const scalar dOwn = mag(Cf[facei] - C[owner[facei]]);
			const scalar dNei = mag(C[neighbour[facei]] - Cf[facei]);
			const scalar dOwnNei = dOwn + dNei;

			w[facei] = dNei / dOwnNei;
		}
	}

	surfaceScalarField::Boundary& wBf =
		weights.boundaryFieldRef();

	forAll(mesh_.boundary(), patchi)
	{
		mesh_.boundary()[patchi].makeWeights(wBf[patchi]);
	}

	if (debug)
	{
		Pout << "surfaceInterpolation::makeWeights() : "
			<< "Finished constructing weighting factors for face interpolation"
			<< endl;
	}
}


void tnbLib::surfaceInterpolation::makeDeltaCoeffs() const
{
	if (debug)
	{
		Pout << "surfaceInterpolation::makeDeltaCoeffs() : "
			<< "Constructing differencing factors array for face gradient"
			<< endl;
	}

	// Force the construction of the weighting factors
	// needed to make sure deltaCoeffs are calculated for parallel runs.
	weights();

	deltaCoeffs_ = new surfaceScalarField
	(
		IOobject
		(
			"deltaCoeffs",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false // Do not register
		),
		mesh_,
		dimless / dimLength
	);
	surfaceScalarField& deltaCoeffs = *deltaCoeffs_;


	// Set local references to mesh data
	const volVectorField& C = mesh_.C();
	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();

	forAll(owner, facei)
	{
		deltaCoeffs[facei] = 1.0 / mag(C[neighbour[facei]] - C[owner[facei]]);
	}

	surfaceScalarField::Boundary& deltaCoeffsBf =
		deltaCoeffs.boundaryFieldRef();

	forAll(deltaCoeffsBf, patchi)
	{
		deltaCoeffsBf[patchi] = 1.0 / mag(mesh_.boundary()[patchi].delta());
	}
}


void tnbLib::surfaceInterpolation::makeNonOrthDeltaCoeffs() const
{
	if (debug)
	{
		Pout << "surfaceInterpolation::makeNonOrthDeltaCoeffs() : "
			<< "Constructing differencing factors array for face gradient"
			<< endl;
	}

	// Force the construction of the weighting factors
	// needed to make sure deltaCoeffs are calculated for parallel runs.
	weights();

	nonOrthDeltaCoeffs_ = new surfaceScalarField
	(
		IOobject
		(
			"nonOrthDeltaCoeffs",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false // Do not register
		),
		mesh_,
		dimless / dimLength
	);
	surfaceScalarField& nonOrthDeltaCoeffs = *nonOrthDeltaCoeffs_;


	// Set local references to mesh data
	const volVectorField& C = mesh_.C();
	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();
	const surfaceVectorField& Sf = mesh_.Sf();
	const surfaceScalarField& magSf = mesh_.magSf();

	forAll(owner, facei)
	{
		vector delta = C[neighbour[facei]] - C[owner[facei]];
		vector unitArea = Sf[facei] / magSf[facei];

		// Standard cell-centre distance form
		// NonOrthDeltaCoeffs[facei] = (unitArea & delta)/magSqr(delta);

		// Slightly under-relaxed form
		// NonOrthDeltaCoeffs[facei] = 1.0/mag(delta);

		// More under-relaxed form
		// NonOrthDeltaCoeffs[facei] = 1.0/(mag(unitArea & delta) + vSmall);

		// Stabilised form for bad meshes
		nonOrthDeltaCoeffs[facei] = 1.0 / max(unitArea & delta, 0.05*mag(delta));
	}

	surfaceScalarField::Boundary& nonOrthDeltaCoeffsBf =
		nonOrthDeltaCoeffs.boundaryFieldRef();

	forAll(nonOrthDeltaCoeffsBf, patchi)
	{
		vectorField delta(mesh_.boundary()[patchi].delta());

		nonOrthDeltaCoeffsBf[patchi] =
			1.0 / max(mesh_.boundary()[patchi].nf() & delta, 0.05*mag(delta));
	}
}


void tnbLib::surfaceInterpolation::makeNonOrthCorrectionVectors() const
{
	if (debug)
	{
		Pout << "surfaceInterpolation::makeNonOrthCorrectionVectors() : "
			<< "Constructing non-orthogonal correction vectors"
			<< endl;
	}

	nonOrthCorrectionVectors_ = new surfaceVectorField
	(
		IOobject
		(
			"nonOrthCorrectionVectors",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false // Do not register
		),
		mesh_,
		dimless
	);
	surfaceVectorField& corrVecs = *nonOrthCorrectionVectors_;

	// Set local references to mesh data
	const volVectorField& C = mesh_.C();
	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();
	const surfaceVectorField& Sf = mesh_.Sf();
	const surfaceScalarField& magSf = mesh_.magSf();
	const surfaceScalarField& NonOrthDeltaCoeffs = nonOrthDeltaCoeffs();

	forAll(owner, facei)
	{
		vector unitArea = Sf[facei] / magSf[facei];
		vector delta = C[neighbour[facei]] - C[owner[facei]];

		corrVecs[facei] = unitArea - delta * NonOrthDeltaCoeffs[facei];
	}

	// Boundary correction vectors set to zero for boundary patches
	// and calculated consistently with internal corrections for
	// coupled patches

	surfaceVectorField::Boundary& corrVecsBf =
		corrVecs.boundaryFieldRef();

	forAll(corrVecsBf, patchi)
	{
		fvsPatchVectorField& patchCorrVecs = corrVecsBf[patchi];

		if (!patchCorrVecs.coupled())
		{
			patchCorrVecs = Zero;
		}
		else
		{
			const fvsPatchScalarField& patchNonOrthDeltaCoeffs
				= NonOrthDeltaCoeffs.boundaryField()[patchi];

			const fvPatch& p = patchCorrVecs.patch();

			const vectorField patchDeltas(mesh_.boundary()[patchi].delta());

			forAll(p, patchFacei)
			{
				vector unitArea =
					Sf.boundaryField()[patchi][patchFacei]
					/ magSf.boundaryField()[patchi][patchFacei];

				const vector& delta = patchDeltas[patchFacei];

				patchCorrVecs[patchFacei] =
					unitArea - delta * patchNonOrthDeltaCoeffs[patchFacei];
			}
		}
	}

	if (debug)
	{
		Pout << "surfaceInterpolation::makeNonOrthCorrectionVectors() : "
			<< "Finished constructing non-orthogonal correction vectors"
			<< endl;
	}
}


// ************************************************************************* //
