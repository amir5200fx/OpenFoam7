#include <streamFunction.hxx>

#include <surfaceFields.hxx>
#include <pointFields.hxx>
#include <emptyPolyPatch.hxx>
#include <symmetryPlanePolyPatch.hxx>
#include <symmetryPolyPatch.hxx>
#include <wedgePolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(streamFunction, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			streamFunction,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointScalarField> tnbLib::functionObjects::streamFunction::calc
(
	const surfaceScalarField& phi
) const
{
	TnbLog << "    functionObjects::" << type() << " " << name()
		<< " calculating steam-function" << endl;

	Vector<label> slabNormal((Vector<label>::one - mesh_.geometricD()) / 2);
	const direction slabDir
	(
		slabNormal
		& Vector<label>(Vector<label>::X, Vector<label>::Y, Vector<label>::Z)
	);

	scalar thickness = vector(slabNormal) & mesh_.bounds().span();

	const pointMesh& pMesh = pointMesh::New(mesh_);

	tmp<pointScalarField> tstreamFunction
	(
		pointScalarField::New
		(
			"streamFunction",
			pMesh,
			dimensionedScalar(phi.dimensions(), 0)
		)
	);
	pointScalarField& streamFunction = tstreamFunction.ref();

	labelList visitedPoint(mesh_.nPoints());
	forAll(visitedPoint, pointi)
	{
		visitedPoint[pointi] = 0;
	}
	label nVisited = 0;
	label nVisitedOld = 0;

	const faceUList& faces = mesh_.faces();
	const pointField& points = mesh_.points();

	label nInternalFaces = mesh_.nInternalFaces();

	vectorField unitAreas(mesh_.faceAreas());
	unitAreas /= mag(unitAreas);

	const polyPatchList& patches = mesh_.boundaryMesh();

	bool finished = true;

	// Find the boundary face with zero flux. set the stream function
	// to zero on that face
	bool found = false;

	do
	{
		found = false;

		forAll(patches, patchi)
		{
			const primitivePatch& bouFaces = patches[patchi];

			if (!isType<emptyPolyPatch>(patches[patchi]))
			{
				forAll(bouFaces, facei)
				{
					if
						(
							magSqr(phi.boundaryField()[patchi][facei]) < small
							)
					{
						const labelList& zeroPoints = bouFaces[facei];

						// Zero flux face found
						found = true;

						forAll(zeroPoints, pointi)
						{
							if (visitedPoint[zeroPoints[pointi]] == 1)
							{
								found = false;
								break;
							}
						}

						if (found)
						{
							TnbLog << "        Zero face: patch: " << patchi
								<< " face: " << facei << endl;

							forAll(zeroPoints, pointi)
							{
								streamFunction[zeroPoints[pointi]] = 0;
								visitedPoint[zeroPoints[pointi]] = 1;
								nVisited++;
							}

							break;
						}
					}
				}
			}

			if (found) break;
		}

		if (!found)
		{
			TnbLog << "        Zero flux boundary face not found. "
				<< "Using cell as a reference."
				<< endl;

			const cellList& c = mesh_.cells();

			forAll(c, cI)
			{
				labelList zeroPoints = c[cI].labels(mesh_.faces());

				bool found = true;

				forAll(zeroPoints, pointi)
				{
					if (visitedPoint[zeroPoints[pointi]] == 1)
					{
						found = false;
						break;
					}
				}

				if (found)
				{
					forAll(zeroPoints, pointi)
					{
						streamFunction[zeroPoints[pointi]] = 0.0;
						visitedPoint[zeroPoints[pointi]] = 1;
						nVisited++;
					}

					break;
				}
				else
				{
					FatalErrorInFunction
						<< "Cannot find initialisation face or a cell."
						<< exit(FatalError);
				}
			}
		}

		// Loop through all faces. If one of the points on
		// the face has the streamfunction value different
		// from -1, all points with -1 ont that face have the
		// streamfunction value equal to the face flux in
		// that point plus the value in the visited point
		do
		{
			finished = true;

			for (label facei = nInternalFaces; facei < faces.size(); facei++)
			{
				const labelList& curBPoints = faces[facei];
				bool bPointFound = false;

				scalar currentBStream = 0.0;
				vector currentBStreamPoint(0, 0, 0);

				forAll(curBPoints, pointi)
				{
					// Check if the point has been visited
					if (visitedPoint[curBPoints[pointi]] == 1)
					{
						// The point has been visited
						currentBStream = streamFunction[curBPoints[pointi]];
						currentBStreamPoint = points[curBPoints[pointi]];

						bPointFound = true;

						break;
					}
				}

				if (bPointFound)
				{
					// Sort out other points on the face
					forAll(curBPoints, pointi)
					{
						// Check if the point has been visited
						if (visitedPoint[curBPoints[pointi]] == 0)
						{
							label patchNo =
								mesh_.boundaryMesh().whichPatch(facei);

							if
								(
									!isType<emptyPolyPatch>(patches[patchNo])
									&& !isType<symmetryPlanePolyPatch>
									(patches[patchNo])
									&& !isType<symmetryPolyPatch>(patches[patchNo])
									&& !isType<wedgePolyPatch>(patches[patchNo])
									)
							{
								label faceNo =
									mesh_.boundaryMesh()[patchNo]
									.whichFace(facei);

								vector edgeHat =
									points[curBPoints[pointi]]
									- currentBStreamPoint;
								edgeHat.replace(slabDir, 0);
								edgeHat /= mag(edgeHat);

								vector nHat = unitAreas[facei];

								if (edgeHat.y() > vSmall)
								{
									visitedPoint[curBPoints[pointi]] = 1;
									nVisited++;

									streamFunction[curBPoints[pointi]] =
										currentBStream
										+ phi.boundaryField()[patchNo][faceNo]
										* sign(nHat.x());
								}
								else if (edgeHat.y() < -vSmall)
								{
									visitedPoint[curBPoints[pointi]] = 1;
									nVisited++;

									streamFunction[curBPoints[pointi]] =
										currentBStream
										- phi.boundaryField()[patchNo][faceNo]
										* sign(nHat.x());
								}
								else
								{
									if (edgeHat.x() > vSmall)
									{
										visitedPoint[curBPoints[pointi]] = 1;
										nVisited++;

										streamFunction[curBPoints[pointi]] =
											currentBStream
											+ phi.boundaryField()[patchNo][faceNo]
											* sign(nHat.y());
									}
									else if (edgeHat.x() < -vSmall)
									{
										visitedPoint[curBPoints[pointi]] = 1;
										nVisited++;

										streamFunction[curBPoints[pointi]] =
											currentBStream
											- phi.boundaryField()[patchNo][faceNo]
											* sign(nHat.y());
									}
								}
							}
						}
					}
				}
				else
				{
					finished = false;
				}
			}

			for (label facei = 0; facei < nInternalFaces; facei++)
			{
				// Get the list of point labels for the face
				const labelList& curPoints = faces[facei];

				bool pointFound = false;

				scalar currentStream = 0.0;
				point currentStreamPoint(0, 0, 0);

				forAll(curPoints, pointi)
				{
					// Check if the point has been visited
					if (visitedPoint[curPoints[pointi]] == 1)
					{
						// The point has been visited
						currentStream = streamFunction[curPoints[pointi]];
						currentStreamPoint = points[curPoints[pointi]];
						pointFound = true;

						break;
					}
				}

				if (pointFound)
				{
					// Sort out other points on the face
					forAll(curPoints, pointi)
					{
						// Check if the point has been visited
						if (visitedPoint[curPoints[pointi]] == 0)
						{
							vector edgeHat =
								points[curPoints[pointi]] - currentStreamPoint;

							edgeHat.replace(slabDir, 0);
							edgeHat /= mag(edgeHat);

							vector nHat = unitAreas[facei];

							if (edgeHat.y() > vSmall)
							{
								visitedPoint[curPoints[pointi]] = 1;
								nVisited++;

								streamFunction[curPoints[pointi]] =
									currentStream
									+ phi[facei] * sign(nHat.x());
							}
							else if (edgeHat.y() < -vSmall)
							{
								visitedPoint[curPoints[pointi]] = 1;
								nVisited++;

								streamFunction[curPoints[pointi]] =
									currentStream
									- phi[facei] * sign(nHat.x());
							}
						}
					}
				}
				else
				{
					finished = false;
				}
			}

			if (nVisited == nVisitedOld)
			{
				// Find new seed.  This must be a
				// multiply connected domain
				TnbLog << "        Exhausted a seed, looking for new seed "
					<< "(this is correct for multiply connected domains).";

				break;
			}
			else
			{
				nVisitedOld = nVisited;
			}
		} while (!finished);
	} while (!finished);

	// Normalise the stream-function by the 2D mesh thickness
	streamFunction /= thickness;
	streamFunction.boundaryFieldRef() = 0.0;

	return tstreamFunction;
}


bool tnbLib::functionObjects::streamFunction::calc()
{
	if (foundObject<surfaceScalarField>(fieldName_))
	{
		const surfaceScalarField& phi =
			mesh_.lookupObject<surfaceScalarField>(fieldName_);

		return store(resultName_, calc(phi));
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::streamFunction::streamFunction
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "phi")
{
	setResultName("streamFunction", "phi");

	label nD = mesh_.nGeometricD();

	if (nD != 2)
	{
		FatalErrorInFunction
			<< "Case is not 2D, stream-function cannot be computed"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::streamFunction::~streamFunction()
{}


// ************************************************************************* //