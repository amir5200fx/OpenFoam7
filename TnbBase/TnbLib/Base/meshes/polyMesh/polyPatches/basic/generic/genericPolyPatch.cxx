#include <genericPolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(genericPolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, genericPolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, genericPolyPatch, dictionary);
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::genericPolyPatch::genericPolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, size, start, index, bm, patchType)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType),
	actualTypeName_(dict.lookup("type")),
	dict_(dict)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const genericPolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	actualTypeName_(pp.actualTypeName_),
	dict_(pp.dict_)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const genericPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	actualTypeName_(pp.actualTypeName_),
	dict_(pp.dict_)
{}


tnbLib::genericPolyPatch::genericPolyPatch
(
	const genericPolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart),
	actualTypeName_(pp.actualTypeName_),
	dict_(pp.dict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::genericPolyPatch::~genericPolyPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::genericPolyPatch::write(Ostream& os) const
{
	writeEntry(os, "type", actualTypeName_);
	patchIdentifier::write(os);
	writeEntry(os, "nFaces", size());
	writeEntry(os, "startFace", start());

	forAllConstIter(dictionary, dict_, iter)
	{
		if
			(
				iter().keyword() != "type"
				&& iter().keyword() != "nFaces"
				&& iter().keyword() != "startFace"
				&& iter().keyword() != "inGroups"
				&& iter().keyword() != "faces"
				)
		{
			iter().write(os);
		}
	}
}


// ************************************************************************* //