#include <sphereToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sphereToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, sphereToCell, word);
	addToRunTimeSelectionTable(topoSetSource, sphereToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::sphereToCell::usage_
(
	sphereToCell::typeName,
	"\n    Usage: sphereToCell (centreX centreY centreZ) radius\n\n"
	"    Select all cells with cellCentre within bounding sphere\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sphereToCell::combine(topoSet& set, const bool add) const
{
	const pointField& ctrs = mesh_.cellCentres();

	const scalar radSquared = radius_ * radius_;

	forAll(ctrs, celli)
	{
		scalar offset = magSqr(centre_ - ctrs[celli]);
		if (offset <= radSquared)
		{
			addOrDelete(set, celli, add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sphereToCell::sphereToCell
(
	const polyMesh& mesh,
	const vector& centre,
	const scalar radius
)
	:
	topoSetSource(mesh),
	centre_(centre),
	radius_(radius)
{}


tnbLib::sphereToCell::sphereToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	centre_(dict.lookup("centre")),
	radius_(readScalar(dict.lookup("radius")))
{}


tnbLib::sphereToCell::sphereToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	centre_(checkIs(is)),
	radius_(readScalar(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sphereToCell::~sphereToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sphereToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells with centre within sphere, with centre = "
			<< centre_ << " and radius = " << radius_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells with centre within sphere, with centre = "
			<< centre_ << " and radius = " << radius_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //