#pragma once
#include <polyMesh.hxx>
#include <indirectPrimitivePatch.hxx>
#include <globalMeshData.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::tmp<tnbLib::pointField> tnbLib::PatchTools::pointNormals
(
	const polyMesh& mesh,
	const PrimitivePatch<FaceList, PointField>& p
)
{
	const globalMeshData& globalData = mesh.globalData();
	const indirectPrimitivePatch& coupledPatch = globalData.coupledPatch();
	const Map<label>& coupledPatchMP = coupledPatch.meshPointMap();
	const mapDistribute& map = globalData.globalPointSlavesMap();
	const globalIndexAndTransform& transforms =
		globalData.globalTransforms();




	// Combine normals. Note: do on all master points. Cannot just use
	// patch points since the master point does not have to be on the
	// patch!

	pointField coupledPointNormals(map.constructSize(), Zero);

	{
		// Collect local pointFaces (sized on patch points only)
		List<List<point>> pointFaceNormals(map.constructSize());
		forAll(p.meshPoints(), patchPointi)
		{
			label meshPointi = p.meshPoints()[patchPointi];
			Map<label>::const_iterator fnd = coupledPatchMP.find(meshPointi);
			if (fnd != coupledPatchMP.end())
			{
				label coupledPointi = fnd();

				List<point>& pNormals = pointFaceNormals[coupledPointi];
				const labelList& pFaces = p.pointFaces()[patchPointi];
				pNormals.setSize(pFaces.size());
				forAll(pFaces, i)
				{
					pNormals[i] = p.faceNormals()[pFaces[i]];
				}
			}
		}


		// Pull remote data into local slots
		map.distribute
		(
			transforms,
			pointFaceNormals,
			mapDistribute::transform()
		);


		// Combine all face normals (-local, -remote,untransformed,
		//  -remote,transformed)

		const labelListList& slaves = globalData.globalPointSlaves();
		const labelListList& transformedSlaves =
			globalData.globalPointTransformedSlaves();

		forAll(slaves, coupledPointi)
		{
			const labelList& slaveSlots = slaves[coupledPointi];
			const labelList& transformedSlaveSlots =
				transformedSlaves[coupledPointi];

			point& n = coupledPointNormals[coupledPointi];

			// Local entries
			const List<point>& local = pointFaceNormals[coupledPointi];

			label nFaces =
				local.size()
				+ slaveSlots.size()
				+ transformedSlaveSlots.size();

			n = sum(local);

			// Add any remote face normals
			forAll(slaveSlots, i)
			{
				n += sum(pointFaceNormals[slaveSlots[i]]);
			}
			forAll(transformedSlaveSlots, i)
			{
				n += sum(pointFaceNormals[transformedSlaveSlots[i]]);
			}

			if (nFaces >= 1)
			{
				n /= mag(n) + vSmall;
			}

			// Put back into slave slots
			forAll(slaveSlots, i)
			{
				coupledPointNormals[slaveSlots[i]] = n;
			}
			forAll(transformedSlaveSlots, i)
			{
				coupledPointNormals[transformedSlaveSlots[i]] = n;
			}
		}


		// Send back
		map.reverseDistribute
		(
			transforms,
			coupledPointNormals.size(),
			coupledPointNormals,
			mapDistribute::transform()
		);
	}


	// 1. Start off with local normals (note:without calculating pointNormals
	//    to avoid them being stored)

	tmp<pointField> textrudeN(new pointField(p.nPoints(), Zero));
	pointField& extrudeN = textrudeN.ref();
	{
		const faceList& localFaces = p.localFaces();
		const vectorField& faceNormals = p.faceNormals();

		forAll(localFaces, facei)
		{
			const face& f = localFaces[facei];
			const vector& n = faceNormals[facei];
			forAll(f, fp)
			{
				extrudeN[f[fp]] += n;
			}
		}
		extrudeN /= mag(extrudeN) + vSmall;
	}


	// 2. Override patch normals on coupled points
	forAll(p.meshPoints(), patchPointi)
	{
		label meshPointi = p.meshPoints()[patchPointi];
		Map<label>::const_iterator fnd = coupledPatchMP.find(meshPointi);
		if (fnd != coupledPatchMP.end())
		{
			label coupledPointi = fnd();
			extrudeN[patchPointi] = coupledPointNormals[coupledPointi];
		}
	}

	return textrudeN;
}


template<class FaceList, class PointField>
tnbLib::tmp<tnbLib::pointField> tnbLib::PatchTools::edgeNormals
(
	const polyMesh& mesh,
	const PrimitivePatch<FaceList, PointField>& p,
	const labelList& patchEdges,
	const labelList& coupledEdges
)
{
	// 1. Start off with local normals

	tmp<pointField> tedgeNormals(new pointField(p.nEdges(), Zero));
	pointField& edgeNormals = tedgeNormals.ref();
	{
		const labelListList& edgeFaces = p.edgeFaces();
		const vectorField& faceNormals = p.faceNormals();

		forAll(edgeFaces, edgeI)
		{
			const labelList& eFaces = edgeFaces[edgeI];
			forAll(eFaces, i)
			{
				edgeNormals[edgeI] += faceNormals[eFaces[i]];
			}
		}
		edgeNormals /= mag(edgeNormals) + vSmall;
	}



	const globalMeshData& globalData = mesh.globalData();
	const mapDistribute& map = globalData.globalEdgeSlavesMap();


	// Convert patch-edge data into cpp-edge data
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//- Construct with all data in consistent orientation
	pointField cppEdgeData(map.constructSize(), Zero);

	forAll(patchEdges, i)
	{
		label patchEdgeI = patchEdges[i];
		label coupledEdgeI = coupledEdges[i];
		cppEdgeData[coupledEdgeI] = edgeNormals[patchEdgeI];
	}


	// Synchronise
	// ~~~~~~~~~~~

	globalData.syncData
	(
		cppEdgeData,
		globalData.globalEdgeSlaves(),
		globalData.globalEdgeTransformedSlaves(),
		map,
		globalData.globalTransforms(),
		plusEqOp<point>(),              // add since normalised later on
		mapDistribute::transform()
	);
	cppEdgeData /= mag(cppEdgeData) + vSmall;


	// Back from cpp-edge to patch-edge data
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	forAll(patchEdges, i)
	{
		label patchEdgeI = patchEdges[i];
		label coupledEdgeI = coupledEdges[i];
		edgeNormals[patchEdgeI] = cppEdgeData[coupledEdgeI];
	}

	return tedgeNormals;
}


// ************************************************************************* //