#include <extendedCellToFaceStencil.hxx>

#include <globalIndex.hxx>
#include <syncTools.hxx>
#include <SortableList.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(extendedCellToFaceStencil, 0);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::extendedCellToFaceStencil::writeStencilStats
(
	Ostream& os,
	const labelListList& stencil,
	const mapDistribute& map
)
{
	label sumSize = 0;
	label nSum = 0;
	label minSize = labelMax;
	label maxSize = labelMin;

	forAll(stencil, i)
	{
		const labelList& sCells = stencil[i];

		if (sCells.size() > 0)
		{
			sumSize += sCells.size();
			nSum++;
			minSize = min(minSize, sCells.size());
			maxSize = max(maxSize, sCells.size());
		}
	}
	reduce(sumSize, sumOp<label>());
	reduce(nSum, sumOp<label>());

	reduce(minSize, minOp<label>());
	reduce(maxSize, maxOp<label>());

	os << "Stencil size :" << nl
		<< "    average : " << scalar(sumSize) / nSum << nl
		<< "    min     : " << minSize << nl
		<< "    max     : " << maxSize << nl
		<< endl;

	// Sum all sent data
	label nSent = 0;
	label nLocal = 0;
	forAll(map.subMap(), proci)
	{
		if (proci != Pstream::myProcNo())
		{
			nSent += map.subMap()[proci].size();
		}
		else
		{
			nLocal += map.subMap()[proci].size();
		}
	}

	os << "Local data size : " << returnReduce(nLocal, sumOp<label>()) << nl
		<< "Sent data size  : " << returnReduce(nSent, sumOp<label>()) << nl
		<< endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCellToFaceStencil::extendedCellToFaceStencil(const polyMesh& mesh)
	:
	mesh_(mesh)
{
	// Check for transformation - not supported.
	const polyBoundaryMesh& patches = mesh.boundaryMesh();

	forAll(patches, patchi)
	{
		if (patches[patchi].coupled())
		{
			const coupledPolyPatch& cpp =
				refCast<const coupledPolyPatch>(patches[patchi]);

			if (!cpp.parallel() || cpp.separated())
			{
				FatalErrorInFunction
					<< "Coupled patches with transformations not supported."
					<< endl
					<< "Problematic patch " << cpp.name() << exit(FatalError);
			}
		}
	}
}


// ************************************************************************* //