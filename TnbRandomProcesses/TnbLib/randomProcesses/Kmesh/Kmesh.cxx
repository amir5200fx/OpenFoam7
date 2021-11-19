#include <Kmesh.hxx>

#include <polyMesh.hxx>
#include <volFields.hxx>
#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //




// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Kmesh::Kmesh(const fvMesh& mesh)
	:
	vectorField(mesh.V().size()),
	nn_(vector::dim)
{
	boundBox box = mesh.bounds();
	l_ = box.span();

	vector cornerCellCentre = ::tnbLib::max(mesh.C().primitiveField());
	vector cellL = 2 * (box.max() - cornerCellCentre);

	vector rdeltaByL;
	label nTot = 1;

	forAll(nn_, i)
	{
		nn_[i] = label(l_[i] / cellL[i] + 0.5);
		nTot *= nn_[i];

		if (nn_[i] > 1)
		{
			l_[i] -= cellL[i];
		}

		rdeltaByL[i] = nn_[i] / (l_[i] * l_[i]);
	}

	if (nTot != mesh.nCells())
	{
		FatalErrorInFunction
			<< "calculated number of cells is incorrect"
			<< abort(FatalError);
	}

	for (label i = 0; i < nn_[0]; i++)
	{
		scalar k1 = (i - nn_[0] / 2)*constant::mathematical::twoPi / l_[0];

		for (label j = 0; j < nn_[1]; j++)
		{
			scalar k2 = (j - nn_[1] / 2)*constant::mathematical::twoPi / l_[1];

			for (label k = 0; k < nn_[2]; k++)
			{
				scalar k3 = (k - nn_[2] / 2)*constant::mathematical::twoPi / l_[2];

				(*this)[index(i, j, k, nn_)] = vector(k1, k2, k3);
			}
		}
	}

	kmax_ = mag
	(
		tnbLib::max
		(
			cmptMag((*this)[index(nn_[0] - 1, nn_[1] - 1, nn_[2] - 1, nn_)]),
			cmptMag((*this)[index(0, 0, 0, nn_)])
		)
	);
}


// ************************************************************************* //