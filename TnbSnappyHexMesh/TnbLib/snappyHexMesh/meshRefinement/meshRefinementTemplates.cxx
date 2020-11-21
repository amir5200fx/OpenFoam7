#include <meshRefinement.hxx>

//#include <fvMesh.hxx>
//#include <globalIndex.hxx>
//#include <syncTools.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//// Add a T entry
//template<class T> void tnbLib::meshRefinement::updateList
//(
//	const labelList& newToOld,
//	const T& nullValue,
//	List<T>& elems
//)
//{
//	List<T> newElems(newToOld.size(), nullValue);
//
//	forAll(newElems, i)
//	{
//		label oldI = newToOld[i];
//
//		if (oldI >= 0)
//		{
//			newElems[i] = elems[oldI];
//		}
//	}
//
//	elems.transfer(newElems);
//}
//
//
//template<class T>
//T tnbLib::meshRefinement::gAverage
//(
//	const PackedBoolList& isMasterElem,
//	const UList<T>& values
//)
//{
//	if (values.size() != isMasterElem.size())
//	{
//		FatalErrorInFunction
//			<< "Number of elements in list " << values.size()
//			<< " does not correspond to number of elements in isMasterElem "
//			<< isMasterElem.size()
//			<< exit(FatalError);
//	}
//
//	T sum = Zero;
//	label n = 0;
//
//	forAll(values, i)
//	{
//		if (isMasterElem[i])
//		{
//			sum += values[i];
//			n++;
//		}
//	}
//
//	reduce(sum, sumOp<T>());
//	reduce(n, sumOp<label>());
//
//	if (n > 0)
//	{
//		return sum / n;
//	}
//	else
//	{
//		return pTraits<T>::max;
//	}
//}
//
//
//// Compare two lists over all boundary faces
//template<class T>
//void tnbLib::meshRefinement::testSyncBoundaryFaceList
//(
//	const scalar tol,
//	const string& msg,
//	const UList<T>& faceData,
//	const UList<T>& syncedFaceData
//) const
//{
//	label nBFaces = mesh_.nFaces() - mesh_.nInternalFaces();
//
//	if (faceData.size() != nBFaces || syncedFaceData.size() != nBFaces)
//	{
//		FatalErrorInFunction
//			<< "Boundary faces:" << nBFaces
//			<< " faceData:" << faceData.size()
//			<< " syncedFaceData:" << syncedFaceData.size()
//			<< abort(FatalError);
//	}
//
//	const polyBoundaryMesh& patches = mesh_.boundaryMesh();
//
//	forAll(patches, patchi)
//	{
//		const polyPatch& pp = patches[patchi];
//
//		label bFacei = pp.start() - mesh_.nInternalFaces();
//
//		forAll(pp, i)
//		{
//			const T& data = faceData[bFacei];
//			const T& syncData = syncedFaceData[bFacei];
//
//			if (mag(data - syncData) > tol)
//			{
//				label facei = pp.start() + i;
//
//				FatalErrorInFunction
//					<< msg
//					<< "patchFace:" << i
//					<< " face:" << facei
//					<< " fc:" << mesh_.faceCentres()[facei]
//					<< " patch:" << pp.name()
//					<< " faceData:" << data
//					<< " syncedFaceData:" << syncData
//					<< " diff:" << mag(data - syncData)
//					<< abort(FatalError);
//			}
//
//			bFacei++;
//		}
//	}
//}
//
//
//// Print list sorted by coordinates. Used for comparing non-parallel v.s.
//// parallel operation
//template<class T>
//void tnbLib::meshRefinement::collectAndPrint
//(
//	const UList<point>& points,
//	const UList<T>& data
//)
//{
//	globalIndex globalPoints(points.size());
//
//	pointField allPoints;
//	globalPoints.gather
//	(
//		Pstream::worldComm,
//		identity(Pstream::nProcs()),
//		points,
//		allPoints,
//		UPstream::msgType(),
//		Pstream::commsTypes::blocking
//	);
//
//	List<T> allData;
//	globalPoints.gather
//	(
//		Pstream::worldComm,
//		identity(Pstream::nProcs()),
//		data,
//		allData,
//		UPstream::msgType(),
//		Pstream::commsTypes::blocking
//	);
//
//
//	scalarField magAllPoints(mag(allPoints - point(-0.317, 0.117, 0.501)));
//
//	labelList visitOrder;
//	sortedOrder(magAllPoints, visitOrder);
//	forAll(visitOrder, i)
//	{
//		label allPointi = visitOrder[i];
//		Info << allPoints[allPointi] << " : " << allData[allPointi]
//			<< endl;
//	}
//}
//
//
//template<class Enum>
//int tnbLib::meshRefinement::readFlags
//(
//	const Enum& namedEnum,
//	const wordList& words
//)
//{
//	int flags = 0;
//
//	forAll(words, i)
//	{
//		int index = namedEnum[words[i]];
//		int val = 1 << index;
//		flags |= val;
//	}
//	return flags;
//}
//
//
//template<class Type>
//void tnbLib::meshRefinement::weightedSum
//(
//	const polyMesh& mesh,
//	const PackedBoolList& isMasterEdge,
//	const labelList& meshPoints,
//	const edgeList& edges,
//	const scalarField& edgeWeights,
//	const Field<Type>& pointData,
//	Field<Type>& sum
//)
//{
//	if
//		(
//			edges.size() != isMasterEdge.size()
//			|| edges.size() != edgeWeights.size()
//			|| meshPoints.size() != pointData.size()
//			)
//	{
//		FatalErrorInFunction
//			<< "Inconsistent sizes for edge or point data:"
//			<< " isMasterEdge:" << isMasterEdge.size()
//			<< " edgeWeights:" << edgeWeights.size()
//			<< " edges:" << edges.size()
//			<< " pointData:" << pointData.size()
//			<< " meshPoints:" << meshPoints.size()
//			<< abort(FatalError);
//	}
//
//	sum.setSize(meshPoints.size());
//	sum = Zero;
//
//	forAll(edges, edgeI)
//	{
//		if (isMasterEdge[edgeI])
//		{
//			const edge& e = edges[edgeI];
//
//			scalar eWeight = edgeWeights[edgeI];
//
//			label v0 = e[0];
//			label v1 = e[1];
//
//			sum[v0] += eWeight * pointData[v1];
//			sum[v1] += eWeight * pointData[v0];
//		}
//	}
//
//	syncTools::syncPointList
//	(
//		mesh,
//		meshPoints,
//		sum,
//		plusEqOp<Type>(),
//		Type(Zero)     // null value
//	);
//}
//
//
//// ************************************************************************* //