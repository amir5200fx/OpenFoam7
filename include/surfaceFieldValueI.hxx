#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypes&
tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionType() const
{
	return regionType_;
}


inline const tnbLib::labelList&
tnbLib::functionObjects::fieldValues::surfaceFieldValue::faceId() const
{
	return faceId_;
}


inline const tnbLib::labelList&
tnbLib::functionObjects::fieldValues::surfaceFieldValue::facePatch() const
{
	return facePatchId_;
}


inline const tnbLib::labelList&
tnbLib::functionObjects::fieldValues::surfaceFieldValue::faceSign() const
{
	return faceSign_;
}


inline tnbLib::fileName
tnbLib::functionObjects::fieldValues::surfaceFieldValue::outputDir() const
{
	return baseFileDir() / name() / "surface" / obr_.time().timeName();
}


// ************************************************************************* //