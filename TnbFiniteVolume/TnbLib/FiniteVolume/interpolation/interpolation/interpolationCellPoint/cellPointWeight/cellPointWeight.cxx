#include <cellPointWeight.hxx>

#include <polyMesh.hxx>
#include <polyMeshTetDecomposition.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

int tnbLib::cellPointWeight::debug(debug::debugSwitch("cellPointWeight", 0));

tnbLib::scalar tnbLib::cellPointWeight::tol(small);

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::cellPointWeight::findTetrahedron
(
	const polyMesh& mesh,
	const vector& position,
	const label celli
)
{
	if (debug)
	{
		Pout << nl << "tnbLib::cellPointWeight::findTetrahedron" << nl
			<< "position = " << position << nl
			<< "celli = " << celli << endl;
	}

	List<tetIndices> cellTets = polyMeshTetDecomposition::cellTetIndices
	(
		mesh,
		celli
	);

	const scalar cellVolume = mesh.cellVolumes()[celli];

	forAll(cellTets, tetI)
	{
		const tetIndices& tetIs = cellTets[tetI];

		// Barycentric coordinates of the position
		scalar det = tetIs.tet(mesh).pointToBarycentric(position, weights_);

		if (mag(det / cellVolume) > tol)
		{
			const scalar& u = weights_[0];
			const scalar& v = weights_[1];
			const scalar& w = weights_[2];

			if
				(
				(u + tol > 0)
					&& (v + tol > 0)
					&& (w + tol > 0)
					&& (u + v + w < 1 + tol)
					)
			{

				faceVertices_ = tetIs.faceTriIs(mesh);

				return;
			}
		}
	}

	// A suitable point in a tetrahedron was not found, find the
	// nearest.

	scalar minNearDist = vGreat;

	label nearestTetI = -1;

	forAll(cellTets, tetI)
	{
		const tetIndices& tetIs = cellTets[tetI];

		scalar nearDist = tetIs.tet(mesh).nearestPoint(position).distance();

		if (nearDist < minNearDist)
		{
			minNearDist = nearDist;

			nearestTetI = tetI;
		}
	}

	if (debug)
	{
		Pout << "cellPointWeight::findTetrahedron" << nl
			<< "    Tetrahedron search failed; using closest tet to point "
			<< position << nl
			<< "    cell: "
			<< celli << nl
			<< endl;
	}


	const tetIndices& tetIs = cellTets[nearestTetI];

	// Barycentric coordinates of the position, ignoring if the
	// determinant is suitable.  If not, the return from barycentric
	// to weights_ is safe.
	weights_ = tetIs.tet(mesh).pointToBarycentric(position);

	faceVertices_ = tetIs.faceTriIs(mesh);
}


void tnbLib::cellPointWeight::findTriangle
(
	const polyMesh& mesh,
	const vector& position,
	const label facei
)
{
	if (debug)
	{
		Pout << "\nbool tnbLib::cellPointWeight::findTriangle" << nl
			<< "position = " << position << nl
			<< "facei = " << facei << endl;
	}

	List<tetIndices> faceTets = polyMeshTetDecomposition::faceTetIndices
	(
		mesh,
		facei,
		mesh.faceOwner()[facei]
	);

	const scalar faceAreaSqr = magSqr(mesh.faceAreas()[facei]);

	forAll(faceTets, tetI)
	{
		const tetIndices& tetIs = faceTets[tetI];

		// Barycentric coordinates of the position
		barycentric2D triWeights;
		const scalar det =
			tetIs.faceTri(mesh).pointToBarycentric(position, triWeights);

		if (0.25*mag(det) / faceAreaSqr > tol)
		{
			const scalar& u = triWeights[0];
			const scalar& v = triWeights[1];

			if
				(
				(u + tol > 0)
					&& (v + tol > 0)
					&& (u + v < 1 + tol)
					)
			{
				// Weight[0] is for the cell centre.
				weights_[0] = 0;
				weights_[1] = triWeights[0];
				weights_[2] = triWeights[1];
				weights_[3] = triWeights[2];

				faceVertices_ = tetIs.faceTriIs(mesh);

				return;
			}
		}
	}

	// A suitable point in a triangle was not found, find the nearest.

	scalar minNearDist = vGreat;

	label nearestTetI = -1;

	forAll(faceTets, tetI)
	{
		const tetIndices& tetIs = faceTets[tetI];

		scalar nearDist = tetIs.faceTri(mesh).nearestPoint(position).distance();

		if (nearDist < minNearDist)
		{
			minNearDist = nearDist;

			nearestTetI = tetI;
		}
	}

	if (debug)
	{
		Pout << "cellPointWeight::findTriangle" << nl
			<< "    Triangle search failed; using closest tri to point "
			<< position << nl
			<< "    face: "
			<< facei << nl
			<< endl;
	}

	const tetIndices& tetIs = faceTets[nearestTetI];

	// Barycentric coordinates of the position, ignoring if the
	// determinant is suitable.  If not, the return from barycentric
	// to triWeights is safe.

	const barycentric2D triWeights =
		tetIs.faceTri(mesh).pointToBarycentric(position);

	// Weight[0] is for the cell centre.
	weights_[0] = 0;
	weights_[1] = triWeights[0];
	weights_[2] = triWeights[1];
	weights_[3] = triWeights[2];

	faceVertices_ = tetIs.faceTriIs(mesh);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellPointWeight::cellPointWeight
(
	const polyMesh& mesh,
	const vector& position,
	const label celli,
	const label facei
)
	:
	celli_(celli)
{
	if (facei < 0)
	{
		// Face data not supplied
		findTetrahedron(mesh, position, celli);
	}
	else
	{
		// Face data supplied
		findTriangle(mesh, position, facei);
	}
}


// ************************************************************************* //