#include <polyMeshFilterSettings.hxx>

#include <polyMeshFilterSettings.hxx>

#include <unitConversion.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyMeshFilterSettings::polyMeshFilterSettings(const dictionary& dict)
	:
	dict_(dict),
	controlMeshQuality_
	(
		dict_.lookupOrDefault<Switch>("controlMeshQuality", false)
	),
	collapseEdgesCoeffDict_(dict_.subDict("collapseEdgesCoeffs")),
	collapseFacesCoeffDict_(dict_.subOrEmptyDict("collapseFacesCoeffs")),
	meshQualityCoeffDict_(dict_.subOrEmptyDict("controlMeshQualityCoeffs")),
	minLen_(readScalar(collapseEdgesCoeffDict_.lookup("minimumEdgeLength"))),
	maxCos_
	(
		::cos
		(
			degToRad
			(
				readScalar(collapseEdgesCoeffDict_.lookup("maximumMergeAngle"))
			)
		)
	),
	edgeReductionFactor_
	(
		meshQualityCoeffDict_.lookupOrDefault<scalar>("edgeReductionFactor", -1)
	),
	maxIterations_
	(
		meshQualityCoeffDict_.lookupOrAddDefault<label>("maximumIterations", 1)
	),
	maxSmoothIters_
	(
		meshQualityCoeffDict_.lookupOrAddDefault<label>
		(
			"maximumSmoothingIterations",
			0
			)
	),
	initialFaceLengthFactor_
	(
		collapseFacesCoeffDict_.lookupOrAddDefault<scalar>
		(
			"initialFaceLengthFactor",
			-1
			)
	),
	faceReductionFactor_
	(
		meshQualityCoeffDict_.lookupOrAddDefault<scalar>
		(
			"faceReductionFactor",
			-1
			)
	),
	maxPointErrorCount_
	(
		meshQualityCoeffDict_.lookupOrAddDefault<label>("maxPointErrorCount", 0)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::polyMeshFilterSettings::writeSettings(Ostream& os) const
{
	os << "Merging:" << nl
		<< "    edges with length less than " << minLen() << " meters" << nl
		<< "    edges split by a point with edges in line to within "
		<< radToDeg(::acos(maxCos())) << " degrees" << nl
		<< "    Minimum edge length reduction factor = "
		<< edgeReductionFactor() << nl
		<< endl;

	if (collapseFacesCoeffDict().empty())
	{
		os << "Face collapsing is off" << endl;
	}
	else
	{
		os << "Face collapsing is on" << endl;
		os << "    Initial face length factor = " << initialFaceLengthFactor()
			<< endl;
	}

	os << "Control mesh quality = " << controlMeshQuality().asText() << endl;

	if (controlMeshQuality())
	{
		os << "    Minimum edge length reduction factor = "
			<< edgeReductionFactor() << nl
			<< "    Minimum face area reduction factor = "
			<< faceReductionFactor() << endl;

		os << "    Maximum number of collapse iterations = " << maxIterations()
			<< endl;

		os << "    Maximum number of edge/face reduction factor smoothing "
			<< "iterations = " << maxSmoothIters() << endl;

		os << "    Maximum number of times a point can contribute to bad "
			<< "faces across " << nl
			<< "    collapse iterations = " << maxPointErrorCount()
			<< endl;
	}

	os << "Selectively disabling wanted collapses until resulting quality"
		<< " satisfies constraints in system/meshQualityDict" << nl
		<< endl;
}


// ************************************************************************* //