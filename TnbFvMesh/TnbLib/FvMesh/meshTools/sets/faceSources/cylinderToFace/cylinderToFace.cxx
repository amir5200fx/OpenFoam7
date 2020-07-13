#include <cylinderToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cylinderToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, cylinderToFace, word);
	addToRunTimeSelectionTable(topoSetSource, cylinderToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::cylinderToFace::usage_
(
	cylinderToFace::typeName,
	"\n    Usage: cylinderToFace (p1X p1Y p1Z) (p2X p2Y p2Z) radius\n\n"
	"    Select all faces with face centre within bounding cylinder\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::cylinderToFace::combine(topoSet& set, const bool add) const
{
	const vector axis = p2_ - p1_;
	const scalar rad2 = sqr(radius_);
	const scalar magAxis2 = magSqr(axis);

	const pointField& ctrs = mesh_.faceCentres();

	forAll(ctrs, facei)
	{
		vector d = ctrs[facei] - p1_;
		scalar magD = d & axis;

		if ((magD > 0) && (magD < magAxis2))
		{
			scalar d2 = (d & d) - sqr(magD) / magAxis2;
			if (d2 < rad2)
			{
				addOrDelete(set, facei, add);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cylinderToFace::cylinderToFace
(
	const polyMesh& mesh,
	const vector& p1,
	const vector& p2,
	const scalar radius
)
	:
	topoSetSource(mesh),
	p1_(p1),
	p2_(p2),
	radius_(radius)
{}


tnbLib::cylinderToFace::cylinderToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	p1_(dict.lookup("p1")),
	p2_(dict.lookup("p2")),
	radius_(readScalar(dict.lookup("radius")))
{}


tnbLib::cylinderToFace::cylinderToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	p1_(checkIs(is)),
	p2_(checkIs(is)),
	radius_(readScalar(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cylinderToFace::~cylinderToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cylinderToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces with centre within cylinder, with p1 = "
			<< p1_ << ", p2 = " << p2_ << " and radius = " << radius_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces with centre within cylinder, with p1 = "
			<< p1_ << ", p2 = " << p2_ << " and radius = " << radius_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //