#include <namedVertex.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockVertices
	{
		defineTypeNameAndDebug(namedVertex, 0);
		addToRunTimeSelectionTable(blockVertex, namedVertex, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockVertices::namedVertex::namedVertex
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	Istream& is
)
	:
	name_(is),
	vertexPtr_(blockVertex::New(dict, index, geometry, is))
{
	dictionary& d = const_cast<dictionary&>(dict);

	dictionary* varDictPtr = d.subDictPtr("namedVertices");
	if (varDictPtr)
	{
		const_cast<dictionary&>(*varDictPtr).add(name_, index);
	}
	else
	{
		dictionary varDict;
		varDict.add(name_, index);
		d.add("namedVertices", varDict);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::blockVertices::namedVertex::operator tnbLib::point() const
{
	return vertexPtr_().operator point();
}


// ************************************************************************* //