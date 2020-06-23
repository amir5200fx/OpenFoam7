#include <cellModel.hxx>

#include <pyramid.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::vector tnbLib::cellModel::centre
(
	const labelList& pointLabels,
	const pointField& points
) const
{
	// Estimate centre of cell
	vector cEst = Zero;

	// Sum the points indicated by the label list
	forAll(pointLabels, i)
	{
		cEst += points[pointLabels[i]];
	}

	// Average by dividing by the number summed over.
	cEst /= scalar(pointLabels.size());


	// Calculate the centre by breaking the cell into pyramids and
	// volume-weighted averaging their centres
	scalar sumV = 0.0;
	vector sumVc = Zero;

	const faceList cellFaces = faces(pointLabels);

	forAll(cellFaces, i)
	{
		const face& curFace = cellFaces[i];

		scalar pyrVol =
			pyramid<point, const point&, const face&>
			(
				curFace,
				cEst
				).mag(points);

		if (pyrVol > small)
		{
			WarningInFunction
				<< "zero or negative pyramid volume: " << -pyrVol
				<< " for face " << i
				<< endl;
		}

		sumVc -=
			pyrVol
			* pyramid<point, const point&, const face&>(curFace, cEst)
			.centre(points);

		sumV -= pyrVol;
	}

	return sumVc / (sumV + vSmall);
}


tnbLib::scalar tnbLib::cellModel::mag
(
	const labelList& pointLabels,
	const pointField& points
) const
{
	// Estimate centre of cell
	vector cEst = Zero;

	// Sum the points indicated by the label list
	forAll(pointLabels, i)
	{
		cEst += points[pointLabels[i]];
	}

	// Average by dividing by the number summed over.
	cEst /= scalar(pointLabels.size());


	// Calculate the magnitude by summing the -mags of the pyramids
	// The sign change is because the faces point outwards
	// and a pyramid is constructed from an inward pointing face
	// and the base centre-apex vector
	scalar v = 0;

	const faceList cellFaces = faces(pointLabels);

	forAll(cellFaces, i)
	{
		const face& curFace = cellFaces[i];

		scalar pyrVol =
			pyramid<point, const point&, const face&>
			(
				curFace,
				cEst
				).mag(points);

		if (pyrVol > small)
		{
			WarningInFunction
				<< "zero or negative pyramid volume: " << -pyrVol
				<< " for face " << i
				<< endl;
		}

		v -= pyrVol;
	}

	return v;
}

// ************************************************************************* //