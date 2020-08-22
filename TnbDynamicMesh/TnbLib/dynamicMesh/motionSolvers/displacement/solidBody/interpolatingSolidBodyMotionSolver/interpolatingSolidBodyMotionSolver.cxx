#include <interpolatingSolidBodyMotionSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <pointPatchDist.hxx>
#include <pointConstraints.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(interpolatingSolidBodyMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		interpolatingSolidBodyMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::interpolatingSolidBodyMotionSolver::interpolatingSolidBodyMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	points0MotionSolver(mesh, dict, typeName),
	SBMFPtr_(solidBodyMotionFunction::New(coeffDict(), mesh.time())),
	patches_(wordReList(coeffDict().lookup("patches"))),
	patchSet_(mesh.boundaryMesh().patchSet(patches_)),
	CofG_(coeffDict().lookup("CofG")),
	di_(readScalar(coeffDict().lookup("innerDistance"))),
	do_(readScalar(coeffDict().lookup("outerDistance"))),
	scale_
	(
		IOobject
		(
			"motionScale",
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		pointMesh::New(mesh),
		dimensionedScalar(dimless, 0)
	)
{
	// Calculate scaling factor everywhere

	{
		const pointMesh& pMesh = pointMesh::New(mesh);

		pointPatchDist pDist(pMesh, patchSet_, points0());

		// Scaling: 1 up to di then linear down to 0 at do away from patches
		scale_.primitiveFieldRef() =
			min
			(
				max
				(
				(do_ - pDist.primitiveField()) / (do_ - di_),
					scalar(0)
				),
				scalar(1)
			);

		// Convert the scale function to a cosine
		scale_.primitiveFieldRef() =
			min
			(
				max
				(
					0.5
					- 0.5
					*cos(scale_.primitiveField()
						*tnbLib::constant::mathematical::pi),
					scalar(0)
				),
				scalar(1)
			);

		pointConstraints::New(pMesh).constrain(scale_);
		scale_.write();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::interpolatingSolidBodyMotionSolver::~interpolatingSolidBodyMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::interpolatingSolidBodyMotionSolver::curPoints() const
{
	const pointField& points0 = this->points0();
	const septernion s = SBMFPtr_().transformation();

	tmp<pointField> tpoints(new pointField(points0));
	pointField& points = tpoints.ref();

	forAll(points, pointi)
	{
		// Move non-stationary points
		if (scale_[pointi] > small)
		{
			// Use solid-body motion where scale = 1
			if (scale_[pointi] > 1 - small)
			{
				points[pointi] =
					CofG_ + s.transformPoint(points0[pointi] - CofG_);
			}
			// Slerp septernion interpolation
			else
			{
				const septernion ss(slerp(septernion::I, s, scale_[pointi]));

				points[pointi] =
					CofG_ + ss.transformPoint(points0[pointi] - CofG_);
			}
		}
	}

	return tpoints;
}


// ************************************************************************* //