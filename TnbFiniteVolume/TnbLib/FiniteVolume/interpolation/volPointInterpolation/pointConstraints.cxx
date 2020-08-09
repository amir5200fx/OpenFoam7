#include <pointConstraints.hxx>

#include <emptyPointPatch.hxx>
#include <polyMesh.hxx>
#include <pointMesh.hxx>
#include <globalMeshData.hxx>
#include <twoDPointCorrector.hxx>

#include <mapDistribute.hxx>  // added by amir
#include <pointFields.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointConstraints, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pointConstraints::makePatchPatchAddressing()
{
	if (debug)
	{
		Pout << "pointConstraints::makePatchPatchAddressing() : "
			<< "constructing boundary addressing"
			<< endl << incrIndent;
	}

	const pointMesh& pMesh = mesh();
	const polyMesh& mesh = pMesh();

	const pointBoundaryMesh& pbm = pMesh.boundary();
	const polyBoundaryMesh& bm = mesh.boundaryMesh();


	// first count the total number of patch-patch points

	label nPatchPatchPoints = 0;

	forAll(pbm, patchi)
	{
		if (!isA<emptyPointPatch>(pbm[patchi]) && !pbm[patchi].coupled())
		{
			const labelList& bp = bm[patchi].boundaryPoints();

			nPatchPatchPoints += bp.size();

			if (debug)
			{
				Pout << indent << "On patch:" << pbm[patchi].name()
					<< " nBoundaryPoints:" << bp.size() << endl;
			}
		}
	}

	if (debug)
	{
		Pout << indent << "Found nPatchPatchPoints:" << nPatchPatchPoints
			<< endl;
	}


	// Go through all patches and mark up the external edge points
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// From meshpoint to index in patchPatchPointConstraints_.
	Map<label> patchPatchPointSet(2 * nPatchPatchPoints);

	// Constraints (initialised to unconstrained)
	patchPatchPointConstraints_.setSize(nPatchPatchPoints);
	patchPatchPointConstraints_ = pointConstraint();

	// From constraint index to mesh point
	labelList patchPatchPoints(nPatchPatchPoints);

	label pppi = 0;

	forAll(pbm, patchi)
	{
		if (!isA<emptyPointPatch>(pbm[patchi]) && !pbm[patchi].coupled())
		{
			const labelList& bp = bm[patchi].boundaryPoints();
			const labelList& meshPoints = pbm[patchi].meshPoints();

			forAll(bp, pointi)
			{
				label ppp = meshPoints[bp[pointi]];

				Map<label>::iterator iter = patchPatchPointSet.find(ppp);

				label constraintI = -1;

				if (iter == patchPatchPointSet.end())
				{
					patchPatchPointSet.insert(ppp, pppi);
					patchPatchPoints[pppi] = ppp;
					constraintI = pppi++;
				}
				else
				{
					constraintI = iter();
				}

				// Apply to patch constraints
				pbm[patchi].applyConstraint
				(
					bp[pointi],
					patchPatchPointConstraints_[constraintI]
				);
			}
		}
	}

	if (debug)
	{
		Pout << indent << "Have (local) constrained points:"
			<< nPatchPatchPoints << endl;
	}


	// Extend set with constraints across coupled points
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	{
		const globalMeshData& gd = mesh.globalData();
		const labelListList& globalPointSlaves = gd.globalPointSlaves();
		const mapDistribute& globalPointSlavesMap = gd.globalPointSlavesMap();
		const Map<label>& cpPointMap = gd.coupledPatch().meshPointMap();
		const labelList& cpMeshPoints = gd.coupledPatch().meshPoints();

		// Constraints on coupled points
		List<pointConstraint> constraints
		(
			globalPointSlavesMap.constructSize()
		);

		// Copy from patchPatch constraints into coupledConstraints.
		forAll(pbm, patchi)
		{
			if (!isA<emptyPointPatch>(pbm[patchi]) && !pbm[patchi].coupled())
			{
				const labelList& bp = bm[patchi].boundaryPoints();
				const labelList& meshPoints = pbm[patchi].meshPoints();

				forAll(bp, pointi)
				{
					label ppp = meshPoints[bp[pointi]];

					Map<label>::const_iterator fnd = cpPointMap.find(ppp);
					if (fnd != cpPointMap.end())
					{
						// Can just copy (instead of apply) constraint
						// will already be consistent across multiple patches.
						constraints[fnd()] = patchPatchPointConstraints_
							[
								patchPatchPointSet[ppp]
							];
					}
				}
			}
		}

		// Exchange data
		globalPointSlavesMap.distribute(constraints);

		// Combine master with slave constraints
		forAll(globalPointSlaves, pointi)
		{
			const labelList& slaves = globalPointSlaves[pointi];

			// Combine master constraint with slave constraints
			forAll(slaves, i)
			{
				constraints[pointi].combine(constraints[slaves[i]]);
			}
			// Duplicate master constraint into slave slots
			forAll(slaves, i)
			{
				constraints[slaves[i]] = constraints[pointi];
			}
		}

		// Send back
		globalPointSlavesMap.reverseDistribute
		(
			cpMeshPoints.size(),
			constraints
		);

		// Add back into patchPatch constraints
		forAll(constraints, coupledPointi)
		{
			if (constraints[coupledPointi].first() != 0)
			{
				label meshPointi = cpMeshPoints[coupledPointi];

				Map<label>::iterator iter = patchPatchPointSet.find(meshPointi);

				label constraintI = -1;

				if (iter == patchPatchPointSet.end())
				{
					// Pout<< indent << "on meshpoint:" << meshPointi
					//    << " coupled:" << coupledPointi
					//    << " at:" << mesh.points()[meshPointi]
					//    << " have new constraint:"
					//    << constraints[coupledPointi]
					//    << endl;

					// Allocate new constraint
					if (patchPatchPoints.size() <= pppi)
					{
						patchPatchPoints.setSize(pppi + 100);
					}
					patchPatchPointSet.insert(meshPointi, pppi);
					patchPatchPoints[pppi] = meshPointi;
					constraintI = pppi++;
				}
				else
				{
					// Pout<< indent << "on meshpoint:" << meshPointi
					//    << " coupled:" << coupledPointi
					//    << " at:" << mesh.points()[meshPointi]
					//    << " have possibly extended constraint:"
					//    << constraints[coupledPointi]
					//    << endl;

					constraintI = iter();
				}

				// Combine (new or existing) constraint with one
				// on coupled.
				patchPatchPointConstraints_[constraintI].combine
				(
					constraints[coupledPointi]
				);
			}
		}
	}



	nPatchPatchPoints = pppi;
	patchPatchPoints.setSize(nPatchPatchPoints);
	patchPatchPointConstraints_.setSize(nPatchPatchPoints);


	if (debug)
	{
		Pout << indent << "Have (global) constrained points:"
			<< nPatchPatchPoints << endl;
	}


	// Copy out all non-trivial constraints
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	patchPatchPointConstraintPoints_.setSize(nPatchPatchPoints);
	patchPatchPointConstraintTensors_.setSize(nPatchPatchPoints);

	label nConstraints = 0;

	forAll(patchPatchPointConstraints_, i)
	{
		// Note: check for more than zero constraints. (could check for
		//       more than one constraint but what about coupled points that
		//       inherit the constraintness)
		if (patchPatchPointConstraints_[i].first() != 0)
		{
			patchPatchPointConstraintPoints_[nConstraints] =
				patchPatchPoints[i];

			patchPatchPointConstraintTensors_[nConstraints] =
				patchPatchPointConstraints_[i].constraintTransformation();

			nConstraints++;
		}
	}

	if (debug)
	{
		Pout << indent << "Have non-trivial constrained points:"
			<< nConstraints << endl;
	}

	patchPatchPointConstraints_.setSize(nConstraints);
	patchPatchPointConstraintPoints_.setSize(nConstraints);
	patchPatchPointConstraintTensors_.setSize(nConstraints);


	if (debug)
	{
		Pout << decrIndent
			<< "pointConstraints::makePatchPatchAddressing() : "
			<< "finished constructing boundary addressing"
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::pointConstraints::pointConstraints(const pointMesh& pm)
	:
	MeshObject<pointMesh, tnbLib::UpdateableMeshObject, pointConstraints>(pm)
{
	if (debug)
	{
		Pout << "pointConstraints::pointConstraints(const pointMesh&): "
			<< "Constructing from pointMesh " << pm.name()
			<< endl;
	}

	makePatchPatchAddressing();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::pointConstraints::~pointConstraints()
{
	if (debug)
	{
		Pout << "pointConstraints::~pointConstraints()" << endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pointConstraints::updateMesh(const mapPolyMesh&)
{
	makePatchPatchAddressing();
}


bool tnbLib::pointConstraints::movePoints()
{
	return true;
}


void tnbLib::pointConstraints::constrainDisplacement
(
	pointVectorField& pf,
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
		pf.mesh()(),
		pf.primitiveFieldRef(),
		maxMagSqrEqOp<vector>()
	);

	// Apply multiple constraints on edge/corner points
	constrainCorners(pf);

	// Apply any 2D motion constraints (or should they go before
	// corner constraints?)
	twoDPointCorrector::New(mesh()()).correctDisplacement
	(
		mesh()().points(),
		pf.primitiveFieldRef()
	);

	if (overrideFixedValue)
	{
		setPatchFields(pf);
	}
}


template<>
void tnbLib::pointConstraints::constrainCorners<tnbLib::scalar>
(
	GeometricField<scalar, pointPatchField, pointMesh>& pf
	) const
{}


template<>
void tnbLib::pointConstraints::constrainCorners<tnbLib::label>
(
	GeometricField<label, pointPatchField, pointMesh>& pf
	) const
{}


// ************************************************************************* //