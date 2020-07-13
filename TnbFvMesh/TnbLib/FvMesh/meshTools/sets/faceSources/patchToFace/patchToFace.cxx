#include <patchToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(patchToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, patchToFace, word);
	addToRunTimeSelectionTable(topoSetSource, patchToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::patchToFace::usage_
(
	patchToFace::typeName,
	"\n    Usage: patchToFace patch\n\n"
	"    Select all faces in the patch. Note:accepts wildcards for patch.\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::patchToFace::combine(topoSet& set, const bool add) const
{
	labelHashSet patchIDs = mesh_.boundaryMesh().patchSet
	(
		List<wordRe>(1, patchName_),
		true,           // warn if not found
		true            // use patch groups if available
	);

	forAllConstIter(labelHashSet, patchIDs, iter)
	{
		label patchi = iter.key();

		const polyPatch& pp = mesh_.boundaryMesh()[patchi];

		Info << "    Found matching patch " << pp.name()
			<< " with " << pp.size() << " faces." << endl;

		for
			(
				label facei = pp.start();
				facei < pp.start() + pp.size();
				facei++
				)
		{
			addOrDelete(set, facei, add);
		}
	}

	if (patchIDs.empty())
	{
		WarningInFunction
			<< "Cannot find any patch named " << patchName_ << endl
			<< "Valid names are " << mesh_.boundaryMesh().names() << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchToFace::patchToFace
(
	const polyMesh& mesh,
	const word& patchName
)
	:
	topoSetSource(mesh),
	patchName_(patchName)
{}


tnbLib::patchToFace::patchToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	patchName_(dict.lookup("name"))
{}


tnbLib::patchToFace::patchToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	patchName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchToFace::~patchToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::patchToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all faces of patch " << patchName_ << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all faces of patch " << patchName_ << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //