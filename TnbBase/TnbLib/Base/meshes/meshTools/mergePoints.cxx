#include <mergePoints.hxx>

#include <ListOps.hxx>
#include <point.hxx>
#include <Field.hxx>
 
#include <IOstreams.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::label tnbLib::mergePoints
(
	const UList<Type>& points,
	const scalar mergeTol,
	const bool verbose,
	labelList& pointMap,
	const Type& origin
)
{
	Type compareOrigin = origin;

	if (origin == Type::max)
	{
		if (points.size())
		{
			compareOrigin = sum(points) / points.size();
		}
	}

	// Create a old to new point mapping array
	pointMap.setSize(points.size());
	pointMap = -1;

	if (points.empty())
	{
		return points.size();
	}

	// We're comparing distance squared to origin first.
	// Say if starting from two close points:
	//     x, y, z
	//     x+mergeTol, y+mergeTol, z+mergeTol
	// Then the magSqr of both will be
	//     x^2+y^2+z^2
	//     x^2+y^2+z^2 + 2*mergeTol*(x+z+y) + mergeTol^2*...
	// so the difference will be 2*mergeTol*(x+y+z)

	const scalar mergeTolSqr = tnbLib::sqr(scalar(mergeTol));

	// Sort points by magSqr
	const Field<Type> d(points - compareOrigin);

	List<scalar> magSqrD(d.size());
	forAll(d, pointi)
	{
		magSqrD[pointi] = magSqr(d[pointi]);
	}
	labelList order;
	sortedOrder(magSqrD, order);


	Field<scalar> sortedTol(points.size());
	forAll(order, sortI)
	{
		label pointi = order[sortI];

		// Convert to scalar precision
		const point pt
		(
			scalar(d[pointi].x()),
			scalar(d[pointi].y()),
			scalar(d[pointi].z())
		);
		sortedTol[sortI] = 2 * mergeTol*(mag(pt.x()) + mag(pt.y()) + mag(pt.z()));
	}

	label newPointi = 0;


	// Handle 0th point separately (is always unique)
	label pointi = order[0];
	pointMap[pointi] = newPointi++;


	for (label sortI = 1; sortI < order.size(); sortI++)
	{
		// Get original point index
		label pointi = order[sortI];
		const scalar mag2 = magSqrD[order[sortI]];
		// Convert to scalar precision
		const point pt
		(
			scalar(points[pointi].x()),
			scalar(points[pointi].y()),
			scalar(points[pointi].z())
		);


		// Compare to previous points to find equal one.
		label equalPointi = -1;

		for
			(
				label prevSortI = sortI - 1;
				prevSortI >= 0
				&& (mag(magSqrD[order[prevSortI]] - mag2) <= sortedTol[sortI]);
				prevSortI--
				)
		{
			label prevPointi = order[prevSortI];
			const point prevPt
			(
				scalar(points[prevPointi].x()),
				scalar(points[prevPointi].y()),
				scalar(points[prevPointi].z())
			);

			if (magSqr(pt - prevPt) <= mergeTolSqr)
			{
				// Found match.
				equalPointi = prevPointi;

				break;
			}
		}


		if (equalPointi != -1)
		{
			// Same coordinate as equalPointi. Map to same new point.
			pointMap[pointi] = pointMap[equalPointi];

			if (verbose)
			{
				Pout << "tnbLib::mergePoints : Merging points "
					<< pointi << " and " << equalPointi
					<< " with coordinates:" << points[pointi]
					<< " and " << points[equalPointi]
					<< endl;
			}
		}
		else
		{
			// Differs. Store new point.
			pointMap[pointi] = newPointi++;
		}
	}

	return newPointi;
}


template<class Type>
bool tnbLib::mergePoints
(
	const UList<Type>& points,
	const scalar mergeTol,
	const bool verbose,
	labelList& pointMap,
	List<Type>& newPoints,
	const Type& origin
)
{
	label nUnique = mergePoints
	(
		points,
		mergeTol,
		verbose,
		pointMap,
		origin
	);

	newPoints.setSize(nUnique);
	forAll(pointMap, pointi)
	{
		newPoints[pointMap[pointi]] = points[pointi];
	}

	return (nUnique != points.size());
}


// ************************************************************************* //