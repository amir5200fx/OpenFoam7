#include <volPointInterpolation.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <pointFields.hxx>
#include <demandDrivenData.hxx>
#include <pointConstraints.hxx>
#include <surfaceFields.hxx>

#include <emptyPolyPatch.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(volPointInterpolation, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::volPointInterpolation::calcBoundaryAddressing()
{
	if (debug)
	{
		Pout << "volPointInterpolation::calcBoundaryAddressing() : "
			<< "constructing boundary addressing"
			<< endl;
	}

	boundaryPtr_.reset
	(
		new primitivePatch
		(
			SubList<face>
			(
				mesh().faces(),
				mesh().nFaces() - mesh().nInternalFaces(),
				mesh().nInternalFaces()
				),
			mesh().points()
		)
	);
	const primitivePatch& boundary = boundaryPtr_();

	boundaryIsPatchFace_.setSize(boundary.size());
	boundaryIsPatchFace_ = false;

	isPatchPoint_.setSize(mesh().nPoints());
	isPatchPoint_ = false;

	const polyBoundaryMesh& pbm = mesh().boundaryMesh();

	// Get precalculated volField only so we can use coupled() tests for
	// cyclicAMI
	const surfaceScalarField& magSf = mesh().magSf();

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];

		if
			(
				!isA<emptyPolyPatch>(pp)
				&& !magSf.boundaryField()[patchi].coupled()
				)
		{
			label bFacei = pp.start() - mesh().nInternalFaces();

			forAll(pp, i)
			{
				boundaryIsPatchFace_[bFacei] = true;

				const face& f = boundary[bFacei++];

				forAll(f, fp)
				{
					isPatchPoint_[f[fp]] = true;
				}
			}
		}
	}

	// Make sure point status is synchronised so even processor that holds
	// no face of a certain patch still can have boundary points marked.
	if (debug)
	{
		boolList oldData(isPatchPoint_);

		pointConstraints::syncUntransformedData
		(
			mesh(),
			isPatchPoint_,
			orEqOp<bool>()
		);

		forAll(isPatchPoint_, pointi)
		{
			if (isPatchPoint_[pointi] != oldData[pointi])
			{
				Pout << "volPointInterpolation::calcBoundaryAddressing():"
					<< " added dangling mesh point:" << pointi
					<< " at:" << mesh().points()[pointi]
					<< endl;
			}
		}

		label nPatchFace = 0;
		forAll(boundaryIsPatchFace_, i)
		{
			if (boundaryIsPatchFace_[i])
			{
				nPatchFace++;
			}
		}
		label nPatchPoint = 0;
		forAll(isPatchPoint_, i)
		{
			if (isPatchPoint_[i])
			{
				nPatchPoint++;
			}
		}
		Pout << "boundary:" << nl
			<< "    faces :" << boundary.size() << nl
			<< "    of which on proper patch:" << nPatchFace << nl
			<< "    points:" << boundary.nPoints() << nl
			<< "    of which on proper patch:" << nPatchPoint << endl;
	}
}


void tnbLib::volPointInterpolation::makeInternalWeights(scalarField& sumWeights)
{
	if (debug)
	{
		Pout << "volPointInterpolation::makeInternalWeights() : "
			<< "constructing weighting factors for internal and non-coupled"
			<< " points." << endl;
	}

	const pointField& points = mesh().points();
	const labelListList& pointCells = mesh().pointCells();
	const vectorField& cellCentres = mesh().cellCentres();

	// Allocate storage for weighting factors
	pointWeights_.clear();
	pointWeights_.setSize(points.size());

	// Calculate inverse distances between cell centres and points
	// and store in weighting factor array
	forAll(points, pointi)
	{
		if (!isPatchPoint_[pointi])
		{
			const labelList& pcp = pointCells[pointi];

			scalarList& pw = pointWeights_[pointi];
			pw.setSize(pcp.size());

			forAll(pcp, pointCelli)
			{
				pw[pointCelli] =
					1.0 / mag(points[pointi] - cellCentres[pcp[pointCelli]]);

				sumWeights[pointi] += pw[pointCelli];
			}
		}
	}
}


