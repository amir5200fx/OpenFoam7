#include <searchableSurfaceToFaceZone.hxx>

#include <polyMesh.hxx>
#include <faceZoneSet.hxx>
#include <searchableSurface.hxx>
#include <syncTools.hxx>
#include <Time.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(searchableSurfaceToFaceZone, 0);
	addToRunTimeSelectionTable
	(
		topoSetSource,
		searchableSurfaceToFaceZone,
		word
	);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::searchableSurfaceToFaceZone::usage_
(
	searchableSurfaceToFaceZone::typeName,
	"\n    Usage: searchableSurfaceToFaceZone surface\n\n"
	"    Select all faces whose cell-cell centre vector intersects the surface "
	"\n"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::searchableSurfaceToFaceZone::searchableSurfaceToFaceZone
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	surfacePtr_
	(
		searchableSurface::New
		(
			word(dict.lookup("surface")),
			IOobject
			(
				dict.lookupOrDefault("name", mesh.objectRegistry::db().name()),
				mesh.time().constant(),
				"triSurface",
				mesh.objectRegistry::db(),
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			),
			dict
		)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::searchableSurfaceToFaceZone::~searchableSurfaceToFaceZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::searchableSurfaceToFaceZone::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if (!isA<faceZoneSet>(set))
	{
		WarningInFunction
			<< "Operation only allowed on a faceZoneSet." << endl;
	}
	else
	{
		faceZoneSet& fzSet = refCast<faceZoneSet>(set);

		// Get cell-cell centre vectors
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		pointField start(mesh_.nFaces());
		pointField end(mesh_.nFaces());

		const pointField& cc = mesh_.cellCentres();

		// Internal faces
		for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
		{
			start[facei] = cc[mesh_.faceOwner()[facei]];
			end[facei] = cc[mesh_.faceNeighbour()[facei]];
		}

		// Boundary faces
		vectorField nbrCellCentres;
		syncTools::swapBoundaryCellPositions(mesh_, cc, nbrCellCentres);

		const polyBoundaryMesh& pbm = mesh_.boundaryMesh();

		forAll(pbm, patchi)
		{
			const polyPatch& pp = pbm[patchi];

			if (pp.coupled())
			{
				forAll(pp, i)
				{
					label facei = pp.start() + i;
					start[facei] = cc[mesh_.faceOwner()[facei]];
					end[facei] = nbrCellCentres[facei - mesh_.nInternalFaces()];
				}
			}
			else
			{
				forAll(pp, i)
				{
					label facei = pp.start() + i;
					start[facei] = cc[mesh_.faceOwner()[facei]];
					end[facei] = mesh_.faceCentres()[facei];
				}
			}
		}


		// Do all intersection tests
		// ~~~~~~~~~~~~~~~~~~~~~~~~~

		List<pointIndexHit> hits;
		surfacePtr_().findLine(start, end, hits);
		pointField normals;
		surfacePtr_().getNormal(hits, normals);


		// Select intersected faces
		// ~~~~~~~~~~~~~~~~~~~~~~~~

		if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
		{
			Info << "    Adding all faces from surface "
				<< surfacePtr_().name() << " ..." << endl;

			DynamicList<label> newAddressing(fzSet.addressing());
			DynamicList<bool> newFlipMap(fzSet.flipMap());

			forAll(hits, facei)
			{
				if (hits[facei].hit() && !fzSet.found(facei))
				{
					newAddressing.append(facei);
					vector d = end[facei] - start[facei];
					newFlipMap.append((normals[facei] & d) < 0);
				}
			}

			fzSet.addressing().transfer(newAddressing);
			fzSet.flipMap().transfer(newFlipMap);
			fzSet.updateSet();
		}
		else if (action == topoSetSource::DELETE)
		{
			Info << "    Removing all faces from surface "
				<< surfacePtr_().name() << " ..." << endl;

			// Start off empty
			DynamicList<label> newAddressing(fzSet.addressing().size());
			DynamicList<bool> newFlipMap(fzSet.flipMap().size());

			forAll(fzSet.addressing(), i)
			{
				if (!hits[fzSet.addressing()[i]].hit())
				{
					newAddressing.append(fzSet.addressing()[i]);
					newFlipMap.append(fzSet.flipMap()[i]);
				}
			}
			fzSet.addressing().transfer(newAddressing);
			fzSet.flipMap().transfer(newFlipMap);
			fzSet.updateSet();
		}
	}
}


// ************************************************************************* //