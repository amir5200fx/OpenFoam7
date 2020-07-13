#include <faceZoneToFaceZone.hxx>

#include <polyMesh.hxx>
#include <faceZoneSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceZoneToFaceZone, 0);
	addToRunTimeSelectionTable(topoSetSource, faceZoneToFaceZone, word);
	addToRunTimeSelectionTable(topoSetSource, faceZoneToFaceZone, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::faceZoneToFaceZone::usage_
(
	faceZoneToFaceZone::typeName,
	"\n    Usage: faceZoneToFaceZone <faceZone>\n\n"
	"    Select all faces in the faceZone\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceZoneToFaceZone::faceZoneToFaceZone
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::faceZoneToFaceZone::faceZoneToFaceZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("zone"))
{}


tnbLib::faceZoneToFaceZone::faceZoneToFaceZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceZoneToFaceZone::~faceZoneToFaceZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceZoneToFaceZone::applyToSet
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
		faceZoneSet& fSet = refCast<faceZoneSet>(set);

		if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
		{
			Info << "    Adding all faces from faceZone " << setName_ << " ..."
				<< endl;

			// Load the set
			faceZoneSet loadedSet(mesh_, setName_);

			DynamicList<label> newAddressing(fSet.addressing());
			DynamicList<bool> newFlipMap(fSet.flipMap());

			forAll(loadedSet.addressing(), i)
			{
				if (!fSet.found(loadedSet.addressing()[i]))
				{
					newAddressing.append(loadedSet.addressing()[i]);
					newFlipMap.append(loadedSet.flipMap()[i]);
				}
			}
			fSet.addressing().transfer(newAddressing);
			fSet.flipMap().transfer(newFlipMap);
			fSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all faces from faceZone " << setName_ << " ..."
				<< endl;

			// Load the set
			faceZoneSet loadedSet(mesh_, setName_);

			DynamicList<label> newAddressing(fSet.addressing().size());
			DynamicList<bool> newFlipMap(fSet.flipMap().size());

			forAll(fSet.addressing(), i)
			{
				if (!loadedSet.found(fSet.addressing()[i]))
				{
					newAddressing.append(fSet.addressing()[i]);
					newFlipMap.append(fSet.flipMap()[i]);
				}
			}
			fSet.addressing().transfer(newAddressing);
			fSet.flipMap().transfer(newFlipMap);
			fSet.updateSet();
		}
	}
}


// ************************************************************************* //