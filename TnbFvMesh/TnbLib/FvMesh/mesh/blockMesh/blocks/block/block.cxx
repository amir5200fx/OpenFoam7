#include <block.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(block, 0);
	defineRunTimeSelectionTable(block, Istream);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::block::block
(
	const dictionary& dict,
	const label index,
	const pointField& vertices,
	const blockEdgeList& edges,
	const blockFaceList& faces,
	Istream& is
)
	:
	blockDescriptor(dict, index, vertices, edges, faces, is)
{
	createPoints();
	createBoundary();
}


tnbLib::block::block(const blockDescriptor& blockDesc)
	:
	blockDescriptor(blockDesc)
{
	createPoints();
	createBoundary();
}


tnbLib::autoPtr<tnbLib::block> tnbLib::block::New
(
	const dictionary& dict,
	const label index,
	const pointField& points,
	const blockEdgeList& edges,
	const blockFaceList& faces,
	Istream& is
)
{
	if (debug)
	{
		InfoInFunction << "Constructing block" << endl;
	}

	const word blockOrCellShapeType(is);

	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(blockOrCellShapeType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		is.putBack(blockOrCellShapeType);
		return autoPtr<block>(new block(dict, index, points, edges, faces, is));
	}
	else
	{
		return autoPtr<block>
			(
				cstrIter()
				(
					dict,
					index,
					points,
					edges,
					faces,
					is
					)
				);
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const block& b)
{
	os << b.points() << nl
		<< b.cells() << nl
		<< b.boundaryPatches() << endl;

	return os;
}


// ************************************************************************* //