#include <blockVertex.hxx>

#include <pointVertex.hxx>
#include <blockMeshTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(blockVertex, 0);
	defineRunTimeSelectionTable(blockVertex, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockVertex::blockVertex()
{}


tnbLib::autoPtr<tnbLib::blockVertex> tnbLib::blockVertex::clone() const
{
	NotImplemented;
	return autoPtr<blockVertex>(nullptr);
}


tnbLib::autoPtr<tnbLib::blockVertex> tnbLib::blockVertex::New
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	Istream& is
)
{
	if (debug)
	{
		InfoInFunction << "Constructing blockVertex" << endl;
	}

	token firstToken(is);

	if (firstToken.isPunctuation() && firstToken.pToken() == token::BEGIN_LIST)
	{
		// Putback the opening bracket
		is.putBack(firstToken);

		return autoPtr<blockVertex>
			(
				new blockVertices::pointVertex(dict, index, geometry, is)
				);
	}
	else if (firstToken.isWord())
	{
		const word faceType(firstToken.wordToken());

		IstreamConstructorTable::iterator cstrIter =
			IstreamConstructorTablePtr_->find(faceType);

		if (cstrIter == IstreamConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown blockVertex type "
				<< faceType << nl << nl
				<< "Valid blockVertex types are" << endl
				<< IstreamConstructorTablePtr_->sortedToc()
				<< abort(FatalError);
		}

		return autoPtr<blockVertex>(cstrIter()(dict, index, geometry, is));
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "incorrect first token, expected <word> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);

		return autoPtr<blockVertex>(nullptr);
	}
}


tnbLib::label tnbLib::blockVertex::read(Istream& is, const dictionary& dict)
{
	const dictionary* varDictPtr = dict.subDictPtr("namedVertices");
	if (varDictPtr)
	{
		return blockMeshTools::read(is, *varDictPtr);
	}
	return readLabel(is);
}


void tnbLib::blockVertex::write
(
	Ostream& os,
	const label val,
	const dictionary& d
)
{
	const dictionary* varDictPtr = d.subDictPtr("namedVertices");
	if (varDictPtr)
	{
		blockMeshTools::write(os, val, *varDictPtr);
	}
	else
	{
		os << val;
	}
}


// ************************************************************************* //