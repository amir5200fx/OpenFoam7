#include <logFiles.hxx>

#include <Time.hxx>
#include <IFstream.hxx>

#include <Pstream.hxx>  // added by amir

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::logFiles::createFiles()
{
	if (Pstream::master())
	{
		const word startTimeName =
			fileObr_.time().timeName(fileObr_.time().startTime().value());

		forAll(names_, i)
		{
			if (!filePtrs_.set(i))
			{
				fileName outputDir(baseFileDir() / prefix_ / startTimeName);
				mkDir(outputDir);

				word fName(names_[i]);

				// Check if file already exists
				IFstream is(outputDir / (fName + ".dat"));
				if (is.good())
				{
					fName = fName + "_" + fileObr_.time().timeName();
				}

				filePtrs_.set(i, new OFstream(outputDir / (fName + ".dat")));

				initStream(filePtrs_[i]);

				writeFileHeader(i);
			}
		}
	}
}


void tnbLib::functionObjects::logFiles::resetNames(const wordList& names)
{
	names_.clear();
	names_.append(names);

	if (Pstream::master())
	{
		filePtrs_.clear();
		filePtrs_.setSize(names_.size());
	}
}


void tnbLib::functionObjects::logFiles::resetName(const word& name)
{
	names_.clear();
	names_.append(name);

	if (Pstream::master())
	{
		filePtrs_.clear();
		filePtrs_.setSize(1);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::logFiles::logFiles
(
	const objectRegistry& obr,
	const word& prefix
)
	:
	writeFile(obr, prefix),
	names_(),
	filePtrs_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::logFiles::~logFiles()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::wordList& tnbLib::functionObjects::logFiles::names() const
{
	return names_;
}


tnbLib::OFstream& tnbLib::functionObjects::logFiles::file()
{
	if (!Pstream::master())
	{
		FatalErrorInFunction
			<< "Request for file() can only be done by the master process"
			<< abort(FatalError);
	}

	if (filePtrs_.size() != 1)
	{
		WarningInFunction
			<< "Requested single file, but multiple files are present"
			<< endl;
	}

	if (!filePtrs_.set(0))
	{
		FatalErrorInFunction
			<< "File pointer at index " << 0 << " not allocated"
			<< abort(FatalError);
	}

	return filePtrs_[0];
}


tnbLib::PtrList<tnbLib::OFstream>& tnbLib::functionObjects::logFiles::files()
{
	if (!Pstream::master())
	{
		FatalErrorInFunction
			<< "Request for files() can only be done by the master process"
			<< abort(FatalError);
	}

	return filePtrs_;
}


tnbLib::OFstream& tnbLib::functionObjects::logFiles::file(const label i)
{
	if (!Pstream::master())
	{
		FatalErrorInFunction
			<< "Request for file(i) can only be done by the master process"
			<< abort(FatalError);
	}

	if (!filePtrs_.set(i))
	{
		FatalErrorInFunction
			<< "File pointer at index " << i << " not allocated"
			<< abort(FatalError);
	}

	return filePtrs_[i];
}


bool tnbLib::functionObjects::logFiles::write()
{
	createFiles();

	return true;
}


// ************************************************************************* //