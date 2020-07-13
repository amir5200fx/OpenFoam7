#include <topoSetSource.hxx>

#include <polyMesh.hxx>
#include <topoSet.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(topoSetSource, 0);
	defineRunTimeSelectionTable(topoSetSource, word);
	defineRunTimeSelectionTable(topoSetSource, istream);

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::topoSetSource::setAction,
		8
		>::names[] =
	{
		"clear",
		"new",
		"invert",
		"add",
		"delete",
		"subset",
		"list",
		"remove"
	};
}


tnbLib::HashTable<tnbLib::string>* tnbLib::topoSetSource::usageTablePtr_ = nullptr;


const tnbLib::NamedEnum<tnbLib::topoSetSource::setAction, 8>
tnbLib::topoSetSource::actionNames_;


const tnbLib::string tnbLib::topoSetSource::illegalSource_
(
	"Illegal topoSetSource name"
);



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::topoSetSource> tnbLib::topoSetSource::New
(
	const word& topoSetSourceType,
	const polyMesh& mesh,
	const dictionary& dict
)
{
	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(topoSetSourceType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown topoSetSource type " << topoSetSourceType
			<< endl << endl
			<< "Valid topoSetSource types : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<topoSetSource>(cstrIter()(mesh, dict));
}


tnbLib::autoPtr<tnbLib::topoSetSource> tnbLib::topoSetSource::New
(
	const word& topoSetSourceType,
	const polyMesh& mesh,
	Istream& is
)
{
	istreamConstructorTable::iterator cstrIter =
		istreamConstructorTablePtr_->find(topoSetSourceType);

	if (cstrIter == istreamConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown topoSetSource type " << topoSetSourceType
			<< endl << endl
			<< "Valid topoSetSource types : " << endl
			<< istreamConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<topoSetSource>(cstrIter()(mesh, is));
}


tnbLib::Istream& tnbLib::topoSetSource::checkIs(Istream& is)
{
	if (is.good() && !is.eof())
	{
		return is;
	}
	else
	{
		FatalErrorInFunction
			<< exit(FatalError);

		return is;
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::topoSetSource::addOrDelete
(
	topoSet& set,
	const label celli,
	const bool add
) const
{
	if (add)
	{
		set.insert(celli);
	}
	else
	{
		set.erase(celli);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::topoSetSource::topoSetSource(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::topoSetSource::~topoSetSource()
{}


// ************************************************************************* //