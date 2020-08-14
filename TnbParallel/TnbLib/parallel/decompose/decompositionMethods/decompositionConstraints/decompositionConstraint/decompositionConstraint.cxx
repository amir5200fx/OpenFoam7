#include <decompositionConstraint.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(decompositionConstraint, 1);
	defineRunTimeSelectionTable(decompositionConstraint, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionConstraint::decompositionConstraint
(
	const dictionary& constraintsDict,
	const word& type
)
	:
	coeffDict_(constraintsDict)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::decompositionConstraint>
tnbLib::decompositionConstraint::New
(
	const dictionary& dict,
	const word& modelType
)
{
	Info << "Selecting decompositionConstraint " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction(dict)
			<< "Unknown decompositionConstraint type "
			<< modelType << nl << nl
			<< "Valid decompositionConstraint types:" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<decompositionConstraint>
		(
			cstrIter()(dict, modelType)
			);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::decompositionConstraint::~decompositionConstraint()
{}


// ************************************************************************* //