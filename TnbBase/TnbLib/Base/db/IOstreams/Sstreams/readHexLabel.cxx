#include <readHexLabel.hxx>

#include <ReadHex.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::label tnbLib::readHexLabel(ISstream& is)
{
	return ReadHex<label>(is);
}


// ************************************************************************* //