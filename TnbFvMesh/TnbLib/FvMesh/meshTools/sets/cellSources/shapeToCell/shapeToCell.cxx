#include <shapeToCell.hxx>

#include <polyMesh.hxx>
#include <unitConversion.hxx>
#include <hexMatcher.hxx>
#include <cellFeatures.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(shapeToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, shapeToCell, word);
	addToRunTimeSelectionTable(topoSetSource, shapeToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::shapeToCell::usage_
(
	shapeToCell::typeName,
	"\n    Usage: shapeToCell tet|pyr|prism|hex|tetWedge|wedge|splitHex\n\n"
	"    Select all cells of given cellShape.\n"
	"    (splitHex hardcoded with internal angle < 10 degrees)\n"
);


// Angle for polys to be considered splitHexes.
tnbLib::scalar tnbLib::shapeToCell::featureCos = tnbLib::cos(degToRad(10.0));


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::shapeToCell::combine(topoSet& set, const bool add) const
{
	if (type_ == "splitHex")
	{
		for (label celli = 0; celli < mesh_.nCells(); celli++)
		{
			cellFeatures superCell(mesh_, featureCos, celli);

			if (hexMatcher().isA(superCell.faces()))
			{
				addOrDelete(set, celli, add);
			}
		}
	}
	else
	{
		const cellModel& wantedModel = *(cellModeller::lookup(type_));

		const cellShapeList& cellShapes = mesh_.cellShapes();

		forAll(cellShapes, celli)
		{
			if (cellShapes[celli].model() == wantedModel)
			{
				addOrDelete(set, celli, add);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::shapeToCell::shapeToCell
(
	const polyMesh& mesh,
	const word& type
)
	:
	topoSetSource(mesh),
	type_(type)
{
	if (!cellModeller::lookup(type_) && (type_ != "splitHex"))
	{
		FatalErrorInFunction
			<< "Illegal cell type " << type_ << exit(FatalError);
	}
}


tnbLib::shapeToCell::shapeToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	type_(dict.lookup("type"))
{
	if (!cellModeller::lookup(type_) && (type_ != "splitHex"))
	{
		FatalErrorInFunction
			<< "Illegal cell type " << type_ << exit(FatalError);
	}
}


tnbLib::shapeToCell::shapeToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	type_(checkIs(is))
{
	if (!cellModeller::lookup(type_) && (type_ != "splitHex"))
	{
		FatalErrorInFunction
			<< "Illegal cell type " << type_ << exit(FatalError);
	}
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::shapeToCell::~shapeToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::shapeToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all cells of type " << type_ << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all cells of type " << type_ << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //