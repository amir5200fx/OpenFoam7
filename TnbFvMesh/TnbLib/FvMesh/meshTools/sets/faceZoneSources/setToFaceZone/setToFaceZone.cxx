#include <setToFaceZone.hxx>

#include <polyMesh.hxx>
#include <faceZoneSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(setToFaceZone, 0);
	addToRunTimeSelectionTable(topoSetSource, setToFaceZone, word);
	addToRunTimeSelectionTable(topoSetSource, setToFaceZone, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::setToFaceZone::usage_
(
	setToFaceZone::typeName,
	"\n    Usage: setToFaceZone <faceSet>\n\n"
	"    Select all faces in the faceSet."
	" Sets flipMap.\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setToFaceZone::setToFaceZone
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::setToFaceZone::setToFaceZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("faceSet"))
{}


tnbLib::setToFaceZone::setToFaceZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setToFaceZone::~setToFaceZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::setToFaceZone::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if (!isA<faceZoneSet>(set))
	{
		WarningInFunction
			<< "Operation only allowed on a faceZoneSet." << endl;
	}
	else
	{
		faceZoneSet& fzSet = refCast<faceZoneSet>(set);

		if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
		{
			Info << "    Adding all faces from faceSet " << setName_
				<< " ..." << endl;

			// Load the sets
			faceSet fSet(mesh_, setName_);

			// Start off from copy
			DynamicList<label> newAddressing(fzSet.addressing());
			DynamicList<bool> newFlipMap(fzSet.flipMap());

			forAllConstIter(faceSet, fSet, iter)
			{
				label facei = iter.key();

				if (!fzSet.found(facei))
				{
					newAddressing.append(facei);
					newFlipMap.append(false);
				}
			}

			fzSet.addressing().transfer(newAddressing);
			fzSet.flipMap().transfer(newFlipMap);
			fzSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all faces from faceSet " << setName_
				<< " ..." << endl;

			// Load the set
			faceSet loadedSet(mesh_, setName_);

			// Start off empty
			DynamicList<label> newAddressing(fzSet.addressing().size());
			DynamicList<bool> newFlipMap(fzSet.flipMap().size());

			forAll(fzSet.addressing(), i)
			{
				if (!loadedSet.found(fzSet.addressing()[i]))
				{
					newAddressing.append(fzSet.addressing()[i]);
					newFlipMap.append(fzSet.flipMap()[i]);
				}
			}
			fzSet.addressing().transfer(newAddressing);
			fzSet.flipMap().transfer(newFlipMap);
			fzSet.updateSet();
		}
	}
}


// ************************************************************************* //