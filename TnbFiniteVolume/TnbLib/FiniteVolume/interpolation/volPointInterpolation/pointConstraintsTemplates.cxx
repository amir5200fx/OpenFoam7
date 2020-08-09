#include <pointConstraints.hxx>

#include <pointFields.hxx>
#include <valuePointPatchFields.hxx>

#include <indirectPrimitivePatch.hxx>  // added by amir
#include <mapDistribute.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class CombineOp>
void tnbLib::pointConstraints::syncUntransformedData
(
	const polyMesh& mesh,
	List<Type>& pointData,
	const CombineOp& cop
)
{
	// Transfer onto coupled patch
	const globalMeshData& gmd = mesh.globalData();
	const indirectPrimitivePatch& cpp = gmd.coupledPatch();
	const labelList& meshPoints = cpp.meshPoints();

	const mapDistribute& slavesMap = gmd.globalCoPointSlavesMap();
	const labelListList& slaves = gmd.globalCoPointSlaves();

	List<Type> elems(slavesMap.constructSize());
	forAll(meshPoints, i)
	{
		elems[i] = pointData[meshPoints[i]];
	}

	// Pull slave data onto master. No need to update transformed slots.
	slavesMap.distribute(elems, false);

	// Combine master data with slave data
	forAll(slaves, i)
	{
		Type& elem = elems[i];

		const labelList& slavePoints = slaves[i];

		// Combine master with untransformed slave data
		forAll(slavePoints, j)
		{
			cop(elem, elems[slavePoints[j]]);
		}

		// Copy result back to slave slots
		forAll(slavePoints, j)
		{
			elems[slavePoints[j]] = elem;
		}
	}

	// Push slave-slot data back to slaves
	slavesMap.reverseDistribute(elems.size(), elems, false);

	// Extract back onto mesh
	forAll(meshPoints, i)
	{
		pointData[meshPoints[i]] = elems[i];
	}
}


template<class Type>
void tnbLib::pointConstraints::setPatchFields
(
	GeometricField<Type, pointPatchField, pointMesh>& pf
)
{
	typename GeometricField<Type, pointPatchField, pointMesh>::
		Boundary& pfbf = pf.boundaryFieldRef();

	forAll(pfbf, patchi)
	{
		pointPatchField<Type>& ppf = pfbf[patchi];

		if (isA<valuePointPatchField<Type>>(ppf))
		{
			refCast<valuePointPatchField<Type>>(ppf) =
				ppf.patchInternalField();
		}
	}
}


template<class Type>
void tnbLib::pointConstraints::constrainCorners
(
	GeometricField<Type, pointPatchField, pointMesh>& pf
) const
{
	forAll(patchPatchPointConstraintPoints_, pointi)
	{
		pf[patchPatchPointConstraintPoints_[pointi]] = transform
		(
			patchPatchPointConstraintTensors_[pointi],
			pf[patchPatchPointConstraintPoints_[pointi]]
		);
	}
}


template<class Type>
void tnbLib::pointConstraints::constrain
(
	GeometricField<Type, pointPatchField, pointMesh>& pf,
	const bool overrideFixedValue
) const
{
	// Override constrained pointPatchField types with the constraint value.
	// This relies on only constrained pointPatchField implementing the evaluate
	// function
	pf.correctBoundaryConditions();

	// Sync any dangling points
	syncUntransformedData
	(
		mesh()(),
		pf.primitiveFieldRef(),
		maxMagSqrEqOp<Type>()
	);

	// Apply multiple constraints on edge/corner points
	constrainCorners(pf);

	if (overrideFixedValue)
	{
		setPatchFields(pf);
	}
}


// ************************************************************************* //