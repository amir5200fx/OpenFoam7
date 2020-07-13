#include <cellToFace.hxx>

#include <polyMesh.hxx>
#include <cellSet.hxx>
#include <Time.hxx>
#include <syncTools.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, cellToFace, word);
	addToRunTimeSelectionTable(topoSetSource, cellToFace, istream);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::cellToFace::cellAction,
		2
		>::names[] =
	{
		"all",
		"both"
	};
}


tnbLib::topoSetSource::addToUsageTable tnbLib::cellToFace::usage_
(
	cellToFace::typeName,
	"\n    Usage: cellToFace <cellSet> all|both\n\n"
	"    Select -all : all faces of cells in the cellSet\n"
	"           -both: faces where both neighbours are in the cellSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::cellToFace::cellAction, 2>
tnbLib::cellToFace::cellActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::cellToFace::combine(topoSet& set, const bool add) const
{
	// Load the set
	if (!exists(mesh_.time().path() / topoSet::localPath(mesh_, setName_)))
	{
		SeriousError << "Cannot load set "
			<< setName_ << endl;
	}

	cellSet loadedSet(mesh_, setName_);

	if (option_ == ALL)
	{
		// Add all faces from cell
		forAllConstIter(cellSet, loadedSet, iter)
		{
			const label celli = iter.key();
			const labelList& cFaces = mesh_.cells()[celli];

			forAll(cFaces, cFacei)
			{
				addOrDelete(set, cFaces[cFacei], add);
			}
		}
	}
	else if (option_ == BOTH)
	{
		// Add all faces whose both neighbours are in set.

		const label nInt = mesh_.nInternalFaces();
		const labelList& own = mesh_.faceOwner();
		const labelList& nei = mesh_.faceNeighbour();
		const polyBoundaryMesh& patches = mesh_.boundaryMesh();


		// Check all internal faces
		for (label facei = 0; facei < nInt; facei++)
		{
			if (loadedSet.found(own[facei]) && loadedSet.found(nei[facei]))
			{
				addOrDelete(set, facei, add);
			}
		}


		// Get coupled cell status
		boolList neiInSet(mesh_.nFaces() - nInt, false);

		forAll(patches, patchi)
		{
			const polyPatch& pp = patches[patchi];

			if (pp.coupled())
			{
				label facei = pp.start();
				forAll(pp, i)
				{
					neiInSet[facei - nInt] = loadedSet.found(own[facei]);
					facei++;
				}
			}
		}
		syncTools::swapBoundaryFaceList(mesh_, neiInSet);


		// Check all boundary faces
		forAll(patches, patchi)
		{
			const polyPatch& pp = patches[patchi];

			if (pp.coupled())
			{
				label facei = pp.start();
				forAll(pp, i)
				{
					if (loadedSet.found(own[facei]) && neiInSet[facei - nInt])
					{
						addOrDelete(set, facei, add);
					}
					facei++;
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellToFace::cellToFace
(
	const polyMesh& mesh,
	const word& setName,
	const cellAction option
)
	:
	topoSetSource(mesh),
	setName_(setName),
	option_(option)
{}


tnbLib::cellToFace::cellToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(cellActionNames_.read(dict.lookup("option")))
{}


tnbLib::cellToFace::cellToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	option_(cellActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellToFace::~cellToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cellToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces according to cellSet " << setName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces according to cellSet " << setName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //