#include <snapParameters.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from dictionary
tnbLib::snapParameters::snapParameters(const dictionary& dict)
	:
	nSmoothPatch_(readLabel(dict.lookup("nSmoothPatch"))),
	snapTol_(readScalar(dict.lookup("tolerance"))),
	nSmoothDispl_(readLabel(dict.lookup("nSolveIter"))),
	nSnap_(readLabel(dict.lookup("nRelaxIter"))),
	nFeatureSnap_(dict.lookupOrDefault("nFeatureSnapIter", -1)),
	explicitFeatureSnap_(dict.lookupOrDefault("explicitFeatureSnap", true)),
	implicitFeatureSnap_(dict.lookupOrDefault("implicitFeatureSnap", false)),
	multiRegionFeatureSnap_
	(
		dict.lookupOrDefault("multiRegionFeatureSnap", false)
	),
	detectNearSurfacesSnap_
	(
		dict.lookupOrDefault("detectNearSurfacesSnap", true)
	)
{}


// ************************************************************************* //