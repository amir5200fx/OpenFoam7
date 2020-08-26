#include <CorrectionLimitingMethod.hxx>

namespace tnbLib
{
	defineTypeNameAndDebug(CorrectionLimitingMethod, 0);
	defineRunTimeSelectionTable(CorrectionLimitingMethod, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethod::CorrectionLimitingMethod
(
	const dictionary& dict
)
{}


tnbLib::CorrectionLimitingMethod::CorrectionLimitingMethod
(
	const CorrectionLimitingMethod& cl
)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::CorrectionLimitingMethod>
tnbLib::CorrectionLimitingMethod::New
(
	const dictionary& dict
)
{
	word modelType(dict.lookup("type"));

	Info << "Selecting correction limiter " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown correction limiter type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid correction limiter types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<CorrectionLimitingMethod>(cstrIter()(dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethod::~CorrectionLimitingMethod()
{}


// ************************************************************************* //