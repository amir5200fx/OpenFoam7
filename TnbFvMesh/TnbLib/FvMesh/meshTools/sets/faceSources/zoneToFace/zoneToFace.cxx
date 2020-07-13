#include <zoneToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(zoneToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, zoneToFace, word);
	addToRunTimeSelectionTable(topoSetSource, zoneToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::zoneToFace::usage_
(
	zoneToFace::typeName,
	"\n    Usage: zoneToFace zone\n\n"
	"    Select all faces in the faceZone."
	" Note:accepts wildcards for zone.\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::zoneToFace::combine(topoSet& set, const bool add) const
{
	bool hasMatched = false;

	forAll(mesh_.faceZones(), i)
	{
		const faceZone& zone = mesh_.faceZones()[i];

		if (zoneName_.match(zone.name()))
		{
			const labelList& faceLabels = mesh_.faceZones()[i];

			Info << "    Found matching zone " << zone.name()
				<< " with " << faceLabels.size() << " faces." << endl;

			hasMatched = true;

			forAll(faceLabels, i)
			{
				// Only do active faces
				if (faceLabels[i] < mesh_.nFaces())
				{
					addOrDelete(set, faceLabels[i], add);
				}
			}
		}
	}

	if (!hasMatched)
	{
		WarningInFunction
			<< "Cannot find any faceZone named " << zoneName_ << endl
			<< "Valid names are " << mesh_.faceZones().names() << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::zoneToFace::zoneToFace
(
	const polyMesh& mesh,
	const word& zoneName
)
	:
	topoSetSource(mesh),
	zoneName_(zoneName)
{}


tnbLib::zoneToFace::zoneToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	zoneName_(dict.lookup("name"))
{}


tnbLib::zoneToFace::zoneToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	zoneName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::zoneToFace::~zoneToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::zoneToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all faces of faceZone " << zoneName_ << " ..."
			<< endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all faces of faceZone " << zoneName_ << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //