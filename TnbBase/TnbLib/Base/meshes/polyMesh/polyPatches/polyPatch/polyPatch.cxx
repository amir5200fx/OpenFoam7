#include <polyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <polyBoundaryMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <SubField.hxx>
#include <entry.hxx>
#include <dictionary.hxx>
#include <pointPatchField.hxx>

#include <demandDrivenData.hxx>  // added by amir


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyPatch, 0);

	int polyPatch::disallowGenericPolyPatch
	(
		debug::debugSwitch("disallowGenericPolyPatch", 0)
	);

	defineRunTimeSelectionTable(polyPatch, word);
	defineRunTimeSelectionTable(polyPatch, dictionary);

	addToRunTimeSelectionTable(polyPatch, polyPatch, word);
	addToRunTimeSelectionTable(polyPatch, polyPatch, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::polyPatch::movePoints(PstreamBuffers&, const pointField& p)
{
	primitivePatch::movePoints(p);
}

void tnbLib::polyPatch::updateMesh(PstreamBuffers&)
{
	primitivePatch::clearGeom();
	clearAddressing();
}


void tnbLib::polyPatch::clearGeom()
{
	primitivePatch::clearGeom();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyPatch::polyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	patchIdentifier(name, index),
	primitivePatch
	(
		faceSubList(bm.mesh().faces(), size, start),
		bm.mesh().points()
	),
	start_(start),
	boundaryMesh_(bm),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	if
		(
			patchType != word::null
			&& constraintType(patchType)
			&& findIndex(inGroups(), patchType) == -1
			)
	{
		inGroups().append(patchType);
	}
}


tnbLib::polyPatch::polyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	patchIdentifier(name, dict, index),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().faces(),
			readLabel(dict.lookup("nFaces")),
			readLabel(dict.lookup("startFace"))
		),
		bm.mesh().points()
	),
	start_(readLabel(dict.lookup("startFace"))),
	boundaryMesh_(bm),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	if
		(
			patchType != word::null
			&& constraintType(patchType)
			&& findIndex(inGroups(), patchType) == -1
			)
	{
		inGroups().append(patchType);
	}
}


tnbLib::polyPatch::polyPatch
(
	const polyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	patchIdentifier(pp),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().faces(),
			pp.size(),
			pp.start()
		),
		bm.mesh().points()
	),
	start_(pp.start()),
	boundaryMesh_(bm),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{}


tnbLib::polyPatch::polyPatch
(
	const polyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	patchIdentifier(pp, index),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().faces(),
			newSize,
			newStart
		),
		bm.mesh().points()
	),
	start_(newStart),
	boundaryMesh_(bm),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{}


tnbLib::polyPatch::polyPatch
(
	const polyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	patchIdentifier(pp, index),
	primitivePatch
	(
		faceSubList
		(
			bm.mesh().faces(),
			mapAddressing.size(),
			newStart
		),
		bm.mesh().points()
	),
	start_(newStart),
	boundaryMesh_(bm),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{}


tnbLib::polyPatch::polyPatch(const polyPatch& p)
	:
	patchIdentifier(p),
	primitivePatch(p),
	start_(p.start_),
	boundaryMesh_(p.boundaryMesh_),
	faceCellsPtr_(nullptr),
	mePtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::polyPatch::~polyPatch()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::polyPatch::constraintType(const word& pt)
{
	return pointPatchField<scalar>::pointPatchConstructorTablePtr_->found(pt);
}


tnbLib::wordList tnbLib::polyPatch::constraintTypes()
{
	wordList cTypes(dictionaryConstructorTablePtr_->size());

	label i = 0;

	for
		(
			dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->begin();
			cstrIter != dictionaryConstructorTablePtr_->end();
			++cstrIter
			)
	{
		if (constraintType(cstrIter.key()))
		{
			cTypes[i++] = cstrIter.key();
		}
	}

	cTypes.setSize(i);

	return cTypes;
}


const tnbLib::polyBoundaryMesh& tnbLib::polyPatch::boundaryMesh() const
{
	return boundaryMesh_;
}


const tnbLib::vectorField::subField tnbLib::polyPatch::faceCentres() const
{
	return patchSlice(boundaryMesh().mesh().faceCentres());
}


const tnbLib::vectorField::subField tnbLib::polyPatch::faceAreas() const
{
	return patchSlice(boundaryMesh().mesh().faceAreas());
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::polyPatch::faceCellCentres() const
{
	tmp<vectorField> tcc(new vectorField(size()));
	vectorField& cc = tcc.ref();

	// get reference to global cell centres
	const vectorField& gcc = boundaryMesh_.mesh().cellCentres();

	const labelUList& faceCells = this->faceCells();

	forAll(faceCells, facei)
	{
		cc[facei] = gcc[faceCells[facei]];
	}

	return tcc;
}


const tnbLib::labelUList& tnbLib::polyPatch::faceCells() const
{
	if (!faceCellsPtr_)
	{
		faceCellsPtr_ = new labelList::subList
		(
			patchSlice(boundaryMesh().mesh().faceOwner())
		);
	}

	return *faceCellsPtr_;
}


const tnbLib::labelList& tnbLib::polyPatch::meshEdges() const
{
	if (!mePtr_)
	{
		mePtr_ =
			new labelList
			(
				primitivePatch::meshEdges
				(
					boundaryMesh().mesh().edges(),
					boundaryMesh().mesh().pointEdges()
				)
			);
	}

	return *mePtr_;
}


void tnbLib::polyPatch::clearAddressing()
{
	primitivePatch::clearTopology();
	primitivePatch::clearPatchMeshAddr();
	deleteDemandDrivenData(faceCellsPtr_);
	deleteDemandDrivenData(mePtr_);
}


void tnbLib::polyPatch::write(Ostream& os) const
{
	writeEntry(os, "type", type());
	patchIdentifier::write(os);
	writeEntry(os, "nFaces", size());
	writeEntry(os, "startFace", start());
}


void tnbLib::polyPatch::initOrder(PstreamBuffers&, const primitivePatch&) const
{}


bool tnbLib::polyPatch::order
(
	PstreamBuffers&,
	const primitivePatch&,
	labelList& faceMap,
	labelList& rotation
) const
{
	// Nothing changed.
	return false;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::polyPatch::operator=(const polyPatch& p)
{
	clearAddressing();

	patchIdentifier::operator=(p);
	primitivePatch::operator=(p);
	start_ = p.start_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const polyPatch& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& os, const polyPatch& p");
	return os;
}


// ************************************************************************* //