#pragma once
#include <polyMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::particle::stationaryTetGeometry
(
	vector& centre,
	vector& base,
	vector& vertex1,
	vector& vertex2
) const
{
	const triFace triIs(currentTetIndices().faceTriIs(mesh_));
	const vectorField& ccs = mesh_.cellCentres();
	const pointField& pts = mesh_.points();

	centre = ccs[celli_];
	base = pts[triIs[0]];
	vertex1 = pts[triIs[1]];
	vertex2 = pts[triIs[2]];
}


inline tnbLib::barycentricTensor tnbLib::particle::stationaryTetTransform() const
{
	vector centre, base, vertex1, vertex2;
	stationaryTetGeometry(centre, base, vertex1, vertex2);

	return barycentricTensor(centre, base, vertex1, vertex2);
}


inline void tnbLib::particle::movingTetGeometry
(
	const scalar fraction,
	Pair<vector>& centre,
	Pair<vector>& base,
	Pair<vector>& vertex1,
	Pair<vector>& vertex2
) const
{
	const triFace triIs(currentTetIndices().faceTriIs(mesh_));
	const pointField& ptsOld = mesh_.oldPoints();
	const pointField& ptsNew = mesh_.points();
	const vector ccOld = mesh_.oldCellCentres()[celli_];
	const vector ccNew = mesh_.cellCentres()[celli_];

	// Old and new points and cell centres are not sub-cycled. If we are sub-
	// cycling, then we have to account for the timestep change here by
	// modifying the fractions that we take of the old and new geometry.
	const Pair<scalar> s = stepFractionSpan();
	const scalar f0 = s[0] + stepFraction_ * s[1], f1 = fraction * s[1];

	centre[0] = ccOld + f0 * (ccNew - ccOld);
	base[0] = ptsOld[triIs[0]] + f0 * (ptsNew[triIs[0]] - ptsOld[triIs[0]]);
	vertex1[0] = ptsOld[triIs[1]] + f0 * (ptsNew[triIs[1]] - ptsOld[triIs[1]]);
	vertex2[0] = ptsOld[triIs[2]] + f0 * (ptsNew[triIs[2]] - ptsOld[triIs[2]]);

	centre[1] = f1 * (ccNew - ccOld);
	base[1] = f1 * (ptsNew[triIs[0]] - ptsOld[triIs[0]]);
	vertex1[1] = f1 * (ptsNew[triIs[1]] - ptsOld[triIs[1]]);
	vertex2[1] = f1 * (ptsNew[triIs[2]] - ptsOld[triIs[2]]);
}


inline tnbLib::Pair<tnbLib::barycentricTensor> tnbLib::particle::movingTetTransform
(
	const scalar fraction
) const
{
	Pair<vector> centre, base, vertex1, vertex2;
	movingTetGeometry(fraction, centre, base, vertex1, vertex2);

	return
		Pair<barycentricTensor>
		(
			barycentricTensor(centre[0], base[0], vertex1[0], vertex2[0]),
			barycentricTensor(centre[1], base[1], vertex1[1], vertex2[1])
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::particle::getNewParticleID() const
{
	label id = particleCount_++;

	if (id == labelMax)
	{
		WarningInFunction
			<< "Particle counter has overflowed. This might cause problems"
			<< " when reconstructing particle tracks." << endl;
	}
	return id;
}


inline const tnbLib::polyMesh& tnbLib::particle::mesh() const
{
	return mesh_;
}


inline const tnbLib::barycentric& tnbLib::particle::coordinates() const
{
	return coordinates_;
}


inline tnbLib::label tnbLib::particle::cell() const
{
	return celli_;
}


inline tnbLib::label tnbLib::particle::tetFace() const
{
	return tetFacei_;
}


inline tnbLib::label tnbLib::particle::tetPt() const
{
	return tetPti_;
}


inline tnbLib::label tnbLib::particle::face() const
{
	return facei_;
}


inline tnbLib::scalar tnbLib::particle::stepFraction() const
{
	return stepFraction_;
}


inline tnbLib::scalar& tnbLib::particle::stepFraction()
{
	return stepFraction_;
}


inline tnbLib::label tnbLib::particle::origProc() const
{
	return origProc_;
}


inline tnbLib::label& tnbLib::particle::origProc()
{
	return origProc_;
}


inline tnbLib::label tnbLib::particle::origId() const
{
	return origId_;
}


inline tnbLib::label& tnbLib::particle::origId()
{
	return origId_;
}


inline tnbLib::Pair<tnbLib::scalar> tnbLib::particle::stepFractionSpan() const
{
	if (mesh_.time().subCycling())
	{
		const TimeState& tsNew = mesh_.time();
		const TimeState& tsOld = mesh_.time().prevTimeState();

		const scalar tFrac =
			(
			(tsNew.value() - tsNew.deltaTValue())
				- (tsOld.value() - tsOld.deltaTValue())
				) / tsOld.deltaTValue();

		const scalar dtFrac = tsNew.deltaTValue() / tsOld.deltaTValue();

		return Pair<scalar>(tFrac, dtFrac);
	}
	else
	{
		return Pair<scalar>(0, 1);
	}
}


inline tnbLib::scalar tnbLib::particle::currentTimeFraction() const
{
	const Pair<scalar> s = stepFractionSpan();

	return s[0] + stepFraction_ * s[1];
}


inline tnbLib::tetIndices tnbLib::particle::currentTetIndices() const
{
	return tetIndices(celli_, tetFacei_, tetPti_);
}


inline tnbLib::barycentricTensor tnbLib::particle::currentTetTransform() const
{
	if (mesh_.moving() && stepFraction_ != 1)
	{
		return movingTetTransform(0)[0];
	}
	else
	{
		return stationaryTetTransform();
	}
}


inline tnbLib::vector tnbLib::particle::normal() const
{
	return currentTetIndices().faceTri(mesh_).normal();
}


inline bool tnbLib::particle::onFace() const
{
	return facei_ >= 0;
}


inline bool tnbLib::particle::onInternalFace() const
{
	return onFace() && mesh_.isInternalFace(facei_);
}


inline bool tnbLib::particle::onBoundaryFace() const
{
	return onFace() && !mesh_.isInternalFace(facei_);
}


inline tnbLib::label tnbLib::particle::patch() const
{
	return onFace() ? mesh_.boundaryMesh().whichPatch(facei_) : -1;
}


inline tnbLib::vector tnbLib::particle::position() const
{
	return currentTetTransform() & coordinates_;
}


inline void tnbLib::particle::reset()
{
	stepFraction_ = 0;
	nBehind_ = 0;
	behind_ = 0;
}


void tnbLib::particle::patchData(vector& normal, vector& displacement) const
{
	if (!onBoundaryFace())
	{
		FatalErrorInFunction
			<< "Patch data was requested for a particle that isn't on a patch"
			<< exit(FatalError);
	}

	if (mesh_.moving() && stepFraction_ != 1)
	{
		Pair<vector> centre, base, vertex1, vertex2;
		movingTetGeometry(1, centre, base, vertex1, vertex2);

		normal = triPointRef(base[0], vertex1[0], vertex2[0]).normal();

		// Interpolate the motion of the three face vertices to the current
		// coordinates
		displacement =
			coordinates_.b()*base[1]
			+ coordinates_.c()*vertex1[1]
			+ coordinates_.d()*vertex2[1];
	}
	else
	{
		vector centre, base, vertex1, vertex2;
		stationaryTetGeometry(centre, base, vertex1, vertex2);

		normal = triPointRef(base, vertex1, vertex2).normal();

		displacement = Zero;
	}
}


// ************************************************************************* //