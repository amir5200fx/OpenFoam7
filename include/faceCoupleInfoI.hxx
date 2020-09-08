#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Add a T entry
template<template<class> class FaceList>
tnbLib::pointField tnbLib::faceCoupleInfo::calcFaceCentres
(
	const FaceList<face>& faces,
	const pointField& points,
	const label start,
	const label size
)
{
	pointField fc(size);

	label facei = start;

	forAll(fc, i)
	{
		fc[i] = faces[facei++].centre(points);
	}
	return fc;
}


template<template<class> class FaceList>
tnbLib::pointField tnbLib::faceCoupleInfo::calcFacePointAverages
(
	const FaceList<face>& faces,
	const pointField& points,
	const label start,
	const label size
)
{
	pointField fpa(size, Zero);

	label facei = start;

	forAll(fpa, i)
	{
		forAll(faces[facei], j)
		{
			fpa[i] += points[faces[facei][j]];
		}
		fpa[i] /= faces[facei++].size();
	}
	return fpa;
}


// ************************************************************************* //