#include <noDecomp.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeName(noDecomp);

	addToRunTimeSelectionTable(decompositionMethod, noDecomp, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noDecomp::noDecomp(const dictionary& decompositionDict)
	:
	decompositionMethod(decompositionDict)
{}


// ************************************************************************* //