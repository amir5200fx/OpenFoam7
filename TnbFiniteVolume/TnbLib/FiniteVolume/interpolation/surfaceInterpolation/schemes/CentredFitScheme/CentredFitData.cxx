#include <CentredFitData.hxx>

#include <surfaceFields.hxx>
#include <volFields.hxx>
#include <SVD.hxx>
#include <syncTools.hxx>
#include <extendedCentredCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Polynomial>
tnbLib::CentredFitData<Polynomial>::CentredFitData
(
	const fvMesh& mesh,
	const extendedCentredCellToFaceStencil& stencil,
	const scalar linearLimitFactor,
	const scalar centralWeight
)
	:
	FitData
	<
	CentredFitData<Polynomial>,
	extendedCentredCellToFaceStencil,
	Polynomial
	>
	(
		mesh, stencil, true, linearLimitFactor, centralWeight
		),
	coeffs_(mesh.nFaces())
{
	if (debug)
	{
		InfoInFunction << "Constructing CentredFitData<Polynomial>" << endl;
	}

	calcFit();

	if (debug)
	{
		Info << "Finished constructing polynomialFit data" << endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Polynomial>
void tnbLib::CentredFitData<Polynomial>::calcFit()
{
	const fvMesh& mesh = this->mesh();

	// Get the cell/face centres in stencil order.
	// Centred face stencils no good for triangles or tets.
	// Need bigger stencils
	List<List<point>> stencilPoints(mesh.nFaces());
	this->stencil().collectData(mesh.C(), stencilPoints);

	// find the fit coefficients for every face in the mesh

	const surfaceScalarField& w = mesh.surfaceInterpolation::weights();

	for (label facei = 0; facei < mesh.nInternalFaces(); facei++)
	{
		FitData
			<
			CentredFitData<Polynomial>,
			extendedCentredCellToFaceStencil,
			Polynomial
			>::calcFit(coeffs_[facei], stencilPoints[facei], w[facei], facei);
	}

	const surfaceScalarField::Boundary& bw = w.boundaryField();

	forAll(bw, patchi)
	{
		const fvsPatchScalarField& pw = bw[patchi];

		if (pw.coupled())
		{
			label facei = pw.patch().start();

			forAll(pw, i)
			{
				FitData
					<
					CentredFitData<Polynomial>,
					extendedCentredCellToFaceStencil,
					Polynomial
					>::calcFit(coeffs_[facei], stencilPoints[facei], pw[i], facei);
				facei++;
			}
		}
	}
}


// ************************************************************************* //