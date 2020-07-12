#include <cellQuality.hxx>

#include <unitConversion.hxx>
#include <SubField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellQuality::cellQuality(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::cellQuality::nonOrthogonality() const
{
	tmp<scalarField> tresult
	(
		new scalarField
		(
			mesh_.nCells(), 0.0
		)
	);

	scalarField& result = tresult.ref();

	scalarField sumArea(mesh_.nCells(), 0.0);

	const vectorField& centres = mesh_.cellCentres();
	const vectorField& areas = mesh_.faceAreas();

	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	forAll(nei, facei)
	{
		vector d = centres[nei[facei]] - centres[own[facei]];
		vector s = areas[facei];
		scalar magS = mag(s);

		scalar cosDDotS =
			radToDeg(tnbLib::acos(min(1.0, (d & s) / (mag(d)*magS + vSmall))));

		result[own[facei]] = max(cosDDotS, result[own[facei]]);

		result[nei[facei]] = max(cosDDotS, result[nei[facei]]);
	}

	forAll(mesh_.boundaryMesh(), patchi)
	{
		const labelUList& faceCells =
			mesh_.boundaryMesh()[patchi].faceCells();

		const vectorField::subField faceCentres =
			mesh_.boundaryMesh()[patchi].faceCentres();

		const vectorField::subField faceAreas =
			mesh_.boundaryMesh()[patchi].faceAreas();

		forAll(faceCentres, facei)
		{
			vector d = faceCentres[facei] - centres[faceCells[facei]];
			vector s = faceAreas[facei];
			scalar magS = mag(s);

			scalar cosDDotS =
				radToDeg(tnbLib::acos(min(1.0, (d & s) / (mag(d)*magS + vSmall))));

			result[faceCells[facei]] = max(cosDDotS, result[faceCells[facei]]);
		}
	}

	return tresult;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::cellQuality::skewness() const
{
	tmp<scalarField> tresult
	(
		new scalarField
		(
			mesh_.nCells(), 0.0
		)
	);
	scalarField& result = tresult.ref();

	scalarField sumArea(mesh_.nCells(), 0.0);

	const vectorField& cellCtrs = mesh_.cellCentres();
	const vectorField& faceCtrs = mesh_.faceCentres();
	const vectorField& areas = mesh_.faceAreas();

	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	forAll(nei, facei)
	{
		scalar dOwn = mag
		(
			(faceCtrs[facei] - cellCtrs[own[facei]]) & areas[facei]
		) / mag(areas[facei]);

		scalar dNei = mag
		(
			(cellCtrs[nei[facei]] - faceCtrs[facei]) & areas[facei]
		) / mag(areas[facei]);

		point faceIntersection =
			cellCtrs[own[facei]]
			+ (dOwn / (dOwn + dNei))*(cellCtrs[nei[facei]] - cellCtrs[own[facei]]);

		scalar skewness =
			mag(faceCtrs[facei] - faceIntersection)
			/ (mag(cellCtrs[nei[facei]] - cellCtrs[own[facei]]) + vSmall);

		result[own[facei]] = max(skewness, result[own[facei]]);

		result[nei[facei]] = max(skewness, result[nei[facei]]);
	}

	forAll(mesh_.boundaryMesh(), patchi)
	{
		const labelUList& faceCells =
			mesh_.boundaryMesh()[patchi].faceCells();

		const vectorField::subField faceCentres =
			mesh_.boundaryMesh()[patchi].faceCentres();

		const vectorField::subField faceAreas =
			mesh_.boundaryMesh()[patchi].faceAreas();

		forAll(faceCentres, facei)
		{
			vector n = faceAreas[facei] / mag(faceAreas[facei]);

			point faceIntersection =
				cellCtrs[faceCells[facei]]
				+ ((faceCentres[facei] - cellCtrs[faceCells[facei]])&n)*n;

			scalar skewness =
				mag(faceCentres[facei] - faceIntersection)
				/ (
					mag(faceCentres[facei] - cellCtrs[faceCells[facei]])
					+ vSmall
					);

			result[faceCells[facei]] = max(skewness, result[faceCells[facei]]);
		}
	}

	return tresult;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::cellQuality::faceNonOrthogonality() const
{
	tmp<scalarField> tresult
	(
		new scalarField
		(
			mesh_.nFaces(), 0.0
		)
	);
	scalarField& result = tresult.ref();


	const vectorField& centres = mesh_.cellCentres();
	const vectorField& areas = mesh_.faceAreas();

	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	forAll(nei, facei)
	{
		vector d = centres[nei[facei]] - centres[own[facei]];
		vector s = areas[facei];
		scalar magS = mag(s);

		scalar cosDDotS =
			radToDeg(tnbLib::acos(min(1.0, (d & s) / (mag(d)*magS + vSmall))));

		result[facei] = cosDDotS;
	}

	label globalFacei = mesh_.nInternalFaces();

	forAll(mesh_.boundaryMesh(), patchi)
	{
		const labelUList& faceCells =
			mesh_.boundaryMesh()[patchi].faceCells();

		const vectorField::subField faceCentres =
			mesh_.boundaryMesh()[patchi].faceCentres();

		const vectorField::subField faceAreas =
			mesh_.boundaryMesh()[patchi].faceAreas();

		forAll(faceCentres, facei)
		{
			vector d = faceCentres[facei] - centres[faceCells[facei]];
			vector s = faceAreas[facei];
			scalar magS = mag(s);

			scalar cosDDotS =
				radToDeg(tnbLib::acos(min(1.0, (d & s) / (mag(d)*magS + vSmall))));

			result[globalFacei++] = cosDDotS;
		}
	}

	return tresult;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::cellQuality::faceSkewness() const
{
	tmp<scalarField> tresult
	(
		new scalarField
		(
			mesh_.nFaces(), 0.0
		)
	);
	scalarField& result = tresult.ref();


	const vectorField& cellCtrs = mesh_.cellCentres();
	const vectorField& faceCtrs = mesh_.faceCentres();
	const vectorField& areas = mesh_.faceAreas();

	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	forAll(nei, facei)
	{
		scalar dOwn = mag
		(
			(faceCtrs[facei] - cellCtrs[own[facei]]) & areas[facei]
		) / mag(areas[facei]);

		scalar dNei = mag
		(
			(cellCtrs[nei[facei]] - faceCtrs[facei]) & areas[facei]
		) / mag(areas[facei]);

		point faceIntersection =
			cellCtrs[own[facei]]
			+ (dOwn / (dOwn + dNei))*(cellCtrs[nei[facei]] - cellCtrs[own[facei]]);

		result[facei] =
			mag(faceCtrs[facei] - faceIntersection)
			/ (mag(cellCtrs[nei[facei]] - cellCtrs[own[facei]]) + vSmall);
	}


	label globalFacei = mesh_.nInternalFaces();

	forAll(mesh_.boundaryMesh(), patchi)
	{
		const labelUList& faceCells =
			mesh_.boundaryMesh()[patchi].faceCells();

		const vectorField::subField faceCentres =
			mesh_.boundaryMesh()[patchi].faceCentres();

		const vectorField::subField faceAreas =
			mesh_.boundaryMesh()[patchi].faceAreas();

		forAll(faceCentres, facei)
		{
			vector n = faceAreas[facei] / mag(faceAreas[facei]);

			point faceIntersection =
				cellCtrs[faceCells[facei]]
				+ ((faceCentres[facei] - cellCtrs[faceCells[facei]])&n)*n;

			result[globalFacei++] =
				mag(faceCentres[facei] - faceIntersection)
				/ (
					mag(faceCentres[facei] - cellCtrs[faceCells[facei]])
					+ vSmall
					);
		}
	}

	return tresult;
}


// ************************************************************************* //