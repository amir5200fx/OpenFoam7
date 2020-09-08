#pragma once
#include <surfaceFields.hxx>
#include <volFields.hxx>
#include <SVD.hxx>
#include <extendedUpwindCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

template<class Polynomial>
tnbLib::UpwindFitData<Polynomial>::UpwindFitData
(
	const fvMesh& mesh,
	const extendedUpwindCellToFaceStencil& stencil,
	const bool linearCorrection,
	const scalar linearLimitFactor,
	const scalar centralWeight
)
	:
	FitData
	<
	UpwindFitData<Polynomial>,
	extendedUpwindCellToFaceStencil,
	Polynomial
	>
	(
		mesh, stencil, linearCorrection, linearLimitFactor, centralWeight
		),
	owncoeffs_(mesh.nFaces()),
	neicoeffs_(mesh.nFaces())
{
	if (debug)
	{
		InfoInFunction << "Constructing UpwindFitData<Polynomial>" << endl;
	}

	calcFit();

	if (debug)
	{
		Info << "    Finished constructing polynomialFit data" << endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Polynomial>
void tnbLib::UpwindFitData<Polynomial>::calcFit()
{
	const fvMesh& mesh = this->mesh();

	const surfaceScalarField& w = mesh.surfaceInterpolation::weights();
	const surfaceScalarField::Boundary& bw = w.boundaryField();

	// Owner stencil weights
	// ~~~~~~~~~~~~~~~~~~~~~

	// Get the cell/face centres in stencil order.
	List<List<point>> stencilPoints(mesh.nFaces());
	this->stencil().collectData
	(
		this->stencil().ownMap(),
		this->stencil().ownStencil(),
		mesh.C(),
		stencilPoints
	);

	// find the fit coefficients for every owner

	// Pout<< "-- Owner --" << endl;
	for (label facei = 0; facei < mesh.nInternalFaces(); facei++)
	{
		FitData
			<
			UpwindFitData<Polynomial>,
			extendedUpwindCellToFaceStencil,
			Polynomial
			>::calcFit(owncoeffs_[facei], stencilPoints[facei], w[facei], facei);

		// Pout<< "    facei:" << facei
		//    << " at:" << mesh.faceCentres()[facei] << endl;
		// forAll(owncoeffs_[facei], i)
		//{
		//    Pout<< "    point:" << stencilPoints[facei][i]
		//        << "\tweight:" << owncoeffs_[facei][i]
		//        << endl;
		//}
	}

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
					UpwindFitData<Polynomial>,
					extendedUpwindCellToFaceStencil,
					Polynomial
					>::calcFit
					(
						owncoeffs_[facei], stencilPoints[facei], pw[i], facei
					);
				facei++;
			}
		}
	}


	// Neighbour stencil weights
	// ~~~~~~~~~~~~~~~~~~~~~~~~~

	// Note:reuse stencilPoints since is major storage
	this->stencil().collectData
	(
		this->stencil().neiMap(),
		this->stencil().neiStencil(),
		mesh.C(),
		stencilPoints
	);

	// find the fit coefficients for every neighbour

	// Pout<< "-- Neighbour --" << endl;
	for (label facei = 0; facei < mesh.nInternalFaces(); facei++)
	{
		FitData
			<
			UpwindFitData<Polynomial>,
			extendedUpwindCellToFaceStencil,
			Polynomial
			>::calcFit(neicoeffs_[facei], stencilPoints[facei], w[facei], facei);

		// Pout<< "    facei:" << facei
		//    << " at:" << mesh.faceCentres()[facei] << endl;
		// forAll(neicoeffs_[facei], i)
		//{
		//    Pout<< "    point:" << stencilPoints[facei][i]
		//        << "\tweight:" << neicoeffs_[facei][i]
		//        << endl;
		//}
	}

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
					UpwindFitData<Polynomial>,
					extendedUpwindCellToFaceStencil,
					Polynomial
					>::calcFit
					(
						neicoeffs_[facei], stencilPoints[facei], pw[i], facei
					);
				facei++;
			}
		}
	}
}


// ************************************************************************* //