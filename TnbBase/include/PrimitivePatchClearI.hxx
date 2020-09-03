#pragma once
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::clearGeom()
{
	if (debug)
	{
		InfoInFunction << "Clearing geometric data" << endl;
	}

	deleteDemandDrivenData(localPointsPtr_);
	deleteDemandDrivenData(faceCentresPtr_);
	deleteDemandDrivenData(faceNormalsPtr_);
	deleteDemandDrivenData(pointNormalsPtr_);
}


template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::clearTopology()
{
	if (debug)
	{
		InfoInFunction << "Clearing patch addressing" << endl;
	}

	// group created and destroyed together
	if (edgesPtr_ && faceFacesPtr_ && edgeFacesPtr_ && faceEdgesPtr_)
	{
		delete edgesPtr_;
		edgesPtr_ = nullptr;

		delete faceFacesPtr_;
		faceFacesPtr_ = nullptr;

		delete edgeFacesPtr_;
		edgeFacesPtr_ = nullptr;

		delete faceEdgesPtr_;
		faceEdgesPtr_ = nullptr;
	}

	deleteDemandDrivenData(boundaryPointsPtr_);
	deleteDemandDrivenData(pointEdgesPtr_);
	deleteDemandDrivenData(pointFacesPtr_);
	deleteDemandDrivenData(edgeLoopsPtr_);
	deleteDemandDrivenData(localPointOrderPtr_);
}


template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::clearPatchMeshAddr()
{
	if (debug)
	{
		InfoInFunction << "Clearing patch-mesh addressing" << endl;
	}

	deleteDemandDrivenData(meshPointsPtr_);
	deleteDemandDrivenData(meshPointMapPtr_);
	deleteDemandDrivenData(localFacesPtr_);
}


template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::clearOut()
{
	clearGeom();
	clearTopology();
	clearPatchMeshAddr();
}


// ************************************************************************* //