#include <setToPointZone.hxx>

#include <polyMesh.hxx>
#include <pointZoneSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(setToPointZone, 0);
	addToRunTimeSelectionTable(topoSetSource, setToPointZone, word);
	addToRunTimeSelectionTable(topoSetSource, setToPointZone, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::setToPointZone::usage_
(
	setToPointZone::typeName,
	"\n    Usage: setToPointZone <pointSet>\n\n"
	"    Select all points in the pointSet.\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setToPointZone::setToPointZone
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::setToPointZone::setToPointZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set"))
{}


tnbLib::setToPointZone::setToPointZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setToPointZone::~setToPointZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::setToPointZone::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if (!isA<pointZoneSet>(set))
	{
		WarningInFunction
			<< "Operation only allowed on a pointZoneSet." << endl;
	}
	else
	{
		pointZoneSet& fzSet = refCast<pointZoneSet>(set);

		if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
		{
			Info << "    Adding all points from pointSet " << setName_
				<< " ..." << endl;

			// Load the sets
			pointSet fSet(mesh_, setName_);

			// Start off from copy
			DynamicList<label> newAddressing(fzSet.addressing());

			forAllConstIter(pointSet, fSet, iter)
			{
				label pointi = iter.key();

				if (!fzSet.found(pointi))
				{
					newAddressing.append(pointi);
				}
			}

			fzSet.addressing().transfer(newAddressing);
			fzSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all points from pointSet " << setName_
				<< " ..." << endl;

			// Load the set
			pointSet loadedSet(mesh_, setName_);

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