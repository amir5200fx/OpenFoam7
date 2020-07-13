#include <setToCellZone.hxx>

#include <polyMesh.hxx>
#include <cellZoneSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(setToCellZone, 0);
	addToRunTimeSelectionTable(topoSetSource, setToCellZone, word);
	addToRunTimeSelectionTable(topoSetSource, setToCellZone, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::setToCellZone::usage_
(
	setToCellZone::typeName,
	"\n    Usage: setToCellZone <cellSet>\n\n"
	"    Select all cells in the cellSet.\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setToCellZone::setToCellZone
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::setToCellZone::setToCellZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set"))
{}


tnbLib::setToCellZone::setToCellZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setToCellZone::~setToCellZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::setToCellZone::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if (!isA<cellZoneSet>(set))
	{
		WarningInFunction
			<< "Operation only allowed on a cellZoneSet." << endl;
	}
	else
	{
		cellZoneSet& fzSet = refCast<cellZoneSet>(set);

		if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
		{
			Info << "    Adding all cells from cellSet " << setName_
				<< " ..." << endl;

			// Load the sets
			cellSet fSet(mesh_, setName_);

			// Start off from copy
			DynamicList<label> newAddressing(fzSet.addressing());

			forAllConstIter(cellSet, fSet, iter)
			{
				label celli = iter.key();

				if (!fzSet.found(celli))
				{
					newAddressing.append(celli);
				}
			}

			fzSet.addressing().transfer(newAddressing);
			fzSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all cells from cellSet " << setName_
				<< " ..." << endl;

			// Load the set
			cellSet loadedSet(mesh_, setName_);

			// Start off empty
			DynamicList<label> newAddressing(fzSet.addressing().size());

			forAll(fzSet.addressing(), i)
			{
				if (!loadedSet.found(fzSet.addressing()[i]))
				{
					newAddressing.append(fzSet.addressing()[i]);
				}
			}
			fzSet.addressing().transfer(newAddressing);
			fzSet.updateSet();
		}
	}
}


// ************************************************************************* //