#include <blockEdge.hxx>

#include <blockVertex.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(blockEdge, 0);
	defineRunTimeSelectionTable(blockEdge, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdge::blockEdge
(
	const pointField& points,
	const label start,
	const label end
)
	:
	points_(points),
	start_(start),
	end_(end)
{}


tnbLib::blockEdge::blockEdge
(
	const dictionary& dict,
	const label index,
	const pointField& points,
	Istream& is
)
	:
	points_(points),
	start_(blockVertex::read(is, dict)),
	end_(blockVertex::read(is, dict))
{}


tnbLib::autoPtr<tnbLib::blockEdge> tnbLib::blockEdge::clone() const
{
	NotImplemented;
	return autoPtr<blockEdge>(nullptr);
}


tnbLib::autoPtr<tnbLib::blockEdge> tnbLib::blockEdge::New
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
{
	if (debug)
	{
		InfoInFunction << "Constructing blockEdge" << endl;
	}

	const word edgeType(is);

	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(edgeType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown blockEdge type "
			<< edgeType << nl << nl
			<< "Valid blockEdge types are" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<blockEdge>(cstrIter()(dict, index, geometry, points, is));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointField tnbLib::blockEdge::appendEndPoints
(
	const pointField& points,
	const label start,
	const label end,
	const pointField& otherKnots
)
{
	pointField allKnots(otherKnots.size() + 2);

	// Start/end knots
	allKnots[0] = points[start];
	allKnots[otherKnots.size() + 1] = points[end];

	// Intermediate knots
	forAll(otherKnots, knotI)
	{
		allKnots[knotI + 1] = otherKnots[knotI];
	}

	return allKnots;
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::blockEdge::position(const scalarList& lambdas) const
{
	tmp<pointField> tpoints(new pointField(lambdas.size()));
	pointField& points = tpoints.ref();

	forAll(lambdas, i)
	{
		points[i] = position(lambdas[i]);
	}
	return tpoints;
}


void tnbLib::blockEdge::write(Ostream& os, const dictionary& d) const
{
	blockVertex::write(os, start_, d);
	os << tab;
	blockVertex::write(os, end_, d);
	os << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const blockEdge& p)
{
	os << p.start_ << tab << p.end_ << endl;

	return os;
}


// ************************************************************************* //