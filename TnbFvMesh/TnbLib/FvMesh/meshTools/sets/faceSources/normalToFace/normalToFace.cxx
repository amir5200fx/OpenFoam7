#include <normalToFace.hxx>

#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(normalToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, normalToFace, word);
	addToRunTimeSelectionTable(topoSetSource, normalToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::normalToFace::usage_
(
	normalToFace::typeName,
	"\n    Usage: normalToFace (nx ny nz) <tol>\n\n"
	"    Select faces with normal aligned to unit vector (nx ny nz)\n"
	"    to within tol\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::normalToFace::setNormal()
{
	normal_ /= mag(normal_) + vSmall;

	Info << "    normalToFace : Normalized vector to " << normal_ << endl;

	if (tol_ < -1 || tol_ > 1)
	{
		FatalErrorInFunction
			<< "tolerance not within range -1..1 : " << tol_
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::normalToFace::normalToFace
(
	const polyMesh& mesh,
	const vector& normal,
	const scalar tol
)
	:
	topoSetSource(mesh),
	normal_(normal),
	tol_(tol)
{
	setNormal();
}


tnbLib::normalToFace::normalToFace(const polyMesh& mesh, const dictionary& dict)
	:
	topoSetSource(mesh),
	normal_(dict.lookup("normal")),
	tol_(readScalar(dict.lookup("cos")))
{
	setNormal();
}


tnbLib::normalToFace::normalToFace(const polyMesh& mesh, Istream& is)
	:
	topoSetSource(mesh),
	normal_(checkIs(is)),
	tol_(readScalar(checkIs(is)))
{
	setNormal();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::normalToFace::~normalToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::normalToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces according to normal being aligned with "
			<< normal_ << " (to within " << tol_ << ") ..." << endl;

		forAll(mesh_.faceAreas(), facei)
		{
			vector n = mesh_.faceAreas()[facei];
			n /= mag(n) + vSmall;

			if (mag(1 - (n & normal_)) < tol_)
			{
				set.insert(facei);
			}
		}
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces according to normal being aligned with "
			<< normal_ << " (to within " << tol_ << ") ..." << endl;


		DynamicList<label> toBeRemoved(set.size() / 10);

		forAllConstIter(topoSet, set, iter)
		{
			const label facei = iter.key();

			vector n = mesh_.faceAreas()[facei];
			n /= mag(n) + vSmall;

			if (mag(1 - (n & normal_)) < tol_)
			{
				toBeRemoved.append(facei);
			}
		}

		forAll(toBeRemoved, i)
		{
			set.erase(toBeRemoved[i]);
		}
	}
}


// ************************************************************************* //