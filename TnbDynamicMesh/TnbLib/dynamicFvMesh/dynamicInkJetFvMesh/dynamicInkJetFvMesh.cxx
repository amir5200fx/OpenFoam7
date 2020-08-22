#include <dynamicInkJetFvMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <mathematicalConstants.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dynamicInkJetFvMesh, 0);
	addToRunTimeSelectionTable(dynamicFvMesh, dynamicInkJetFvMesh, IOobject);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicInkJetFvMesh::dynamicInkJetFvMesh(const IOobject& io)
	:
	dynamicFvMesh(io),
	dynamicMeshCoeffs_(dynamicMeshDict().optionalSubDict(typeName + "Coeffs")),
	amplitude_(readScalar(dynamicMeshCoeffs_.lookup("amplitude"))),
	frequency_(readScalar(dynamicMeshCoeffs_.lookup("frequency"))),
	refPlaneX_(readScalar(dynamicMeshCoeffs_.lookup("refPlaneX"))),
	stationaryPoints_
	(
		tnbLib::IOobject
		(
			"points",
			io.time().constant(),
			meshSubDir,
			*this,
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::NO_WRITE
		)
	),
	velocityMotionCorrection_(*this, dynamicMeshDict())
{
	Info << "Performing a dynamic mesh calculation: " << endl
		<< "amplitude: " << amplitude_
		<< " frequency: " << frequency_
		<< " refPlaneX: " << refPlaneX_ << endl;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dynamicInkJetFvMesh::~dynamicInkJetFvMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dynamicInkJetFvMesh::update()
{
	scalar scalingFunction =
		0.5*
		(
			::cos(constant::mathematical::twoPi*frequency_*time().value())
			- 1.0
			);

	Info << "Mesh scaling. Time = " << time().value() << " scaling: "
		<< scalingFunction << endl;

	pointField newPoints = stationaryPoints_;

	newPoints.replace
	(
		vector::X,
		stationaryPoints_.component(vector::X)*
		(
			1.0
			+ pos0
			(
				-(stationaryPoints_.component(vector::X))
				- refPlaneX_
			)*amplitude_*scalingFunction
			)
	);

	fvMesh::movePoints(newPoints);

	velocityMotionCorrection_.update();

	return true;
}


// ************************************************************************* //