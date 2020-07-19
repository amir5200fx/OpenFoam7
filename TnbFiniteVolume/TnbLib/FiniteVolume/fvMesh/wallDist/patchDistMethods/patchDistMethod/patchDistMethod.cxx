#include <patchDistMethod.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(patchDistMethod, 0);
	defineRunTimeSelectionTable(patchDistMethod, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchDistMethod::patchDistMethod
(
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
	:
	mesh_(mesh),
	patchIDs_(patchIDs)
{}


// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::patchDistMethod> tnbLib::patchDistMethod::New
(
	const dictionary& dict,
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
{
	word patchDistMethodType(dict.lookup("method"));

	Info << "Selecting patchDistMethod " << patchDistMethodType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(patchDistMethodType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patchDistMethodType type "
			<< patchDistMethodType << endl << endl
			<< "Valid patchDistMethod types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(dict, mesh, patchIDs);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchDistMethod::~patchDistMethod()
{}


// ************************************************************************* //