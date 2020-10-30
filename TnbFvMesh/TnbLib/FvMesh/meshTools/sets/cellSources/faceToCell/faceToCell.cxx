#include <faceToCell.hxx>

#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, faceToCell, word);
	addToRunTimeSelectionTable(topoSetSource, faceToCell, istream);

	/*template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceToCell::faceAction,
		4
		>::names[] =
	{
		"neighbour",
		"owner",
		"any",
		"all"
	};*/
}


tnbLib::topoSetSource::addToUsageTable tnbLib::faceToCell::usage_
(
	faceToCell::typeName,
	"\n    Usage: faceToCell <faceSet> neighbour|owner|any|all\n\n"
	"    Select cells that are the owner|neighbour|any"
	" of the faces in the faceSet or where all faces are in the faceSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::faceToCell::faceAction, 4>
tnbLib::faceToCell::faceActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::faceToCell::combine(topoSet& set, const bool add) const
{
	// Load the set
	faceSet loadedSet(mesh_, setName_);


	// Handle owner/neighbour/any selection
	forAllConstIter(faceSet, loadedSet, iter)
	{
		const label facei = iter.key();

		if ((option_ == OWNER) || (option_ == ANY))
		{
			const label celli = mesh_.faceOwner()[facei];

			addOrDelete(set, celli, add);
		}

		if (mesh_.isInternalFace(facei))
		{
			if ((option_ == NEIGHBOUR) || (option_ == ANY))
			{
				const label celli = mesh_.faceNeighbour()[facei];

				addOrDelete(set, celli, add);
			}
		}
	}

	// Handle all selection.
	if (option_ == ALL)
	{
		// Count number of selected faces per cell.

		Map<label> facesPerCell(loadedSet.size());

		forAllConstIter(faceSet, loadedSet, iter)
		{
			const label facei = iter.key();
			const label own = mesh_.faceOwner()[facei];

			Map<label>::iterator fndOwn = facesPerCell.find(own);

			if (fndOwn == facesPerCell.end())
			{
				facesPerCell.insert(own, 1);
			}
			else
			{
				fndOwn()++;
			}

			if (mesh_.isInternalFace(facei))
			{
				label nei = mesh_.faceNeighbour()[facei];

				Map<label>::iterator fndNei = facesPerCell.find(nei);

				if (fndNei == facesPerCell.end())
				{
					facesPerCell.insert(nei, 1);
				}
				else
				{
					fndNei()++;
				}
			}
		}

		// Include cells that are referenced as many times as they have faces
		// -> all faces in set.
		forAllConstIter(Map<label>, facesPerCell, iter)
		{
			const label celli = iter.key();

			if (iter() == mesh_.cells()[celli].size())
			{
				addOrDelete(set, celli, add);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceToCell::faceToCell
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


tnbLib::faceToCell::faceToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(faceActionNames_.read(dict.lookup("option")))
{}


tnbLib::faceToCell::faceToCell
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

tnbLib::faceToCell::~faceToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells according to faceSet " << setName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells according to faceSet " << setName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //