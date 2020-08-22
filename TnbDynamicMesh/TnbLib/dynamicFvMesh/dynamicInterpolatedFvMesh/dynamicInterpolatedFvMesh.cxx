#include <dynamicInterpolatedFvMesh.hxx>

#include <volFields.hxx>
#include <pointFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dynamicInterpolatedFvMesh, 0);
	addToRunTimeSelectionTable
	(
		dynamicFvMesh,
		dynamicInterpolatedFvMesh,
		IOobject
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicInterpolatedFvMesh::dynamicInterpolatedFvMesh(const IOobject& io)
	:
	dynamicFvMesh(io),
	dynamicMeshCoeffs_(dynamicMeshDict().optionalSubDict(typeName + "Coeffs")),
	pointInterpolator_(*this, dynamicMeshCoeffs_),
	displacement_(dynamicMeshCoeffs_.lookup("displacement")),
	points0_
	(
		displacement_
		? new pointIOField(points0IO(*this))
		: nullptr
	),
	velocityMotionCorrection_(*this, dynamicMeshDict())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dynamicInterpolatedFvMesh::~dynamicInterpolatedFvMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dynamicInterpolatedFvMesh::update()
{
	if (displacement_)
	{
		fvMesh::movePoints(points0_() + pointInterpolator_.curPointField()());
	}
	else
	{
		fvMesh::movePoints(pointInterpolator_.curPointField());
	}

	velocityMotionCorrection_.update();

	return true;
}


// ************************************************************************* //