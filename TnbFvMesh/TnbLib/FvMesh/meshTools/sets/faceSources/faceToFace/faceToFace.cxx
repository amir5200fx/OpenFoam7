#include <faceToFace.hxx>

#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, faceToFace, word);
	addToRunTimeSelectionTable(topoSetSource, faceToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::faceToFace::usage_
(
	faceToFace::typeName,
	"\n    Usage: faceToFace <faceSet>\n\n"
	"    Select all faces in the faceSet\n\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceToFace::faceToFace
(
	const polyMesh& mesh,
	const word& setName
)
	:
	topoSetSource(mesh),
	setName_(setName)
{}


tnbLib::faceToFace::faceToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set"))
{}


tnbLib::faceToFace::faceToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceToFace::~faceToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all faces from faceSet " << setName_ << " ..."
			<< endl;

		// Load the set
		faceSet loadedSet(mesh_, setName_);

		set.addSet(loadedSet);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all faces from faceSet " << setName_ << " ..."
			<< endl;

		// Load the set
		faceSet loadedSet(mesh_, setName_);

		set.deleteSet(loadedSet);
	}
}


// ************************************************************************* //