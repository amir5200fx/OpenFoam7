#include <coordSet.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::coordSet::coordFormat,
		5
		>::names[] =
	{
		"xyz",
		"x",
		"y",
		"z",
		"distance"
	};
}


const tnbLib::NamedEnum<tnbLib::coordSet::coordFormat, 5>
tnbLib::coordSet::coordFormatNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coordSet::coordSet
(
	const word& name,
	const word& axis
)
	:
	pointField(0),
	name_(name),
	axis_(coordFormatNames_[axis]),
	curveDist_(0)
{}


tnbLib::coordSet::coordSet
(
	const word& name,
	const word& axis,
	const List<point>& points,
	const scalarList& curveDist
)
	:
	pointField(points),
	name_(name),
	axis_(coordFormatNames_[axis]),
	curveDist_(curveDist)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::coordSet::hasVectorAxis() const
{
	return axis_ == XYZ;
}


tnbLib::scalar tnbLib::coordSet::scalarCoord
(
	const label index
)   const
{
	const point& p = operator[](index);

	if (axis_ == X)
	{
		return p.x();
	}
	else if (axis_ == Y)
	{
		return p.y();
	}
	else if (axis_ == Z)
	{
		return p.z();
	}
	else if (axis_ == DISTANCE)
	{
		// Use distance to reference point
		return curveDist_[index];
	}
	else
	{
		FatalErrorInFunction
			<< "Illegal axis specification " << axis_
			<< " for sampling line " << name_
			<< exit(FatalError);

		return 0;
	}
}


tnbLib::point tnbLib::coordSet::vectorCoord(const label index) const
{
	const point& p = operator[](index);

	return p;
}


tnbLib::Ostream& tnbLib::coordSet::write(Ostream& os) const
{
	os << "name:" << name_ << " axis:" << axis_
		<< endl
		<< endl << "\t(coord)"
		<< endl;

	forAll(*this, sampleI)
	{
		os << '\t' << operator[](sampleI) << endl;
	}

	return os;
}


// ************************************************************************* //