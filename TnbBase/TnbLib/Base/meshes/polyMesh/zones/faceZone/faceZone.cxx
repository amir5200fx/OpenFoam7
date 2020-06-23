#include <faceZone.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <faceZoneMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <demandDrivenData.hxx>
#include <mapPolyMesh.hxx>
#include <syncTools.hxx>

#include <PstreamReduceOps.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceZone, 0);
	defineRunTimeSelectionTable(faceZone, dictionary);
	addToRunTimeSelectionTable(faceZone, faceZone, dictionary);
}

const char* const tnbLib::faceZone::labelsName = "faceLabels";


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::faceZone::calcFaceZonePatch() const
{
	if (debug)
	{
		InfoInFunction << "Calculating primitive patch" << endl;
	}

	if (patchPtr_)
	{
		FatalErrorInFunction
			<< "primitive face zone patch already calculated"
			<< abort(FatalError);
	}

	patchPtr_ =
		new primitiveFacePatch
		(
			faceList(size()),
			zoneMesh().mesh().points()
		);

	primitiveFacePatch& patch = *patchPtr_;

	const faceList& f = zoneMesh().mesh().faces();

	const labelList& addr = *this;
	const boolList& flip = flipMap();

	forAll(addr, facei)
	{
		if (flip[facei])
		{
			patch[facei] = f[addr[facei]].reverseFace();
		}
		else
		{
			patch[facei] = f[addr[facei]];
		}
	}

	if (debug)
	{
		InfoInFunction << "Finished calculating primitive patch" << endl;
	}
}


void tnbLib::faceZone::calcCellLayers() const
{
	if (debug)
	{
		InfoInFunction << "Calculating master cells" << endl;
	}

	// It is an error to attempt to recalculate edgeCells
	// if the pointer is already set
	if (masterCellsPtr_ || slaveCellsPtr_)
	{
		FatalErrorInFunction
			<< "cell layers already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Go through all the faces in the master zone.  Choose the
		// master or slave cell based on the face flip

		const labelList& own = zoneMesh().mesh().faceOwner();
		const labelList& nei = zoneMesh().mesh().faceNeighbour();

		const labelList& mf = *this;

		const boolList& faceFlip = flipMap();

		masterCellsPtr_ = new labelList(mf.size());
		labelList& mc = *masterCellsPtr_;

		slaveCellsPtr_ = new labelList(mf.size());
		labelList& sc = *slaveCellsPtr_;

		forAll(mf, facei)
		{
			label ownCelli = own[mf[facei]];
			label neiCelli =
				(
					zoneMesh().mesh().isInternalFace(mf[facei])
					? nei[mf[facei]]
					: -1
					);

			if (!faceFlip[facei])
			{
				// Face is oriented correctly, no flip needed
				mc[facei] = neiCelli;
				sc[facei] = ownCelli;
			}
			else
			{
				mc[facei] = ownCelli;
				sc[facei] = neiCelli;
			}
		}
	}
}


void tnbLib::faceZone::checkAddressing() const
{
	if (size() != flipMap_.size())
	{
		FatalErrorInFunction
			<< "Size of addressing: " << size()
			<< " size of flip map: " << flipMap_.size()
			<< abort(FatalError);
	}

	const labelList& mf = *this;

	// Note: nFaces, nCells might not be set yet on mesh so use owner size
	const label nFaces = zoneMesh().mesh().faceOwner().size();

	bool hasWarned = false;
	forAll(mf, i)
	{
		if (!hasWarned && (mf[i] < 0 || mf[i] >= nFaces))
		{
			WarningInFunction
				<< "Illegal face index " << mf[i] << " outside range 0.."
				<< nFaces - 1 << endl;
			hasWarned = true;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceZone::faceZone
(
	const word& name,
	const labelUList& addr,
	const boolList& fm,
	const label index,
	const faceZoneMesh& zm
)
	:
	zone(name, addr, index),
	flipMap_(fm),
	zoneMesh_(zm),
	patchPtr_(nullptr),
	masterCellsPtr_(nullptr),
	slaveCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	checkAddressing();
}


tnbLib::faceZone::faceZone
(
	const word& name,
	labelList&& addr,
	boolList&& fm,
	const label index,
	const faceZoneMesh& zm
)
	:
	zone(name, move(addr), index),
	flipMap_(move(fm)),
	zoneMesh_(zm),
	patchPtr_(nullptr),
	masterCellsPtr_(nullptr),
	slaveCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	checkAddressing();
}


tnbLib::faceZone::faceZone
(
	const word& name,
	const dictionary& dict,
	const label index,
	const faceZoneMesh& zm
)
	:
	zone(name, dict, this->labelsName, index),
	flipMap_(dict.lookup("flipMap")),
	zoneMesh_(zm),
	patchPtr_(nullptr),
	masterCellsPtr_(nullptr),
	slaveCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	checkAddressing();
}


