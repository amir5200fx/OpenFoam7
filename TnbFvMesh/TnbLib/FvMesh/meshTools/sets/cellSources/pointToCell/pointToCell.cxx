#include <pointToCell.hxx>

#include <polyMesh.hxx>
#include <pointSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, pointToCell, word);
	addToRunTimeSelectionTable(topoSetSource, pointToCell, istream);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::pointToCell::pointAction,
		2
		>::names[] =
	{
		"any",
		"edge"
	};
}


tnbLib::topoSetSource::addToUsageTable tnbLib::pointToCell::usage_
(
	pointToCell::typeName,
	"\n    Usage: pointToCell <pointSet> any|edge\n\n"
	"    Select all cells with any point ('any') or any edge ('edge')"
	" in the pointSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::pointToCell::pointAction, 2>
tnbLib::pointToCell::pointActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointToCell::combine(topoSet& set, const bool add) const
{
	// Load the set
	pointSet loadedSet(mesh_, setName_);


	// Handle any selection
	if (option_ == ANY)
	{
		forAllConstIter(pointSet, loadedSet, iter)
		{
			const label pointi = iter.key();
			const labelList& pCells = mesh_.pointCells()[pointi];

			forAll(pCells, pCelli)
			{
				addOrDelete(set, pCells[pCelli], add);
			}
		}
	}
	else if (option_ == EDGE)
	{
		const faceList& faces = mesh_.faces();
		forAll(faces, facei)
		{
			const face& f = faces[facei];

			forAll(f, fp)
			{
				if (loadedSet.found(f[fp]) && loadedSet.found(f.nextLabel(fp)))
				{
					addOrDelete(set, mesh_.faceOwner()[facei], add);
					if (mesh_.isInternalFace(facei))
					{
						addOrDelete(set, mesh_.faceNeighbour()[facei], add);
					}
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointToCell::pointToCell
(
	const polyMesh& mesh,
	const word& setName,
	const pointAction option
)
	:
	topoSetSource(mesh),
	setName_(setName),
	option_(option)
{}


tnbLib::pointToCell::pointToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(pointActionNames_.read(dict.lookup("option")))
{}


tnbLib::pointToCell::pointToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	option_(pointActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointToCell::~pointToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells according to pointSet " << setName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells according to pointSet " << setName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //