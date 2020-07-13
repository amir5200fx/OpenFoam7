#include <cellToCell.hxx>

#include <polyMesh.hxx>
#include <cellSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, cellToCell, word);
	addToRunTimeSelectionTable(topoSetSource, cellToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::cellToCell::usage_
(
	cellToCell::typeName,
	"\n    Usage: cellToCell <cellSet>\n\n"
	"    Select all cells in the cellSet\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellToCell::cellToCell
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::cellToCell::cellToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set"))
{}


tnbLib::cellToCell::cellToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellToCell::~cellToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cellToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::ADD) || (action == topoSetSource::NEW))
	{
		Info << "    Adding all elements of cellSet " << setName_ << " ..."
			<< endl;

		// Load the set
		cellSet loadedSet(mesh_, setName_);

		set.addSet(loadedSet);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all elements of cellSet " << setName_ << " ..."
			<< endl;

		// Load the set
		cellSet loadedSet(mesh_, setName_);

		set.deleteSet(loadedSet);
	}
}


// ************************************************************************* //