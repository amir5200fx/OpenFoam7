#include <pointVertex.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockVertices
	{
		defineTypeNameAndDebug(pointVertex, 0);
		addToRunTimeSelectionTable(blockVertex, pointVertex, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockVertices::pointVertex::pointVertex
(
	const dictionary&,
	const label index,
	const searchableSurfaces& geometry,
	Istream& is
)
	:
	vertex_(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::blockVertices::pointVertex::operator tnbLib::point() const
{
	return vertex_;
}


// ************************************************************************* //