#include "checkMeshQuality.hxx"
#include <polyMesh.hxx>
#include <cellSet.hxx>
#include <faceSet.hxx>
#include <motionSmoother.hxx>
#include <surfaceWriter.hxx>
#include "checkTools.hxx"

tnbLib::label tnbLib::checkMeshQuality
(
    const polyMesh& mesh,
    const dictionary& dict,
    const autoPtr<surfaceWriter>& writer
)
{
    label noFailedChecks = 0;

    {
        faceSet faces(mesh, "meshQualityFaces", mesh.nFaces() / 100 + 1);
        motionSmoother::checkMesh(false, mesh, dict, faces);

        label nFaces = returnReduce(faces.size(), sumOp<label>());

        if (nFaces > 0)
        {
            noFailedChecks++;

            Info << "  <<Writing " << nFaces
                << " faces in error to set " << faces.name() << endl;
            faces.instance() = mesh.pointsInstance();
            faces.write();
            if (writer.valid())
            {
                mergeAndWrite(writer(), faces);
            }
        }
    }

    return noFailedChecks;
}
