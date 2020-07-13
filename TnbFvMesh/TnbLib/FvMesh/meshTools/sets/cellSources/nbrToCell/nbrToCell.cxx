#include <nbrToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nbrToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, nbrToCell, word);
	addToRunTimeSelectionTable(topoSetSource, nbrToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::nbrToCell::usage_
(
	nbrToCell::typeName,
	"\n    Usage: nbrToCell <nNeighbours>\n\n"
	"    Select all cells with <= nNeighbours neighbouring cells\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nbrToCell::combine(topoSet& set, const bool add) const
{
	const cellList& cells = mesh().cells();
	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	boolList isCoupled(mesh_.nFaces() - mesh_.nInternalFaces(), false);

	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		if (pp.coupled())
		{
			label facei = pp.start();
			forAll(pp, i)
			{
				isCoupled[facei - mesh_.nInternalFaces()] = true;
				facei++;
			}
		}
	}

	forAll(cells, celli)
	{
		const cell& cFaces = cells[celli];

		label nNbrCells = 0;

		forAll(cFaces, i)
		{
			label facei = cFaces[i];

			if (mesh_.isInternalFace(facei))
			{
				nNbrCells++;
			}
			else if (isCoupled[facei - mesh_.nInternalFaces()])
			{
				nNbrCells++;
			}
		}

		if (nNbrCells <= minNbrs_)
		{
			addOrDelete(set, celli, add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nbrToCell::nbrToCell
(
	const polyMesh& mesh,
	const label minNbrs
)
	:
	topoSetSource(mesh),
	minNbrs_(minNbrs)
{}


tnbLib::nbrToCell::nbrToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	minNbrs_(readLabel(dict.lookup("neighbours")))
{}


tnbLib::nbrToCell::nbrToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	minNbrs_(readLabel(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nbrToCell::~nbrToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nbrToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells with only " << minNbrs_ << " or less"
			" neighbouring cells" << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells with only " << minNbrs_ << " or less"
			" neighbouring cells" << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //