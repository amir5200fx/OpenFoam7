#pragma once
#include <polyMesh.hxx>
#include <mapDistribute.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class CombineOp, class TransformOp>
void tnbLib::globalMeshData::syncData
(
	List<Type>& elems,
	const labelListList& slaves,
	const labelListList& transformedSlaves,
	const mapDistribute& slavesMap,
	const globalIndexAndTransform& transforms,
	const CombineOp& cop,
	const TransformOp& top
)
{
	// Pull slave data onto master
	slavesMap.distribute(transforms, elems, top);

	// Combine master data with slave data
	forAll(slaves, i)
	{
		Type& elem = elems[i];

		const labelList& slavePoints = slaves[i];
		label nTransformSlavePoints =
			(
				transformedSlaves.size() == 0
				? 0
				: transformedSlaves[i].size()
				);

		if (slavePoints.size() + nTransformSlavePoints > 0)
		{
			// Combine master with untransformed slave data
			forAll(slavePoints, j)
			{
				cop(elem, elems[slavePoints[j]]);
			}

			// Combine master with transformed slave data
			if (nTransformSlavePoints)
			{
				const labelList& transformSlavePoints = transformedSlaves[i];
				forAll(transformSlavePoints, j)
				{
					cop(elem, elems[transformSlavePoints[j]]);
				}
			}

			// Copy result back to slave slots
			forAll(slavePoints, j)
			{
				elems[slavePoints[j]] = elem;
			}
			if (nTransformSlavePoints)
			{
				const labelList& transformSlavePoints = transformedSlaves[i];
				forAll(transformSlavePoints, j)
				{
					elems[transformSlavePoints[j]] = elem;
				}
			}
		}
	}

	// Push slave-slot data back to slaves
	slavesMap.reverseDistribute
	(
		transforms,
		elems.size(),
		elems,
		top
	);
}


template<class Type, class CombineOp>
void tnbLib::globalMeshData::syncData
(
	List<Type>& elems,
	const labelListList& slaves,
	const labelListList& transformedSlaves,
	const mapDistribute& slavesMap,
	const CombineOp& cop
)
{
	// Pull slave data onto master
	slavesMap.distribute(elems);

	// Combine master data with slave data
	forAll(slaves, i)
	{
		Type& elem = elems[i];

		const labelList& slavePoints = slaves[i];
		label nTransformSlavePoints =
			(
				transformedSlaves.size() == 0
				? 0
				: transformedSlaves[i].size()
				);

		if (slavePoints.size() + nTransformSlavePoints > 0)
		{
			// Combine master with untransformed slave data
			forAll(slavePoints, j)
			{
				cop(elem, elems[slavePoints[j]]);
			}

			// Combine master with transformed slave data
			if (nTransformSlavePoints)
			{
				const labelList& transformSlavePoints = transformedSlaves[i];
				forAll(transformSlavePoints, j)
				{
					cop(elem, elems[transformSlavePoints[j]]);
				}
			}

			// Copy result back to slave slots
			forAll(slavePoints, j)
			{
				elems[slavePoints[j]] = elem;
			}
			if (nTransformSlavePoints)
			{
				const labelList& transformSlavePoints = transformedSlaves[i];
				forAll(transformSlavePoints, j)
				{
					elems[transformSlavePoints[j]] = elem;
				}
			}
		}
	}

	// Push slave-slot data back to slaves
	slavesMap.reverseDistribute(elems.size(), elems);
}


template<class Type, class CombineOp, class TransformOp>
void tnbLib::globalMeshData::syncPointData
(
	List<Type>& pointData,
	const CombineOp& cop,
	const TransformOp& top
) const
{
	if (pointData.size() != mesh_.nPoints())
	{
		FatalErrorInFunction
			<< "Number of elements in data:" << pointData.size()
			<< " differs from number of points in mesh:" << mesh_.nPoints()
			<< abort(FatalError);
	}

	// Transfer onto coupled patch
	const indirectPrimitivePatch& cpp = coupledPatch();
	List<Type> cppFld(UIndirectList<Type>(pointData, cpp.meshPoints()));

	syncData
	(
		cppFld,
		globalPointSlaves(),
		globalPointTransformedSlaves(),
		globalPointSlavesMap(),
		globalTransforms(),
		cop,
		top
	);

	// Extract back onto mesh
	forAll(cpp.meshPoints(), i)
	{
		pointData[cpp.meshPoints()[i]] = cppFld[i];
	}
}


// ************************************************************************* //