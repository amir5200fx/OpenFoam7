#include <TimeScaleModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(TimeScaleModel, 0);
	defineRunTimeSelectionTable(TimeScaleModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimeScaleModel::TimeScaleModel
(
	const dictionary& dict
)
	:
	alphaPacked_(readScalar(dict.lookup("alphaPacked"))),
	e_(readScalar(dict.lookup("e")))
{
}


tnbLib::TimeScaleModel::TimeScaleModel
(
	const TimeScaleModel& cm
)
	:
	alphaPacked_(cm.alphaPacked_),
	e_(cm.e_)
{
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::TimeScaleModel> tnbLib::TimeScaleModel::New
(
	const dictionary& dict
)
{
	word modelType(dict.lookup("type"));

	Info << "Selecting time scale model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown time scale model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid time scale model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<TimeScaleModel>(cstrIter()(dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::TimeScaleModel::~TimeScaleModel()
{}


// ************************************************************************* //