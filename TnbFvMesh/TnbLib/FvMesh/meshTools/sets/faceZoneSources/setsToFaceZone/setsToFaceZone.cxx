#include <setsToFaceZone.hxx>

#include <polyMesh.hxx>
#include <faceZoneSet.hxx>
#include <cellSet.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(setsToFaceZone, 0);
	addToRunTimeSelectionTable(topoSetSource, setsToFaceZone, word);
	addToRunTimeSelectionTable(topoSetSource, setsToFaceZone, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::setsToFaceZone::usage_
(
	setsToFaceZone::typeName,
	"\n    Usage: setsToFaceZone <faceSet> <slaveCellSet>\n\n"
	"    Select all faces in the faceSet."
	" Orientated so slave side is in cellSet.\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setsToFaceZone::setsToFaceZone
(
	const polyMesh& mesh,
	const word& faceSetName,
	const word& cellSetName,
	const Switch& flip
)
	:
	topoSetSource(mesh),
	faceSetName_(faceSetName),
	cellSetName_(cellSetName),
	flip_(flip)
{}


tnbLib::setsToFaceZone::setsToFaceZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	faceSetName_(dict.lookup("faceSet")),
	cellSetName_(dict.lookup("cellSet")),
	flip_(dict.lookupOrDefault("flip", false))
{}


tnbLib::setsToFaceZone::setsToFaceZone
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	faceSetName_(checkIs(is)),
	cellSetName_(checkIs(is)),
	flip_(false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setsToFaceZone::~setsToFaceZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::setsToFaceZone::applyToSet
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
			Info << "    Adding all faces from faceSet " << faceSetName_
				<< " ..." << endl;

			// Load the sets
			faceSet fSet(mesh_, faceSetName_);
			cellSet cSet(mesh_, cellSetName_);

			// Start off from copy
			DynamicList<label> newAddressing(fzSet.addressing());
			DynamicList<bool> newFlipMap(fzSet.flipMap());

			forAllConstIter(faceSet, fSet, iter)
			{
				label facei = iter.key();

				if (!fzSet.found(facei))
				{
					bool flipFace = false;

					label own = mesh_.faceOwner()[facei];
					bool ownFound = cSet.found(own);

					if (mesh_.isInternalFace(facei))
					{
						label nei = mesh_.faceNeighbour()[facei];
						bool neiFound = cSet.found(nei);

						if (ownFound && !neiFound)
						{
							flipFace = false;
						}
						else if (!ownFound && neiFound)
						{
							flipFace = true;
						}
						else
						{
							WarningInFunction
								<< "One of owner or neighbour of internal face "
								<< facei << " should be in cellSet "
								<< cSet.name()
								<< " to be able to determine orientation."
								<< endl
								<< "Face:" << facei << " own:" << own
								<< " OwnInCellSet:" << ownFound
								<< " nei:" << nei
								<< " NeiInCellSet:" << neiFound
								<< endl;
						}
					}
					else
					{
						flipFace = !ownFound;
					}


					if (flip_)
					{
						flipFace = !flipFace;
					}

					newAddressing.append(facei);
					newFlipMap.append(flipFace);
				}
			}

			fzSet.addressing().transfer(newAddressing);
			fzSet.flipMap().transfer(newFlipMap);
			fzSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all faces from faceSet " << faceSetName_
				<< " ..." << endl;

			// Load the set
			faceZoneSet loadedSet(mesh_, faceSetName_);

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