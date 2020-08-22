#include <polyLine.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::polyLine::calcParam()
{
	param_.setSize(points_.size());

	if (param_.size())
	{
		param_[0] = 0.0;

		for (label i = 1; i < param_.size(); i++)
		{
			param_[i] = param_[i - 1] + mag(points_[i] - points_[i - 1]);
		}

		// Normalize on the interval 0-1
		lineLength_ = param_.last();
		for (label i = 1; i < param_.size() - 1; i++)
		{
			param_[i] /= lineLength_;
		}
		param_.last() = 1.0;
	}
	else
	{
		lineLength_ = 0.0;
	}
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyLine::polyLine(const pointField& ps, const bool)
	:
	points_(ps),
	lineLength_(0.0),
	param_(0)
{
	calcParam();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::pointField& tnbLib::polyLine::points() const
{
	return points_;
}


tnbLib::label tnbLib::polyLine::nSegments() const
{
	return points_.size() - 1;
}


tnbLib::label tnbLib::polyLine::localParameter(scalar& lambda) const
{
	// Check endpoints
	if (lambda < small)
	{
		lambda = 0;
		return 0;
	}
	else if (lambda > 1 - small)
	{
		lambda = 1;
		return nSegments();
	}

	// Search table of cumulative distances to find which line-segment
	// we are on.
	// Check the upper bound.

	label segmentI = 1;
	while (param_[segmentI] < lambda)
	{
		segmentI++;
	}
	segmentI--;   // We want the corresponding lower bound

	// The local parameter [0-1] on this line segment
	lambda =
		(lambda - param_[segmentI]) / (param_[segmentI + 1] - param_[segmentI]);

	return segmentI;
}


tnbLib::point tnbLib::polyLine::position(const scalar mu) const
{
	// Check end-points
	if (mu < small)
	{
		return points_.first();
	}
	else if (mu > 1 - small)
	{
		return points_.last();
	}

	scalar lambda = mu;
	label segment = localParameter(lambda);
	return position(segment, lambda);
}


tnbLib::point tnbLib::polyLine::position
(
	const label segment,
	const scalar mu
) const
{
	// Out-of-bounds
	if (segment < 0)
	{
		return points_.first();
	}
	else if (segment > nSegments())
	{
		return points_.last();
	}

	const point& p0 = points()[segment];
	const point& p1 = points()[segment + 1];

	// Special cases - no calculation needed
	if (mu <= 0.0)
	{
		return p0;
	}
	else if (mu >= 1.0)
	{
		return p1;
	}
	else
	{
		// Linear interpolation
		return points_[segment] + mu * (p1 - p0);
	}
}


tnbLib::scalar tnbLib::polyLine::length() const
{
	return lineLength_;
}


// ************************************************************************* //