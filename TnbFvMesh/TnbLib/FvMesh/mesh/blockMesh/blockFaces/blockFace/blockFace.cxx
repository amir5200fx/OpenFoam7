#include <blockFace.hxx>

#include <blockMeshTools.hxx>
#include <blockVertex.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(blockFace, 0);
	defineRunTimeSelectionTable(blockFace, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockFace::blockFace(const face& vertices)
	:
	vertices_(vertices)
{}


tnbLib::blockFace::blockFace
(
	const dictionary& dict,
	const label index,
	Istream& is
)
	:
	vertices_
	(
		blockMeshTools::read<label>
		(
			is,
			dict.subOrEmptyDict("namedVertices")
			)
	)
{}


tnbLib::autoPtr<tnbLib::blockFace> tnbLib::blockFace::clone() const
{
	NotImplemented;
	return autoPtr<blockFace>(nullptr);
}


tnbLib::autoPtr<tnbLib::blockFace> tnbLib::blockFace::New
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	Istream& is
)
{
	if (debug)
	{
		InfoInFunction << "Constructing blockFace" << endl;
	}

	const word faceType(is);

	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(faceType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown blockFace type "
			<< faceType << nl << nl
			<< "Valid blockFace types are" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<blockFace>(cstrIter()(dict, index, geometry, is));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::blockFace::write(Ostream& os, const dictionary& d) const
{
	// Write size and start delimiter
	os << vertices_.size() << token::BEGIN_LIST;

	// Write contents
	forAll(vertices_, i)
	{
		if (i > 0) os << token::SPACE;
		blockVertex::write(os, vertices_[i], d);
	}

	// Write end delimiter
	os << token::END_LIST;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const blockFace& p)
{
	os << p.vertices_ << endl;

	return os;
}


// ************************************************************************* //