#include <faceToPoint.hxx>

#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, faceToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, faceToPoint, istream);

	/*template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceToPoint::faceAction,
		1
		>::names[] =
	{
		"all"
	};*/
}


tnbLib::topoSetSource::addToUsageTable tnbLib::faceToPoint::usage_
(
	faceToPoint::typeName,
	"\n    Usage: faceToPoint <faceSet> all\n\n"
	"    Select all points of faces in the faceSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::faceToPoint::faceAction, 1>
tnbLib::faceToPoint::faceActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::faceToPoint::combine(topoSet& set, const bool add) const
{
	// Load the set
	faceSet loadedSet(mesh_, setName_);

	// Add all points from faces in loadedSet
	forAllConstIter(faceSet, loadedSet, iter)
	{
		const face& f = mesh_.faces()[iter.key()];

		forAll(f, fp)
		{
			addOrDelete(set, f[fp], add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceToPoint::faceToPoint
(
	const polyMesh& mesh,
	const word& setName,
	const faceAction option
)
	:
	topoSetSource(mesh),
	setName_(setName),
	option_(option)
{}


tnbLib::faceToPoint::faceToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(faceActionNames_.read(dict.lookup("option")))
{}


tnbLib::faceToPoint::faceToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	option_(faceActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceToPoint::~faceToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding points from face in faceSet " << setName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing points from face in faceSet " << setName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //