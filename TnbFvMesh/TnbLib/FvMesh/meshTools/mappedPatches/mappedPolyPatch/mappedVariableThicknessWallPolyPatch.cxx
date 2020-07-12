#include <mappedVariableThicknessWallPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedVariableThicknessWallPolyPatch, 0);

	addToRunTimeSelectionTable
	(
		polyPatch,
		mappedVariableThicknessWallPolyPatch,
		word
	);

	addToRunTimeSelectionTable
	(
		polyPatch,
		mappedVariableThicknessWallPolyPatch,
		dictionary
	);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	mappedWallPolyPatch(name, size, start, index, bm, patchType),
	thickness_(size)
{}


tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const word& sampleRegion,
	const mappedPatchBase::sampleMode mode,
	const word& samplePatch,
	const vectorField& offset,
	const polyBoundaryMesh& bm
)
	:
	mappedWallPolyPatch(name, size, start, index, bm, typeName),
	thickness_(size)
{}


tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const word& sampleRegion,
	const mappedPatchBase::sampleMode mode,
	const word& samplePatch,
	const vector& offset,
	const polyBoundaryMesh& bm
)
	:
	mappedWallPolyPatch(name, size, start, index, bm, typeName),
	thickness_(size)
{}


tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	mappedWallPolyPatch(name, dict, index, bm, patchType),
	thickness_(scalarField("thickness", dict, this->size()))
{}


tnbLib::mappedVariableThicknessWallPolyPatch::
mappedVariableThicknessWallPolyPatch
(
	const mappedVariableThicknessWallPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	mappedWallPolyPatch(pp, bm),
	thickness_(pp.thickness_)
{}


tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const mappedVariableThicknessWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	mappedWallPolyPatch(pp, bm, index, newSize, newStart),
	thickness_(newSize)
{}


tnbLib::mappedVariableThicknessWallPolyPatch::mappedVariableThicknessWallPolyPatch
(
	const mappedVariableThicknessWallPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	mappedWallPolyPatch(pp, bm, index, mapAddressing, newStart),
	thickness_(pp.size())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::mappedVariableThicknessWallPolyPatch::
~mappedVariableThicknessWallPolyPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedVariableThicknessWallPolyPatch::
write(tnbLib::Ostream& os) const
{
	writeEntry(os, "thickness", thickness_);
}


// ************************************************************************* //