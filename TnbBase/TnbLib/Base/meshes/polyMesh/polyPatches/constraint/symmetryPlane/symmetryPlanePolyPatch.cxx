#include <symmetryPlanePolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <symmetryPolyPatch.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(symmetryPlanePolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, symmetryPlanePolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, symmetryPlanePolyPatch, dictionary);
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

void tnbLib::symmetryPlanePolyPatch::calcGeometry(PstreamBuffers&)
{
	if (n_ == vector::rootMax)
	{
		if (returnReduce(size(), sumOp<label>()))
		{
			const vectorField& nf(faceNormals());
			n_ = gAverage(nf);

			if (debug)
			{
				Info << "Patch " << name() << " calculated average normal "
					<< n_ << endl;
			}


			// Check the symmetry plane is planar
			forAll(nf, facei)
			{
				if (magSqr(n_ - nf[facei]) > small)
				{
					FatalErrorInFunction
						<< "Symmetry plane '" << name() << "' is not planar."
						<< endl
						<< "At local face at "
						<< primitivePatch::faceCentres()[facei]
						<< " the normal " << nf[facei]
						<< " differs from the average normal " << n_
						<< " by " << magSqr(n_ - nf[facei]) << endl
						<< "Either split the patch into planar parts"
						<< " or use the " << symmetryPolyPatch::typeName
						<< " patch type"
						<< exit(FatalError);
				}
			}
		}
	}
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::symmetryPlanePolyPatch::symmetryPlanePolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, size, start, index, bm, patchType),
	n_(vector::rootMax)
{}


tnbLib::symmetryPlanePolyPatch::symmetryPlanePolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType),
	n_(vector::rootMax)
{}


tnbLib::symmetryPlanePolyPatch::symmetryPlanePolyPatch
(
	const symmetryPlanePolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	n_(pp.n_)
{}


tnbLib::symmetryPlanePolyPatch::symmetryPlanePolyPatch
(
	const symmetryPlanePolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	n_(pp.n_)
{}


tnbLib::symmetryPlanePolyPatch::symmetryPlanePolyPatch
(
	const symmetryPlanePolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart),
	n_(pp.n_)
{}


// ************************************************************************* //