void tnbLib::volPointInterpolation::makeBoundaryWeights(scalarField& sumWeights)
{
	if (debug)
	{
		Pout << "volPointInterpolation::makeBoundaryWeights() : "
			<< "constructing weighting factors for boundary points." << endl;
	}

	const pointField& points = mesh().points();
	const pointField& faceCentres = mesh().faceCentres();

	const primitivePatch& boundary = boundaryPtr_();

	boundaryPointWeights_.clear();
	boundaryPointWeights_.setSize(boundary.meshPoints().size());

	forAll(boundary.meshPoints(), i)
	{
		label pointi = boundary.meshPoints()[i];

		if (isPatchPoint_[pointi])
		{
			const labelList& pFaces = boundary.pointFaces()[i];

			scalarList& pw = boundaryPointWeights_[i];
			pw.setSize(pFaces.size());

			sumWeights[pointi] = 0.0;

			forAll(pFaces, i)
			{
				if (boundaryIsPatchFace_[pFaces[i]])
				{
					label facei = mesh().nInternalFaces() + pFaces[i];

					pw[i] = 1.0 / mag(points[pointi] - faceCentres[facei]);
					sumWeights[pointi] += pw[i];
				}
				else
				{
					pw[i] = 0.0;
				}
			}
		}
	}
}


void tnbLib::volPointInterpolation::makeWeights()
{
	if (debug)
	{
		Pout << "volPointInterpolation::makeWeights() : "
			<< "constructing weighting factors"
			<< endl;
	}

	// Update addressing over all boundary faces
	calcBoundaryAddressing();


	// Running sum of weights
	pointScalarField sumWeights
	(
		IOobject
		(
			"volPointSumWeights",
			mesh().polyMesh::instance(),
			mesh()
		),
		pointMesh::New(mesh()),
		dimensionedScalar(dimless, 0)
	);


	// Create internal weights; add to sumWeights
	makeInternalWeights(sumWeights);


	// Create boundary weights; override sumWeights
	makeBoundaryWeights(sumWeights);


	// forAll(boundary.meshPoints(), i)
	//{
	//    label pointi = boundary.meshPoints()[i];
	//
	//    if (isPatchPoint_[pointi])
	//    {
	//        Pout<< "Calculated Weight at boundary point:" << i
	//            << " at:" << mesh().points()[pointi]
	//            << " sumWeight:" << sumWeights[pointi]
	//            << " from:" << boundaryPointWeights_[i]
	//            << endl;
	//    }
	//}


	// Sum collocated contributions
	pointConstraints::syncUntransformedData
	(
		mesh(),
		sumWeights,
		plusEqOp<scalar>()
	);

	// And add separated contributions
	addSeparated(sumWeights);

	// Push master data to slaves. It is possible (not sure how often) for
	// a coupled point to have its master on a different patch so
	// to make sure just push master data to slaves. Reuse the syncPointData
	// structure.
	pushUntransformedData(sumWeights);


	// Normalise internal weights
	forAll(pointWeights_, pointi)
	{
		scalarList& pw = pointWeights_[pointi];
		// Note:pw only sized for !isPatchPoint
		forAll(pw, i)
		{
			pw[i] /= sumWeights[pointi];
		}
	}

	// Normalise boundary weights
	const primitivePatch& boundary = boundaryPtr_();

	forAll(boundary.meshPoints(), i)
	{
		label pointi = boundary.meshPoints()[i];

		scalarList& pw = boundaryPointWeights_[i];
		// Note:pw only sized for isPatchPoint
		forAll(pw, i)
		{
			pw[i] /= sumWeights[pointi];
		}
	}


	if (debug)
	{
		Pout << "volPointInterpolation::makeWeights() : "
			<< "finished constructing weighting factors"
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::volPointInterpolation::volPointInterpolation(const fvMesh& vm)
	:
	MeshObject<fvMesh, tnbLib::UpdateableMeshObject, volPointInterpolation>(vm)
{
	makeWeights();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::volPointInterpolation::~volPointInterpolation()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::volPointInterpolation::updateMesh(const mapPolyMesh&)
{
	makeWeights();
}


bool tnbLib::volPointInterpolation::movePoints()
{
	makeWeights();

	return true;
}


void tnbLib::volPointInterpolation::interpolateDisplacement
(
	const volVectorField& vf,
	pointVectorField& pf
) const
{
	interpolateInternalField(vf, pf);

	// Interpolate to the patches but no constraints
	interpolateBoundaryField(vf, pf);

	// Apply displacement constraints
	const pointConstraints& pcs = pointConstraints::New(pf.mesh());

	pcs.constrainDisplacement(pf, false);
}


// ************************************************************************* //