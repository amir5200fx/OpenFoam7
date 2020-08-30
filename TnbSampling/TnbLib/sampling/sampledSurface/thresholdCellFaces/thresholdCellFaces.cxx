#include <thresholdCellFaces.hxx>

#include <emptyPolyPatch.hxx>

#include <polyMesh.hxx>  // added by amir
#include <processorPolyPatch.hxx>  // added by amir

// ** * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(thresholdCellFaces, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::thresholdCellFaces::calculate
(
	const scalarField& field,
	const scalar lowerThreshold,
	const scalar upperThreshold,
	const bool triangulate
)
{
	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	const faceList& origFaces = mesh_.faces();
	const pointField& origPoints = mesh_.points();

	const polyBoundaryMesh& bMesh = mesh_.boundaryMesh();


	surfZoneList surfZones(bMesh.size() + 1);

	surfZones[0] = surfZone
	(
		"internalMesh",
		0,  // size
		0,  // start
		0   // index
	);

	forAll(bMesh, patchi)
	{
		surfZones[patchi + 1] = surfZone
		(
			bMesh[patchi].name(),
			0,        // size
			0,        // start
			patchi + 1  // index
		);
	}


	label nFaces = 0;
	label nPoints = 0;


	meshCells_.clear();

	DynamicList<face>  surfFaces(0.5 * mesh_.nFaces());
	DynamicList<label> surfCells(surfFaces.size());

	labelList oldToNewPoints(origPoints.size(), -1);


	// internal faces only
	for (label facei = 0; facei < mesh_.nInternalFaces(); ++facei)
	{
		int side = 0;

		// check lowerThreshold
		if (field[own[facei]] > lowerThreshold)
		{
			if (field[nei[facei]] < lowerThreshold)
			{
				side = +1;
			}
		}
		else if (field[nei[facei]] > lowerThreshold)
		{
			side = -1;
		}

		// check upperThreshold
		if (field[own[facei]] < upperThreshold)
		{
			if (field[nei[facei]] > upperThreshold)
			{
				side = +1;
			}
		}
		else if (field[nei[facei]] < upperThreshold)
		{
			side = -1;
		}


		if (side)
		{
			const face& f = origFaces[facei];

			forAll(f, fp)
			{
				if (oldToNewPoints[f[fp]] == -1)
				{
					oldToNewPoints[f[fp]] = nPoints++;
				}
			}


			label cellId;
			face  surfFace;

			if (side > 0)
			{
				surfFace = f;
				cellId = own[facei];
			}
			else
			{
				surfFace = f.reverseFace();
				cellId = nei[facei];
			}


			if (triangulate)
			{
				label count = surfFace.triangles(origPoints, surfFaces);
				while (count-- > 0)
				{
					surfCells.append(cellId);
				}
			}
			else
			{
				surfFaces.append(surfFace);
				surfCells.append(cellId);
			}
		}
	}

	surfZones[0].size() = surfFaces.size();


	// nothing special for processor patches?
	forAll(bMesh, patchi)
	{
		const polyPatch& p = bMesh[patchi];
		surfZone& zone = surfZones[patchi + 1];

		zone.start() = nFaces;

		if
			(
				isA<emptyPolyPatch>(p)
				|| (Pstream::parRun() && isA<processorPolyPatch>(p))
				)
		{
			continue;
		}

		label facei = p.start();

		// patch faces
		forAll(p, localFacei)
		{
			if
				(
					field[own[facei]] > lowerThreshold
					&& field[own[facei]] < upperThreshold
					)
			{
				const face& f = origFaces[facei];
				forAll(f, fp)
				{
					if (oldToNewPoints[f[fp]] == -1)
					{
						oldToNewPoints[f[fp]] = nPoints++;
					}
				}

				label cellId = own[facei];

				if (triangulate)
				{
					label count = f.triangles(origPoints, surfFaces);
					while (count-- > 0)
					{
						surfCells.append(cellId);
					}
				}
				else
				{
					surfFaces.append(f);
					surfCells.append(cellId);
				}
			}

			++facei;
		}

		zone.size() = surfFaces.size() - zone.start();
	}


	surfFaces.shrink();
	surfCells.shrink();

	// renumber
	forAll(surfFaces, facei)
	{
		inplaceRenumber(oldToNewPoints, surfFaces[facei]);
	}


	pointField surfPoints(nPoints);
	nPoints = 0;
	forAll(oldToNewPoints, pointi)
	{
		if (oldToNewPoints[pointi] >= 0)
		{
			surfPoints[oldToNewPoints[pointi]] = origPoints[pointi];
			nPoints++;
		}
	}
	surfPoints.setSize(nPoints);

	this->storedPoints().transfer(surfPoints);
	this->storedFaces().transfer(surfFaces);
	this->storedZones().transfer(surfZones);

	meshCells_.transfer(surfCells);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::thresholdCellFaces::thresholdCellFaces
(
	const polyMesh& mesh,
	const scalarField& field,
	const scalar lowerThreshold,
	const scalar upperThreshold,
	const bool triangulate
)
	:
	mesh_(mesh)
{

	if (lowerThreshold > upperThreshold)
	{
		WarningInFunction
			<< lowerThreshold << " > " << upperThreshold << endl;
	}

	calculate(field, lowerThreshold, upperThreshold, triangulate);
}


// ************************************************************************* //