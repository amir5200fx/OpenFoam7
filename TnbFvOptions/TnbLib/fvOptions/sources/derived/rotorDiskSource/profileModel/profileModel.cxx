#include <profileModel.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(profileModel, 0);
	defineRunTimeSelectionTable(profileModel, dictionary);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

bool tnbLib::profileModel::readFromFile() const
{
	return fName_ != fileName::null;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profileModel::profileModel(const dictionary& dict, const word& name)
	:
	dict_(dict),
	name_(name),
	fName_(fileName::null)
{
	dict.readIfPresent("file", fName_);
}

// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::profileModel::~profileModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::profileModel::name() const
{
	return name_;
}


tnbLib::autoPtr<tnbLib::profileModel> tnbLib::profileModel::New
(
	const dictionary& dict
)
{
	const word& modelName(dict.dictName());

	const word modelType(dict.lookup("type"));

	Info << "    - creating " << modelType << " profile " << modelName << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown profile model type " << modelType
			<< nl << nl
			<< "Valid model types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<profileModel>(cstrIter()(dict, modelName));
}


// ************************************************************************* //