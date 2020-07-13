#include <pointToFace.hxx>

#include <polyMesh.hxx>
#include <pointSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, pointToFace, word);
	addToRunTimeSelectionTable(topoSetSource, pointToFace, istream);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::pointToFace::pointAction,
		3
		>::names[] =
	{
		"any",
		"all",
		"edge"
	};
}


tnbLib::topoSetSource::addToUsageTable tnbLib::pointToFace::usage_
(
	pointToFace::typeName,
	"\n    Usage: pointToFace <pointSet> any|all|edge\n\n"
	"    Select faces with\n"
	"    -any point in the pointSet\n"
	"    -all points in the pointSet\n\n"
	"    -two consecutive points (an edge) in the pointSet\n\n"
);

const tnbLib::NamedEnum<tnbLib::pointToFace::pointAction, 3>
tnbLib::pointToFace::pointActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointToFace::combine(topoSet& set, const bool add) const
{
	// Load the set
	pointSet loadedSet(mesh_, setName_);

	if (option_ == ANY)
	{
		// Add faces with any point in loadedSet
		forAllConstIter(pointSet, loadedSet, iter)
		{
			const label pointi = iter.key();
			const labelList& pFaces = mesh_.pointFaces()[pointi];

			forAll(pFaces, pFacei)
			{
				addOrDelete(set, pFaces[pFacei], add);
			}
		}
	}
	else if (option_ == ALL)
	{
		// Add all faces whose points are all in set.

		// Count number of points using face.
		Map<label> numPoints(loadedSet.size());

		forAllConstIter(pointSet, loadedSet, iter)
		{
			const label pointi = iter.key();
			const labelList& pFaces = mesh_.pointFaces()[pointi];

			forAll(pFaces, pFacei)
			{
				const label facei = pFaces[pFacei];

				Map<label>::iterator fndFace = numPoints.find(facei);

				if (fndFace == numPoints.end())
				{
					numPoints.insert(facei, 1);
				}
				else
				{
					fndFace()++;
				}
			}
		}


		// Include faces that are referenced as many times as there are points
		// in face -> all points of face
		forAllConstIter(Map<label>, numPoints, iter)
		{
			const label facei = iter.key();

			if (iter() == mesh_.faces()[facei].size())
			{
				addOrDelete(set, facei, add);
			}
		}
	}
	else if (option_ == EDGE)
	{
		const faceList& faces = mesh_.faces();
		forAll(faces, facei)
		{
			const face& f = faces[facei];

			forAll(f, fp)
			{
				if (loadedSet.found(f[fp]) && loadedSet.found(f.nextLabel(fp)))
				{
					addOrDelete(set, facei, add);
					break;
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointToFace::pointToFace
(
	const polyMesh& mesh,
	const word& setName,
	const pointAction option
)
	:
	topoSetSource(mesh),
	setName_(setName),
	option_(option)
{}


tnbLib::pointToFace::pointToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	option_(pointActionNames_.read(dict.lookup("option")))
{}


tnbLib::pointToFace::pointToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	option_(pointActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointToFace::~pointToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding faces according to pointSet " << setName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing faces according to pointSet " << setName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //