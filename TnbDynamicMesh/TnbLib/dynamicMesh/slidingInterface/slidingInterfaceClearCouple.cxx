#include <slidingInterface.hxx>

#include <polyTopoChange.hxx>
#include <polyMesh.hxx>
#include <polyTopoChanger.hxx>
#include <polyRemovePoint.hxx>
#include <polyRemoveFace.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::slidingInterface::clearCouple
(
	polyTopoChange& ref
) const
{
	if (debug)
	{
		Pout << "void slidingInterface::clearCouple("
			<< "polyTopoChange& ref) const for object " << name() << " : "
			<< "Clearing old couple points and faces." << endl;
	}

	// Remove all points from the point zone

	const polyMesh& mesh = topoChanger().mesh();

	const labelList& cutPointZoneLabels =
		mesh.pointZones()[cutPointZoneID_.index()];

	forAll(cutPointZoneLabels, pointi)
	{
		ref.setAction(polyRemovePoint(cutPointZoneLabels[pointi]));
	}

	// Remove all faces from the face zone
	const labelList& cutFaceZoneLabels =
		mesh.faceZones()[cutFaceZoneID_.index()];

	forAll(cutFaceZoneLabels, facei)
	{
		ref.setAction(polyRemoveFace(cutFaceZoneLabels[facei]));
	}

	if (debug)
	{
		Pout << "void slidingInterface::clearCouple("
			<< "polyTopoChange& ref) const for object " << name() << " : "
			<< "Finished clearing old couple points and faces." << endl;
	}
}


// ************************************************************************* //