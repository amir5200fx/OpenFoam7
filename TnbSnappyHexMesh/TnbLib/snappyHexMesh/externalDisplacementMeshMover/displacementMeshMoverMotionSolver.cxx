#include <displacementMeshMoverMotionSolver.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <localPointRegion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    defineTypeNameAndDebug(displacementMeshMoverMotionSolver, 0);

    addToRunTimeSelectionTable
    (
        motionSolver,
        displacementMeshMoverMotionSolver,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementMeshMoverMotionSolver::displacementMeshMoverMotionSolver
(
    const polyMesh& mesh,
    const dictionary& dict
)
    :
    displacementMotionSolver(mesh, dict, typeName) // read pointDisplacement
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementMeshMoverMotionSolver::
~displacementMeshMoverMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::externalDisplacementMeshMover&
tnbLib::displacementMeshMoverMotionSolver::meshMover() const
{
    if (!meshMoverPtr_.valid())
    {
        const word moverType(coeffDict().lookup("meshMover"));

        meshMoverPtr_ = externalDisplacementMeshMover::New
        (
            moverType,
            coeffDict().optionalSubDict(moverType + "Coeffs"),
            localPointRegion::findDuplicateFacePairs(mesh()),
            pointDisplacement_
        );
    }
    return meshMoverPtr_();
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::displacementMeshMoverMotionSolver::curPoints() const
{
    // Return actual points. Cannot do a reference since complains about
    // assignment to self in polyMesh::movePoints
    return tmp<pointField>(new pointField(mesh().points()));
}


void tnbLib::displacementMeshMoverMotionSolver::solve()
{
    // The points have moved so before calculation update
    // the mesh and motionSolver accordingly
    movePoints(mesh().points());

    // Update any point motion bcs (e.g. timevarying)
    pointDisplacement().boundaryFieldRef().updateCoeffs();

    label nAllowableErrors = 0;
    labelList checkFaces(identity(mesh().nFaces()));
    meshMover().move
    (
        coeffDict().optionalSubDict(meshMover().type() + "Coeffs"),
        nAllowableErrors,
        checkFaces
    );

    // This will have updated the mesh and implicitly the pointDisplacement
    pointDisplacement().correctBoundaryConditions();
}


void tnbLib::displacementMeshMoverMotionSolver::movePoints(const pointField& p)
{
    displacementMotionSolver::movePoints(p);

    // Update meshMover for new geometry
    if (meshMoverPtr_.valid())
    {
        meshMover().movePoints(p);
    }
}


void tnbLib::displacementMeshMoverMotionSolver::updateMesh
(
    const mapPolyMesh& map
)
{
    displacementMotionSolver::updateMesh(map);

    // Update meshMover for new topology
    meshMoverPtr_.clear();
}


// ************************************************************************* //
