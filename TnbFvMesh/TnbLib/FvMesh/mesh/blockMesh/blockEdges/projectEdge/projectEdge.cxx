#include <projectEdge.hxx>

#include <searchableSurfacesQueries.hxx>
#include <unitConversion.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <pointConstraint.hxx>
#include <OBJstream.hxx>
#include <linearInterpolationWeights.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(projectEdge, 0);
	addToRunTimeSelectionTable(blockEdge, projectEdge, Istream);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::projectEdge::findNearest
(
	const point& pt,
	point& near,
	pointConstraint& constraint
) const
{
	if (surfaces_.size())
	{
		const scalar distSqr = magSqr(points_[end_] - points_[start_]);

		pointField boundaryNear(1);
		List<pointConstraint> boundaryConstraint(1);

		searchableSurfacesQueries::findNearest
		(
			geometry_,
			surfaces_,
			pointField(1, pt),
			scalarField(1, distSqr),
			boundaryNear,
			boundaryConstraint
		);
		near = boundaryNear[0];
		constraint = boundaryConstraint[0];
	}
	else
	{
		near = pt;
		constraint = pointConstraint();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::projectEdge::projectEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
	:
	blockEdge(dict, index, points, is),
	geometry_(geometry)
{
	wordList names(is);
	surfaces_.setSize(names.size());
	forAll(names, i)
	{
		surfaces_[i] = geometry_.findSurfaceID(names[i]);

		if (surfaces_[i] == -1)
		{
			FatalIOErrorInFunction(is)
				<< "Cannot find surface " << names[i] << " in geometry"
				<< exit(FatalIOError);
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::projectEdge::position(const scalar lambda) const
{
	// Initial guess
	const point start(points_[start_] + lambda * (points_[end_] - points_[start_]));

	point near(start);

	if (lambda >= small && lambda < 1.0 - small)
	{
		pointConstraint constraint;
		findNearest(start, near, constraint);
	}

	return near;
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::projectEdge::position(const scalarList& lambdas) const
{
	// For debugging to tag the output
	static label eIter = 0;

	autoPtr<OBJstream> debugStr;
	if (debug)
	{
		debugStr.reset
		(
			new OBJstream("projectEdge_" + tnbLib::name(eIter++) + ".obj")
		);
		Info << "Writing lines from straight-line start points"
			<< " to projected points to " << debugStr().name() << endl;
	}


	tmp<pointField> tpoints(new pointField(lambdas.size()));
	pointField& points = tpoints.ref();

	const point& startPt = points_[start_];
	const point& endPt = points_[end_];
	const vector d = endPt - startPt;

	// Initial guess
	forAll(lambdas, i)
	{
		points[i] = startPt + lambdas[i] * d;
	}


	// Upper limit for number of iterations
	const label maxIter = 10;
	// Residual tolerance
	const scalar relTol = 0.1;
	const scalar absTol = 1e-4;

	scalar initialResidual = 0.0;

	for (label iter = 0; iter < maxIter; iter++)
	{
		// Do projection
		{
			List<pointConstraint> constraints(lambdas.size());
			pointField start(points);
			searchableSurfacesQueries::findNearest
			(
				geometry_,
				surfaces_,
				start,
				scalarField(start.size(), magSqr(d)),
				points,
				constraints
			);

			// Reset start and end point
			if (lambdas[0] < small)
			{
				points[0] = startPt;
			}
			if (lambdas.last() > 1.0 - small)
			{
				points.last() = endPt;
			}

			if (debugStr.valid())
			{
				forAll(points, i)
				{
					debugStr().write(linePointRef(start[i], points[i]));
				}
			}
		}

		// Calculate lambdas (normalised coordinate along edge)
		scalarField projLambdas(points.size());
		{
			projLambdas[0] = 0.0;
			for (label i = 1; i < points.size(); i++)
			{
				projLambdas[i] = projLambdas[i - 1] + mag(points[i] - points[i - 1]);
			}
			projLambdas /= projLambdas.last();
		}
		linearInterpolationWeights interpolator(projLambdas);

		// Compare actual distances and move points (along straight line;
		// not along surface)
		vectorField residual(points.size(), vector::zero);
		labelList indices;
		scalarField weights;
		for (label i = 1; i < points.size() - 1; i++)
		{
			interpolator.valueWeights(lambdas[i], indices, weights);

			point predicted = vector::zero;
			forAll(indices, indexi)
			{
				predicted += weights[indexi] * points[indices[indexi]];
			}
			residual[i] = predicted - points[i];
		}

		scalar scalarResidual = sum(mag(residual));

		if (debug)
		{
			Pout << "Iter:" << iter << " initialResidual:" << initialResidual
				<< " residual:" << scalarResidual << endl;
		}

		if (scalarResidual < absTol*0.5*lambdas.size())
		{
			break;
		}
		else if (iter == 0)
		{
			initialResidual = scalarResidual;
		}
		else if (scalarResidual / initialResidual < relTol)
		{
			break;
		}


		if (debugStr.valid())
		{
			forAll(points, i)
			{
				const point predicted(points[i] + residual[i]);
				debugStr().write(linePointRef(points[i], predicted));
			}
		}

		points += residual;
	}

	return tpoints;
}


// ************************************************************************* //