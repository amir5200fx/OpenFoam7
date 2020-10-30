#include <cellToPoint.hxx>

#include <polyMesh.hxx>
#include <cellSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, cellToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, cellToPoint, istream);

	/*template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::cellToPoint::cellAction,
		1
		>::names[] =
	{
		"all"
	};*/
}


tnbLib::topoSetSource::addToUsageTable tnbLib::cellToPoint::usage_
(
	cellToPoint::typeName,
	"\n    Usage: cellToPoint <cellSet> all\n\n"
	"    Select all points of cells in the cellSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::cellToPoint::cellAction, 1>
tnbLib::cellToPoint::cellActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::cellToPoint::combine(topoSet& set, const bool add) const
{
	// Load the set
	cellSet loadedSet(mesh_, setName_);

	// Add all point from cells in loadedSet
	forAllConstIter(cellSet, loadedSet, iter)
	{
		const label celli = iter.key();
		const labelList& cFaces = mesh_.cells()[celli];

		forAll(cFaces, cFacei)
		{
			const face& f = mesh_.faces()[cFaces[cFacei]];

			forAll(f, fp)
			{
				addOrDelete(set, f[fp], add);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellToPoint::cellToPoint
(
	const polyMesh& mesh,
	const word& setName,
	const cellAction option
)
	:
	topoSetSource(mesh),
	setName_(setName),
	option_(option)
{}


tnbLib::cellToPoint::cellToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(cellActionNames_.read(dict.lookup("option")))
{}


tnbLib::cellToPoint::cellToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	option_(cellActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellToPoint::~cellToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cellToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding from " << setName_ << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing from " << setName_ << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //