#include <namedBlock.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blocks
	{
		defineTypeNameAndDebug(namedBlock, 0);
		addToRunTimeSelectionTable(block, namedBlock, Istream);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blocks::namedBlock::namedBlock
(
	const dictionary& dict,
	const label index,
	const pointField& vertices,
	const blockEdgeList& edges,
	const blockFaceList& faces,
	Istream& is
)
	:
	word(is),
	block(dict, index, vertices, edges, faces, is)
{
	dictionary& d = const_cast<dictionary&>(dict);
	dictionary* varDictPtr = d.subDictPtr("namedBlocks");
	if (varDictPtr)
	{
		const_cast<dictionary&>(*varDictPtr).add(*this, index);
	}
	else
	{
		dictionary varDict;
		varDict.add(*this, index);
		d.add("namedBlocks", varDict);
	}
}


// ************************************************************************* //