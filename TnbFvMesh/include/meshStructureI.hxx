#pragma once
// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::meshStructure::structured() const
{
	return structured_;
}


const tnbLib::labelList& tnbLib::meshStructure::cellToPatchFaceAddressing() const
{
	return cellToPatchFaceAddressing_;
}


tnbLib::labelList& tnbLib::meshStructure::cellToPatchFaceAddressing()
{
	return cellToPatchFaceAddressing_;
}


const tnbLib::labelList& tnbLib::meshStructure::cellLayer() const
{
	return cellLayer_;
}


tnbLib::labelList& tnbLib::meshStructure::cellLayer()
{
	return cellLayer_;
}


const tnbLib::labelList& tnbLib::meshStructure::faceToPatchFaceAddressing() const
{
	return faceToPatchFaceAddressing_;
}


tnbLib::labelList& tnbLib::meshStructure::faceToPatchFaceAddressing()
{
	return faceToPatchFaceAddressing_;
}


const tnbLib::labelList& tnbLib::meshStructure::faceToPatchEdgeAddressing() const
{
	return faceToPatchEdgeAddressing_;
}


tnbLib::labelList& tnbLib::meshStructure::faceToPatchEdgeAddressing()
{
	return faceToPatchEdgeAddressing_;
}


const tnbLib::labelList& tnbLib::meshStructure::faceLayer() const
{
	return faceLayer_;
}


tnbLib::labelList& tnbLib::meshStructure::faceLayer()
{
	return faceLayer_;
}


const tnbLib::labelList& tnbLib::meshStructure::pointToPatchPointAddressing() const
{
	return pointToPatchPointAddressing_;
}


tnbLib::labelList& tnbLib::meshStructure::pointToPatchPointAddressing()
{
	return pointToPatchPointAddressing_;
}


const tnbLib::labelList& tnbLib::meshStructure::pointLayer() const
{
	return pointLayer_;
}


tnbLib::labelList& tnbLib::meshStructure::pointLayer()
{
	return pointLayer_;
}


// ************************************************************************* //
