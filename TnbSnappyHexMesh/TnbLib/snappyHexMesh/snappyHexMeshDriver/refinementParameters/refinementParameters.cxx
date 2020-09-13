#include <refinementParameters.hxx>

#include <unitConversion.hxx>
#include <polyMesh.hxx>
#include <globalIndex.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::refinementParameters::refinementParameters(const dictionary& dict)
	:
	maxGlobalCells_(readLabel(dict.lookup("maxGlobalCells"))),
	maxLocalCells_(readLabel(dict.lookup("maxLocalCells"))),
	minRefineCells_(readLabel(dict.lookup("minRefinementCells"))),
	planarAngle_
	(
		dict.lookupOrDefault
		(
			"planarAngle",
			readScalar(dict.lookup("resolveFeatureAngle"))
		)
	),
	nBufferLayers_(readLabel(dict.lookup("nCellsBetweenLevels"))),
	keepPoints_(pointField(1, dict.lookup("locationInMesh"))),
	allowFreeStandingZoneFaces_(dict.lookup("allowFreeStandingZoneFaces")),
	useTopologicalSnapDetection_
	(
		dict.lookupOrDefault<bool>("useTopologicalSnapDetection", true)
	),
	maxLoadUnbalance_(dict.lookupOrDefault<scalar>("maxLoadUnbalance", 0)),
	handleSnapProblems_
	(
		dict.lookupOrDefault<Switch>("handleSnapProblems", true)
	)
{
	scalar featAngle(readScalar(dict.lookup("resolveFeatureAngle")));

	if (featAngle < 0 || featAngle > 180)
	{
		curvature_ = -great;
	}
	else
	{
		curvature_ = tnbLib::cos(degToRad(featAngle));
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::refinementParameters::findCells(const polyMesh& mesh)
const
{
	// Force calculation of tet-diag decomposition (for use in findCell)
	(void)mesh.tetBasePtIs();

	// Global calculation engine
	globalIndex globalCells(mesh.nCells());

	// Cell label per point
	labelList cellLabels(keepPoints_.size());

	forAll(keepPoints_, i)
	{
		const point& keepPoint = keepPoints_[i];

		label localCelli = mesh.findCell(keepPoint);

		label globalCelli = -1;

		if (localCelli != -1)
		{
			globalCelli = globalCells.toGlobal(localCelli);
		}

		reduce(globalCelli, maxOp<label>());

		if (globalCelli == -1)
		{
			FatalErrorInFunction
				<< "Point " << keepPoint
				<< " is not inside the mesh or on a face or edge." << nl
				<< "Bounding box of the mesh:" << mesh.bounds()
				<< exit(FatalError);
		}


		label proci = globalCells.whichProcID(globalCelli);
		label procCelli = globalCells.toLocal(proci, globalCelli);

		Info << "Found point " << keepPoint << " in cell " << procCelli
			<< " on processor " << proci << endl;


		if (globalCells.isLocal(globalCelli))
		{
			cellLabels[i] = localCelli;
		}
		else
		{
			cellLabels[i] = -1;
		}
	}
	return cellLabels;
}


// ************************************************************************* //