#include <setAndNormalToFaceZone.hxx>

#include <polyMesh.hxx>
#include <faceZoneSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(setAndNormalToFaceZone, 0);

	addToRunTimeSelectionTable(topoSetSource, setAndNormalToFaceZone, word);

	addToRunTimeSelectionTable(topoSetSource, setAndNormalToFaceZone, istream);

}


tnbLib::topoSetSource::addToUsageTable tnbLib::setAndNormalToFaceZone::usage_
(
	setAndNormalToFaceZone::typeName,
	"\n    Usage: setAndNormalToFaceZone <faceSet> <normal>\n\n"
	"    Select all faces in the faceSet and orient using normal.\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setAndNormalToFaceZone::setAndNormalToFaceZone
(
	const polyMesh& mesh,
	const word& setName,
	const vector& normal
)
	:
	topoSetSource(mesh),
	setName_(setName),
	normal_(normal)
{}


tnbLib::setAndNormalToFaceZone::setAndNormalToFaceZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("faceSet")),
	normal_(dict.lookup("normal"))
{}


tnbLib::setAndNormalToFaceZone::setAndNormalToFaceZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	normal_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setAndNormalToFaceZone::~setAndNormalToFaceZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::setAndNormalToFaceZone::applyToSet
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

			const faceList& faces = mesh_.faces();
			const pointField& points = mesh_.points();

			forAllConstIter(faceSet, fSet, iter)
			{
				label facei = iter.key();

				if (!fzSet.found(facei))
				{
					newAddressing.append(facei);

					const vector a = faces[facei].area(points);
					if ((a & normal_) > 0)
					{
						newFlipMap.append(false);
					}
					else
					{
						newFlipMap.append(true);
					}
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