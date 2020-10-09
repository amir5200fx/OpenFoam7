#include <timeActivatedFileUpdate.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(timeActivatedFileUpdate, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			timeActivatedFileUpdate,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::timeActivatedFileUpdate::updateFile()
{
	label i = lastIndex_;
	while
		(
			i < timeVsFile_.size() - 1
			&& timeVsFile_[i + 1].first() < time_.value()
			)
	{
		i++;
	}

	if (i > lastIndex_)
	{
		Info << nl << type() << ": copying file" << nl << timeVsFile_[i].second()
			<< nl << "to:" << nl << fileToUpdate_ << nl << endl;

		fileName destFile(fileToUpdate_ + tnbLib::name(pid()));
		cp(timeVsFile_[i].second(), destFile);
		mv(destFile, fileToUpdate_);
		lastIndex_ = i;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::timeActivatedFileUpdate::timeActivatedFileUpdate
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(runTime),
	fileToUpdate_(dict.lookup("fileToUpdate")),
	timeVsFile_(),
	lastIndex_(-1)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::timeActivatedFileUpdate::~timeActivatedFileUpdate()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::timeActivatedFileUpdate::read
(
	const dictionary& dict
)
{
	dict.lookup("fileToUpdate") >> fileToUpdate_;
	dict.lookup("timeVsFile") >> timeVsFile_;

	lastIndex_ = -1;
	fileToUpdate_.expand();

	Info << type() << ": time vs file list:" << nl;
	forAll(timeVsFile_, i)
	{
		timeVsFile_[i].second() = timeVsFile_[i].second().expand();
		if (!isFile(timeVsFile_[i].second()))
		{
			FatalErrorInFunction
				<< "File: " << timeVsFile_[i].second() << " not found"
				<< nl << exit(FatalError);
		}

		Info << "    " << timeVsFile_[i].first() << tab
			<< timeVsFile_[i].second() << endl;
	}
	Info << endl;

	updateFile();

	return true;
}


bool tnbLib::functionObjects::timeActivatedFileUpdate::execute()
{
	updateFile();

	return true;
}


bool tnbLib::functionObjects::timeActivatedFileUpdate::write()
{
	return true;
}


// ************************************************************************* //