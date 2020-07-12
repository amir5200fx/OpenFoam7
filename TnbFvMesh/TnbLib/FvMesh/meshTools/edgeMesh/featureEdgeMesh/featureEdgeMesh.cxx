#include <featureEdgeMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(featureEdgeMesh, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::featureEdgeMesh::featureEdgeMesh(const IOobject& io)
	:
	regIOobject(io),
	edgeMesh(pointField(0), edgeList(0))
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}

	if (debug)
	{
		Pout << "featureEdgeMesh::featureEdgeMesh :"
			<< " constructed from IOobject :"
			<< " points:" << points().size()
			<< " edges:" << edges().size()
			<< endl;
	}
}


tnbLib::featureEdgeMesh::featureEdgeMesh
(
	const IOobject& io,
	const pointField& points,
	const edgeList& edges
)
	:
	regIOobject(io),
	edgeMesh(points, edges)
{}


// Copy constructor
tnbLib::featureEdgeMesh::featureEdgeMesh
(
	const IOobject& io,
	const featureEdgeMesh& em
)
	:
	regIOobject(io),
	edgeMesh(em)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::featureEdgeMesh::readData(Istream& is)
{
	is >> *this;
	return !is.bad();
}


bool tnbLib::featureEdgeMesh::writeData(Ostream& os) const
{
	os << *this;

	return os.good();
}


// ************************************************************************* //