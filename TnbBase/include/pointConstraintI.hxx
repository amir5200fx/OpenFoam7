#pragma once
#include <FixedList.hxx>
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::pointConstraint::pointConstraint()
	:
	Tuple2<label, vector>(0, Zero)
{}


inline tnbLib::pointConstraint::pointConstraint(const Tuple2<label, vector>& pc)
	:
	Tuple2<label, vector>(pc)
{}


inline tnbLib::pointConstraint::pointConstraint(Istream& is)
	:
	Tuple2<label, vector>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline void tnbLib::pointConstraint::applyConstraint(const vector& cd)
{
	if (first() == 0)
	{
		first() = 1;
		second() = cd;
	}
	else if (first() == 1)
	{
		vector planeNormal = cd ^ second();
		scalar magPlaneNormal = mag(planeNormal);

		if (magPlaneNormal > 1e-3)
		{
			first() = 2;
			second() = planeNormal / magPlaneNormal;
		}
	}
	else if (first() == 2)
	{
		if (mag(cd & second()) > 1e-3)
		{
			first() = 3;
			second() = Zero;
		}
	}
}


inline void tnbLib::pointConstraint::combine(const pointConstraint& pc)
{
	if (first() == 0)
	{
		operator=(pc);
	}
	else if (first() == 1)
	{
		// Save single normal
		vector n = second();
		// Apply to supplied point constaint
		operator=(pc);
		applyConstraint(n);
	}
	else if (first() == 2)
	{
		if (pc.first() == 0)
		{
		}
		else if (pc.first() == 1)
		{
			applyConstraint(pc.second());
		}
		else if (pc.first() == 2)
		{
			// Both constrained to line. Same (+-)direction?
			if (mag(second() & pc.second()) <= (1.0 - 1e-3))
			{
				// Different directions
				first() = 3;
				second() = Zero;
			}
		}
		else
		{
			first() = 3;
			second() = Zero;
		}
	}
}


inline tnbLib::tensor tnbLib::pointConstraint::constraintTransformation() const
{
	if (first() == 0)
	{
		return I;
	}
	else if (first() == 1)
	{
		return I - sqr(second());
	}
	else if (first() == 2)
	{
		return sqr(second());
	}
	else
	{
		return Zero;
	}
}


inline void tnbLib::pointConstraint::unconstrainedDirections
(
	label& n,
	tensor& tt
) const
{
	n = 3 - first();

	FixedList<vector, 3> vecs;

	if (first() == 0)
	{
		vecs[0] = vector(1, 0, 0);
		vecs[1] = vector(0, 1, 0);
		vecs[2] = vector(0, 0, 1);
	}
	else if (first() == 1)
	{
		const vector& planeDir = second();

		vecs[0] = vector(1, 0, 0) - planeDir.x()*planeDir;

		if (mag(vecs[0].x()) < 1e-3)
		{
			vecs[0] = vector(0, 1, 0) - planeDir.y()*planeDir;
		}

		vecs[0] /= mag(vecs[0]);
		vecs[1] = vecs[0] ^ planeDir;
		vecs[1] /= mag(vecs[1]);
	}
	else if (first() == 2)
	{
		vecs[0] = second();
	}

	// Knock out remaining vectors
	for (direction dir = n; dir < vecs.size(); dir++)
	{
		vecs[dir] = Zero;
	}

	tt = tensor(vecs[0], vecs[1], vecs[2]);
}


inline tnbLib::vector tnbLib::pointConstraint::constrainDisplacement
(
	const vector& d
) const
{
	vector cd;

	if (first() == 0)
	{
		cd = d;
	}
	else if (first() == 1)
	{
		// Remove plane normal
		cd = d - (d&second())*second();
	}
	else if (first() == 2)
	{
		// Keep line direction only
		cd = (d&second())*second();
	}
	else
	{
		cd = Zero;
	}
	return cd;
}


inline void tnbLib::combineConstraintsEqOp::operator()
(
	pointConstraint& x,
	const pointConstraint& y
	) const
{
	x.combine(y);
}


inline tnbLib::pointConstraint tnbLib::transform
(
	const tensor& tt,
	const pointConstraint& v
)
{
	return pointConstraint
	(
		Tuple2<label, vector>(v.first(), transform(tt, v.second()))
	);
}


// ************************************************************************* //