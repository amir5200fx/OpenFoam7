#include <fileOperationInitialise.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <OSspecific.hxx>

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	namespace fileOperations
	{
		defineTypeNameAndDebug(fileOperationInitialise, 0);
		defineRunTimeSelectionTable(fileOperationInitialise, word);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileOperations::fileOperationInitialise::fileOperationInitialise
(
	int& argc,
	char**& argv
)
{}


tnbLib::autoPtr<tnbLib::fileOperations::fileOperationInitialise>
tnbLib::fileOperations::fileOperationInitialise::New
(
	const word& type,
	int& argc,
	char**& argv
)
{
	if (debug)
	{
		InfoInFunction << "Constructing fileOperationInitialise" << endl;
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(type);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown fileOperationInitialise type "
			<< type << nl << nl
			<< "Valid fileOperationInitialise types are" << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<fileOperationInitialise>(cstrIter()(argc, argv));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileOperations::fileOperationInitialise::~fileOperationInitialise()
{}


// ************************************************************************* //
