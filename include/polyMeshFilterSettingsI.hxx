#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::dictionary&
tnbLib::polyMeshFilterSettings::collapseEdgesCoeffDict() const
{
	return collapseEdgesCoeffDict_;
}

inline const tnbLib::dictionary&
tnbLib::polyMeshFilterSettings::collapseFacesCoeffDict() const
{
	return collapseFacesCoeffDict_;
}

inline const tnbLib::dictionary&
tnbLib::polyMeshFilterSettings::meshQualityCoeffDict() const
{
	return meshQualityCoeffDict_;
}


inline const tnbLib::Switch&
tnbLib::polyMeshFilterSettings::controlMeshQuality() const
{
	return controlMeshQuality_;
}

inline const tnbLib::scalar& tnbLib::polyMeshFilterSettings::minLen() const
{
	return minLen_;
}

inline const tnbLib::scalar& tnbLib::polyMeshFilterSettings::maxCos() const
{
	return maxCos_;
}

inline const tnbLib::scalar&
tnbLib::polyMeshFilterSettings::edgeReductionFactor() const
{
	return edgeReductionFactor_;
}

inline const tnbLib::label& tnbLib::polyMeshFilterSettings::maxIterations() const
{
	return maxIterations_;
}

inline const tnbLib::label& tnbLib::polyMeshFilterSettings::maxSmoothIters() const
{
	return maxSmoothIters_;
}

inline const tnbLib::scalar&
tnbLib::polyMeshFilterSettings::initialFaceLengthFactor() const
{
	return initialFaceLengthFactor_;
}

inline const tnbLib::scalar&
tnbLib::polyMeshFilterSettings::faceReductionFactor() const
{
	return faceReductionFactor_;
}

inline const tnbLib::label&
tnbLib::polyMeshFilterSettings::maxPointErrorCount() const
{
	return maxPointErrorCount_;
}


// ************************************************************************* //