#pragma once
#include <EdgeMap.hxx>  // added by amir
#include <PackedBoolList.hxx> // added by amir
#include <Map.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class FaceList1, class PointField1, class FaceList2, class PointField2>
void tnbLib::PatchTools::matchPoints
(
	const PrimitivePatch<FaceList1, PointField1>& p1,
	const PrimitivePatch<FaceList2, PointField2>& p2,

	labelList& p1PointLabels,
	labelList& p2PointLabels
)
{
	p1PointLabels.setSize(p1.nPoints());
	p2PointLabels.setSize(p1.nPoints());

	label nMatches = 0;

	forAll(p1.meshPoints(), pointi)
	{
		label meshPointi = p1.meshPoints()[pointi];

		Map<label>::const_iterator iter = p2.meshPointMap().find
		(
			meshPointi
		);

		if (iter != p2.meshPointMap().end())
		{
			p1PointLabels[nMatches] = pointi;
			p2PointLabels[nMatches] = iter();
			nMatches++;
		}
	}
	p1PointLabels.setSize(nMatches);
	p2PointLabels.setSize(nMatches);
}


template<class FaceList1, class PointField1, class FaceList2, class PointField2>
void tnbLib::PatchTools::matchEdges
(
	const PrimitivePatch<FaceList1, PointField1>& p1,
	const PrimitivePatch<FaceList2, PointField2>& p2,

	labelList& p1EdgeLabels,
	labelList& p2EdgeLabels,
	PackedBoolList& sameOrientation
)
{
	p1EdgeLabels.setSize(p1.nEdges());
	p2EdgeLabels.setSize(p1.nEdges());
	sameOrientation.setSize(p1.nEdges());
	sameOrientation = 0;

	label nMatches = 0;

	EdgeMap<label> edgeToIndex(2 * p1.nEdges());
	forAll(p1.edges(), edgeI)
	{
		const edge& e = p1.edges()[edgeI];
		const edge meshE
		(
			p1.meshPoints()[e[0]],
			p1.meshPoints()[e[1]]
		);
		edgeToIndex.insert(meshE, edgeI);
	}

	forAll(p2.edges(), edgeI)
	{
		const edge& e = p2.edges()[edgeI];
		const edge meshE(p2.meshPoints()[e[0]], p2.meshPoints()[e[1]]);

		EdgeMap<label>::const_iterator iter = edgeToIndex.find(meshE);

		if (iter != edgeToIndex.end())
		{
			p1EdgeLabels[nMatches] = iter();
			p2EdgeLabels[nMatches] = edgeI;
			sameOrientation[nMatches] = (meshE[0] == iter.key()[0]);
			nMatches++;
		}
	}
	p1EdgeLabels.setSize(nMatches);
	p2EdgeLabels.setSize(nMatches);
	sameOrientation.setSize(nMatches);
}


// ************************************************************************* //