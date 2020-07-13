#include <faceZoneToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceZoneToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, faceZoneToCell, word);
	addToRunTimeSelectionTable(topoSetSource, faceZoneToCell, istream);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceZoneToCell::faceAction,
		2
		>::names[] =
	{
		"master",
		"slave"
	};
}


tnbLib::topoSetSource::addToUsageTable tnbLib::faceZoneToCell::usage_
(
	faceZoneToCell::typeName,
	"\n    Usage: faceZoneToCell zone master|slave\n\n"
	"    Select master or slave side of the faceZone."
	" Note:accepts wildcards for zone.\n\n"
);


const tnbLib::NamedEnum<tnbLib::faceZoneToCell::faceAction, 2>
tnbLib::faceZoneToCell::faceActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::faceZoneToCell::combine(topoSet& set, const bool add) const
{
	bool hasMatched = false;

	forAll(mesh_.faceZones(), i)
	{
		const faceZone& zone = mesh_.faceZones()[i];

		if (zoneName_.match(zone.name()))
		{
			const labelList& cellLabels =
				(
					option_ == MASTER
					? zone.masterCells()
					: zone.slaveCells()
					);

			Info << "    Found matching zone " << zone.name()
				<< " with " << cellLabels.size() << " cells on selected side."
				<< endl;

			hasMatched = true;

			forAll(cellLabels, i)
			{
				// Only do active cells
				if (cellLabels[i] >= 0 && cellLabels[i] < mesh_.nCells())
				{
					addOrDelete(set, cellLabels[i], add);
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

tnbLib::faceZoneToCell::faceZoneToCell
(
	const polyMesh& mesh,
	const word& zoneName,
	const faceAction option
)
	:
	topoSetSource(mesh),
	zoneName_(zoneName),
	option_(option)
{}


tnbLib::faceZoneToCell::faceZoneToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	zoneName_(dict.lookup("name")),
	option_(faceActionNames_.read(dict.lookup("option")))
{}


tnbLib::faceZoneToCell::faceZoneToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	zoneName_(checkIs(is)),
	option_(faceActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceZoneToCell::~faceZoneToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceZoneToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all " << faceActionNames_[option_]
			<< " cells of faceZone " << zoneName_ << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all " << faceActionNames_[option_]
			<< " cells of faceZone " << zoneName_ << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //