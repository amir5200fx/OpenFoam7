#include <matchPoints.hxx>

#include <SortableList.hxx>
#include <ListOps.hxx>

#include <IOstreams.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::matchPoints
(
	const UList<point>& pts0,
	const UList<point>& pts1,
	const UList<scalar>& matchDistances,
	const bool verbose,
	labelList& from0To1,
	const point& origin
)
{
	from0To1.setSize(pts0.size());
	from0To1 = -1;

	bool fullMatch = true;

	point compareOrigin = origin;

	if (origin == point(vGreat, vGreat, vGreat))
	{
		if (pts1.size())
		{
			compareOrigin = sum(pts1) / pts1.size();
		}
	}

	SortableList<scalar> pts0MagSqr(magSqr(pts0 - compareOrigin));

	SortableList<scalar> pts1MagSqr(magSqr(pts1 - compareOrigin));

	forAll(pts0MagSqr, i)
	{
		scalar dist0 = pts0MagSqr[i];

		label face0I = pts0MagSqr.indices()[i];

		scalar matchDist = matchDistances[face0I];

		label startI = findLower(pts1MagSqr, 0.99999*dist0 - 2 * matchDist);

		if (startI == -1)
		{
			startI = 0;
		}


		// Go through range of equal mag and find nearest vector.
		scalar minDistSqr = vGreat;
		label minFacei = -1;

		for
			(
				label j = startI;
				(
				(j < pts1MagSqr.size())
					&& (pts1MagSqr[j] < 1.00001*dist0 + 2 * matchDist)
					);
				j++
				)
		{
			label facei = pts1MagSqr.indices()[j];
			// Compare actual vectors
			scalar distSqr = magSqr(pts0[face0I] - pts1[facei]);

			if (distSqr <= sqr(matchDist) && distSqr < minDistSqr)
			{
				minDistSqr = distSqr;
				minFacei = facei;
			}
		}

		if (minFacei == -1)
		{
			fullMatch = false;

			if (verbose)
			{
				Pout << "Cannot find point in pts1 matching point " << face0I
					<< " coord:" << pts0[face0I]
					<< " in pts0 when using tolerance " << matchDist << endl;

				// Go through range of equal mag and find equal vector.
				Pout << "Searching started from:" << startI << " in pts1"
					<< endl;
				for
					(
						label j = startI;
						(
						(j < pts1MagSqr.size())
							&& (pts1MagSqr[j] < 1.00001*dist0 + 2 * matchDist)
							);
						j++
						)
				{
					label facei = pts1MagSqr.indices()[j];

					Pout << "    Compared coord: " << pts1[facei]
						<< " at index " << j
						<< " with difference to point "
						<< mag(pts1[facei] - pts0[face0I]) << endl;
				}
			}
		}

		from0To1[face0I] = minFacei;
	}

	return fullMatch;
}


bool tnbLib::matchPoints
(
	const UList<point>& pts0,
	const UList<point>& pts1,
	const UList<point>& pts0Dir,
	const UList<point>& pts1Dir,
	const UList<scalar>& matchDistances,
	const bool verbose,
	labelList& from0To1,
	const point& origin
)
{
	from0To1.setSize(pts0.size());
	from0To1 = -1;

	bool fullMatch = true;

	point compareOrigin = origin;

	if (origin == point(vGreat, vGreat, vGreat))
	{
		if (pts1.size())
		{
			compareOrigin = sum(pts1) / pts1.size();
		}
	}

	SortableList<scalar> pts0MagSqr(magSqr(pts0 - compareOrigin));

	SortableList<scalar> pts1MagSqr(magSqr(pts1 - compareOrigin));

	forAll(pts0MagSqr, i)
	{
		scalar dist0 = pts0MagSqr[i];

		label face0I = pts0MagSqr.indices()[i];

		scalar matchDist = matchDistances[face0I];

		label startI = findLower(pts1MagSqr, 0.99999*dist0 - 2 * matchDist);

		if (startI == -1)
		{
			startI = 0;
		}

		// Go through range of equal mag and find nearest vector.
		scalar minDistSqr = vGreat;
		scalar minDistNorm = 0;
		label minFacei = -1;

		for
			(
				label j = startI;
				(
				(j < pts1MagSqr.size())
					&& (pts1MagSqr[j] < 1.00001*dist0 + 2 * matchDist)
					);
				j++
				)
		{
			label facei = pts1MagSqr.indices()[j];
			// Compare actual vectors
			scalar distSqr = magSqr(pts0[face0I] - pts1[facei]);

			scalar distNorm = (pts0Dir[face0I] & pts1Dir[facei]);

			if
				(
					magSqr(pts0Dir[face0I]) < sqr(small)
					&& magSqr(pts1Dir[facei]) < sqr(small)
					)
			{
				distNorm = -1;
			}

			if (distSqr <= sqr(matchDist) && distSqr < minDistSqr)
			{
				// Check that the normals point in equal and opposite directions
				if (distNorm < minDistNorm)
				{
					minDistNorm = distNorm;
					minDistSqr = distSqr;
					minFacei = facei;
				}
			}
		}

		if (minFacei == -1)
		{
			fullMatch = false;

			if (verbose)
			{
				Pout << "Cannot find point in pts1 matching point " << face0I
					<< " coord:" << pts0[face0I]
					<< " in pts0 when using tolerance " << matchDist << endl;

				// Go through range of equal mag and find equal vector.
				Pout << "Searching started from:" << startI << " in pts1"
					<< endl;
				for
					(
						label j = startI;
						(
						(j < pts1MagSqr.size())
							&& (pts1MagSqr[j] < 1.00001*dist0 + 2 * matchDist)
							);
						j++
						)
				{
					label facei = pts1MagSqr.indices()[j];

					Pout << "    Compared coord: " << pts1[facei]
						<< " at index " << j
						<< " with difference to point "
						<< mag(pts1[facei] - pts0[face0I]) << endl;
				}
			}
		}

		from0To1[face0I] = minFacei;
	}

	return fullMatch;
}


// ************************************************************************* //