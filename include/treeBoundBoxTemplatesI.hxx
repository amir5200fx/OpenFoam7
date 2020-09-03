#pragma once
#include <FixedList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


template<unsigned Size>
tnbLib::treeBoundBox::treeBoundBox
(
	const UList<point>& points,
	const FixedList<label, Size>& indices
)
	:
	boundBox(points, indices, false)
{
	// points may be empty, but a FixedList is never empty
	if (points.empty())
	{
		WarningInFunction
			<< "cannot find bounding box for zero-sized pointField, "
			<< "returning zero" << endl;

		return;
	}
}

// ************************************************************************* //