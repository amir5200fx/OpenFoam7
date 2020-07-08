#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::tetIndices::cell() const
{
	return celli_;
}


inline tnbLib::label& tnbLib::tetIndices::cell()
{
	return celli_;
}


inline tnbLib::label tnbLib::tetIndices::face() const
{
	return facei_;
}


inline tnbLib::label& tnbLib::tetIndices::face()
{
	return facei_;
}


inline tnbLib::label tnbLib::tetIndices::tetPt() const
{
	return tetPti_;
}


inline tnbLib::label& tnbLib::tetIndices::tetPt()
{
	return tetPti_;
}


inline tnbLib::triFace tnbLib::tetIndices::faceTriIs(const polyMesh& mesh) const
{
	const tnbLib::face& f = mesh.faces()[face()];

	label faceBasePtI = mesh.tetBasePtIs()[face()];

	if (faceBasePtI < 0)
	{
		static label badFacei = -1;

		if (badFacei != face())
		{
			WarningInFunction
				<< "No base point for face " << face() << ", " << f
				<< ", produces a valid tet decomposition." << endl;

			badFacei = face();
		}

		faceBasePtI = 0;
	}

	label facePtI = (tetPt() + faceBasePtI) % f.size();
	label faceOtherPtI = f.fcIndex(facePtI);

	if (mesh.faceOwner()[face()] != cell())
	{
		Swap(facePtI, faceOtherPtI);
	}

	return triFace(f[faceBasePtI], f[facePtI], f[faceOtherPtI]);
}


inline tnbLib::tetPointRef tnbLib::tetIndices::tet(const polyMesh& mesh) const
{
	const pointField& meshPoints = mesh.points();
	const triFace tri = faceTriIs(mesh);

	return tetPointRef
	(
		mesh.cellCentres()[cell()],
		meshPoints[tri[0]],
		meshPoints[tri[1]],
		meshPoints[tri[2]]
	);
}


inline tnbLib::triPointRef tnbLib::tetIndices::faceTri(const polyMesh& mesh) const
{
	const pointField& meshPoints = mesh.points();
	const triFace tri = faceTriIs(mesh);

	return triPointRef
	(
		meshPoints[tri[0]],
		meshPoints[tri[1]],
		meshPoints[tri[2]]
	);
}


inline tnbLib::triPointRef tnbLib::tetIndices::oldFaceTri
(
	const polyMesh& mesh
) const
{
	const pointField& meshOldPoints = mesh.oldPoints();
	const triFace tri = faceTriIs(mesh);

	return triPointRef
	(
		meshOldPoints[tri[0]],
		meshOldPoints[tri[1]],
		meshOldPoints[tri[2]]
	);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::tetIndices::operator==(const tnbLib::tetIndices& rhs) const
{
	return
		cell() == rhs.cell()
		&& face() == rhs.face()
		&& tetPt() == rhs.tetPt();
}


inline bool tnbLib::tetIndices::operator!=(const tnbLib::tetIndices& rhs) const
{
	return !(*this == rhs);
}


// ************************************************************************* //