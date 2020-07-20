#include <LeastSquaresVectorsTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Stencil>
tnbLib::fv::LeastSquaresVectors<Stencil>::LeastSquaresVectors
(
	const fvMesh& mesh
)
	:
	MeshObject<fvMesh, tnbLib::MoveableMeshObject, LeastSquaresVectors>(mesh),
	vectors_(mesh.nCells())
{
	calcLeastSquaresVectors();
}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

template<class Stencil>
tnbLib::fv::LeastSquaresVectors<Stencil>::~LeastSquaresVectors()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Stencil>
void tnbLib::fv::LeastSquaresVectors<Stencil>::calcLeastSquaresVectors()
{
	if (debug)
	{
		InfoInFunction << "Calculating least square gradient vectors" << endl;
	}

	const fvMesh& mesh = this->mesh_;
	const extendedCentredCellToCellStencil& stencil = this->stencil();

	stencil.collectData(mesh.C(), vectors_);

	// Create the base form of the dd-tensor
	// including components for the "empty" directions
	symmTensor dd0(sqr((Vector<label>::one - mesh.geometricD()) / 2));

	forAll(vectors_, i)
	{
		List<vector>& lsvi = vectors_[i];
		symmTensor dd(dd0);

		// The current cell is 0 in the stencil
		// Calculate the deltas and sum the weighted dd
		for (label j = 1; j < lsvi.size(); j++)
		{
			lsvi[j] = lsvi[j] - lsvi[0];
			scalar magSqrLsvi = magSqr(lsvi[j]);
			dd += sqr(lsvi[j]) / magSqrLsvi;
			lsvi[j] /= magSqrLsvi;
		}

		// Invert dd
		dd = inv(dd);

		// Remove the components corresponding to the empty directions
		dd -= dd0;

		// Finalize the gradient weighting vectors
		lsvi[0] = Zero;
		for (label j = 1; j < lsvi.size(); j++)
		{
			lsvi[j] = dd & lsvi[j];
			lsvi[0] -= lsvi[j];
		}
	}

	if (debug)
	{
		InfoInFunction
			<< "Finished calculating least square gradient vectors" << endl;
	}
}


template<class Stencil>
bool tnbLib::fv::LeastSquaresVectors<Stencil>::movePoints()
{
	calcLeastSquaresVectors();
	return true;
}


// ************************************************************************* //