tnbLib::faceZone::faceZone
(
	const faceZone& fz,
	const labelUList& addr,
	const boolList& fm,
	const label index,
	const faceZoneMesh& zm
)
	:
	zone(fz, addr, index),
	flipMap_(fm),
	zoneMesh_(zm),
	patchPtr_(nullptr),
	masterCellsPtr_(nullptr),
	slaveCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	checkAddressing();
}


tnbLib::faceZone::faceZone
(
	const faceZone& fz,
	labelList&& addr,
	boolList&& fm,
	const label index,
	const faceZoneMesh& zm
)
	:
	zone(fz, move(addr), index),
	flipMap_(move(fm)),
	zoneMesh_(zm),
	patchPtr_(nullptr),
	masterCellsPtr_(nullptr),
	slaveCellsPtr_(nullptr),
	mePtr_(nullptr)
{
	checkAddressing();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceZone::~faceZone()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::faceZoneMesh& tnbLib::faceZone::zoneMesh() const
{
	return zoneMesh_;
}


tnbLib::label tnbLib::faceZone::whichFace(const label globalFaceID) const
{
	return zone::localID(globalFaceID);
}


const tnbLib::primitiveFacePatch& tnbLib::faceZone::operator()() const
{
	if (!patchPtr_)
	{
		calcFaceZonePatch();
	}

	return *patchPtr_;
}


const tnbLib::labelList& tnbLib::faceZone::masterCells() const
{
	if (!masterCellsPtr_)
	{
		calcCellLayers();
	}

	return *masterCellsPtr_;
}


const tnbLib::labelList& tnbLib::faceZone::slaveCells() const
{
	if (!slaveCellsPtr_)
	{
		calcCellLayers();
	}

	return *slaveCellsPtr_;
}


const tnbLib::labelList& tnbLib::faceZone::meshEdges() const
{
	if (!mePtr_)
	{
		mePtr_ =
			new labelList
			(
				operator()().meshEdges
				(
					zoneMesh().mesh().edges(),
					zoneMesh().mesh().pointEdges()
				)
			);
	}

	return *mePtr_;
}


void tnbLib::faceZone::clearAddressing()
{
	zone::clearAddressing();

	deleteDemandDrivenData(patchPtr_);

	deleteDemandDrivenData(masterCellsPtr_);
	deleteDemandDrivenData(slaveCellsPtr_);

	deleteDemandDrivenData(mePtr_);
}


void tnbLib::faceZone::resetAddressing
(
	const labelUList& addr,
	const boolList& flipMap
)
{
	clearAddressing();
	labelList::operator=(addr);
	flipMap_ = flipMap;
}


void tnbLib::faceZone::updateMesh(const mapPolyMesh& mpm)
{
	clearAddressing();

	labelList newAddressing(size());
	boolList newFlipMap(flipMap_.size());
	label nFaces = 0;

	const labelList& faceMap = mpm.reverseFaceMap();

	forAll(*this, i)
	{
		const label facei = operator[](i);

		if (faceMap[facei] >= 0)
		{
			newAddressing[nFaces] = faceMap[facei];
			newFlipMap[nFaces] = flipMap_[i];       // Keep flip map.
			nFaces++;
		}
	}

	newAddressing.setSize(nFaces);
	newFlipMap.setSize(nFaces);

	transfer(newAddressing);
	flipMap_.transfer(newFlipMap);
}


bool tnbLib::faceZone::checkDefinition(const bool report) const
{
	return zone::checkDefinition(zoneMesh().mesh().faces().size(), report);
}


bool tnbLib::faceZone::checkParallelSync(const bool report) const
{
	const polyMesh& mesh = zoneMesh().mesh();
	const polyBoundaryMesh& bm = mesh.boundaryMesh();

	bool hasError = false;


	// Check that zone faces are synced
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	{
		boolList neiZoneFace(mesh.nFaces() - mesh.nInternalFaces(), false);
		boolList neiZoneFlip(mesh.nFaces() - mesh.nInternalFaces(), false);
		forAll(*this, i)
		{
			const label facei = operator[](i);

			if (!mesh.isInternalFace(facei))
			{
				neiZoneFace[facei - mesh.nInternalFaces()] = true;
				neiZoneFlip[facei - mesh.nInternalFaces()] = flipMap()[i];
			}
		}
		boolList myZoneFace(neiZoneFace);
		syncTools::swapBoundaryFaceList(mesh, neiZoneFace);
		boolList myZoneFlip(neiZoneFlip);
		syncTools::swapBoundaryFaceList(mesh, neiZoneFlip);

		forAll(*this, i)
		{
			const label facei = operator[](i);
			const label patchi = bm.whichPatch(facei);

			if (patchi != -1 && bm[patchi].coupled())
			{
				const label bFacei = facei - mesh.nInternalFaces();

				// Check face in zone on both sides
				if (myZoneFace[bFacei] != neiZoneFace[bFacei])
				{
					hasError = true;

					if (report)
					{
						Pout << " ***Problem with faceZone " << index()
							<< " named " << name()
							<< ". Face " << facei
							<< " on coupled patch "
							<< bm[patchi].name()
							<< " is not consistent with its coupled neighbour."
							<< endl;
					}
					else
					{
						// w/o report - can stop checking now
						break;
					}
				}
				else if (myZoneFlip[bFacei] == neiZoneFlip[bFacei])
				{
					// Flip state should be opposite.
					hasError = true;

					if (report)
					{
						Pout << " ***Problem with faceZone " << index()
							<< " named " << name()
							<< ". Face " << facei
							<< " on coupled patch "
							<< bm[patchi].name()
							<< " does not have consistent flipMap"
							<< " across coupled faces."
							<< endl;
					}
					else
					{
						// w/o report - can stop checking now
						break;
					}
				}
			}
		}
	}

	return returnReduce(hasError, orOp<bool>());
}


void tnbLib::faceZone::movePoints(const pointField& p)
{
	if (patchPtr_)
	{
		patchPtr_->movePoints(p);
	}
}

void tnbLib::faceZone::write(Ostream& os) const
{
	os << nl << name()
		<< nl << static_cast<const labelList&>(*this)
		<< nl << flipMap();
}


void tnbLib::faceZone::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << nl
		<< "    type " << type() << token::END_STATEMENT << nl;

	writeEntry(os, this->labelsName, *this);
	writeEntry(os, "flipMap", flipMap());

	os << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::faceZone::operator=(const faceZone& zn)
{
	clearAddressing();
	zone::operator=(zn);
	flipMap_ = zn.flipMap_;
}


void tnbLib::faceZone::operator=(faceZone&& zn)
{
	clearAddressing();
	zone::operator=(move(zn));
	flipMap_ = move(zn.flipMap_);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const faceZone& zn)
{
	zn.write(os);
	os.check("Ostream& operator<<(Ostream&, const faceZone&");
	return os;
}


// ************************************************************************* //