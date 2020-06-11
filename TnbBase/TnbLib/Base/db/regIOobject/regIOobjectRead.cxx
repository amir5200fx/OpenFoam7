#include <regIOobject.hxx>

#include <IFstream.hxx>
#include <Time.hxx>
#include <Pstream.hxx>
#include <HashSet.hxx>
#include <fileOperation.hxx>

#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::regIOobject::readHeaderOk
(
	const IOstream::streamFormat format,
	const word& typeName
)
{
	// Everyone check or just master
	bool masterOnly =
		global()
		&& (
			regIOobject::fileModificationChecking == timeStampMaster
			|| regIOobject::fileModificationChecking == inotifyMaster
			);


	// Check if header is ok for READ_IF_PRESENT
	bool isHeaderOk = false;
	if (readOpt() == IOobject::READ_IF_PRESENT)
	{
		if (masterOnly)
		{
			if (Pstream::master())
			{
				isHeaderOk = headerOk();
			}
			Pstream::scatter(isHeaderOk);
		}
		else
		{
			isHeaderOk = headerOk();
		}
	}

	if
		(
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| isHeaderOk
			)
	{
		return fileHandler().read(*this, masterOnly, format, typeName);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::regIOobject::readStream(const bool read)
{
	if (IFstream::debug)
	{
		InfoInFunction
			<< "Reading object " << name()
			<< " from file " << objectPath()
			<< endl;
	}

	if (readOpt() == NO_READ)
	{
		FatalErrorInFunction
			<< "NO_READ specified for read-constructor of object " << name()
			<< " of class " << headerClassName()
			<< abort(FatalError);
	}

	// Construct object stream and read header if not already constructed
	if (!isPtr_.valid())
	{
		fileName objPath;
		if (watchIndices_.size())
		{
			// File is being watched. Read exact file that is being watched.
			objPath = fileHandler().getFile(watchIndices_.last());
		}
		else
		{
			// Search intelligently for file
			objPath = filePath();

			if (IFstream::debug)
			{
				Pout << "regIOobject::readStream() : "
					<< "found object " << name()
					<< " (global " << global() << ")"
					<< " in file " << objPath
					<< endl;
			}
		}

		isPtr_ = fileHandler().readStream(*this, objPath, type(), read);
	}

	return isPtr_();
}


tnbLib::Istream& tnbLib::regIOobject::readStream
(
	const word& expectName,
	const bool read
)
{
	if (IFstream::debug)
	{
		Pout << "regIOobject::readStream(const word&) : "
			<< "reading object " << name()
			<< endl;
	}

	// Construct IFstream if not already constructed
	if (!isPtr_.valid())
	{
		readStream(read);

		// Check the className of the regIOobject
		// dictionary is an allowable name in case the actual class
		// instantiated is a dictionary
		if
			(
				read
				&& expectName.size()
				&& headerClassName() != expectName
				&& headerClassName() != "dictionary"
				)
		{
			FatalIOErrorInFunction(isPtr_())
				<< "unexpected class name " << headerClassName()
				<< " expected " << expectName << endl
				<< "    while reading object " << name()
				<< exit(FatalIOError);
		}
	}

	return isPtr_();
}


void tnbLib::regIOobject::close()
{
	if (IFstream::debug)
	{
		Pout << "regIOobject::close() : "
			<< "finished reading "
			<< (isPtr_.valid() ? isPtr_().name() : "dummy")
			<< endl;
	}

	isPtr_.clear();
}


bool tnbLib::regIOobject::readData(Istream&)
{
	return false;
}


bool tnbLib::regIOobject::read()
{
	// Note: cannot do anything in readStream itself since this is used by
	// e.g. GeometricField.


	// Save old watchIndices and clear (so the list of included files can
	// change)
	fileNameList oldWatchFiles;
	if (watchIndices_.size())
	{
		oldWatchFiles.setSize(watchIndices_.size());
		forAll(watchIndices_, i)
		{
			oldWatchFiles[i] = fileHandler().getFile(watchIndices_[i]);
		}
		forAllReverse(watchIndices_, i)
		{
			fileHandler().removeWatch(watchIndices_[i]);
		}
		watchIndices_.clear();
	}


	// Read
	bool masterOnly =
		global()
		&& (
			regIOobject::fileModificationChecking == timeStampMaster
			|| regIOobject::fileModificationChecking == inotifyMaster
			);

	// Note: IOstream::binary flag is for all the processor comms. (Only for
	//       dictionaries should it be ascii)
	bool ok = fileHandler().read(*this, masterOnly, IOstream::BINARY, type());

	if (oldWatchFiles.size())
	{
		// Re-watch master file
		addWatch();
	}

	return ok;
}


bool tnbLib::regIOobject::modified() const
{
	forAllReverse(watchIndices_, i)
	{
		if (fileHandler().getState(watchIndices_[i]) != fileMonitor::UNMODIFIED)
		{
			return true;
		}
	}

	return false;
}


bool tnbLib::regIOobject::readIfModified()
{
	// Get index of modified file so we can give nice message. Could instead
	// just call above modified()
	label modified = -1;
	forAllReverse(watchIndices_, i)
	{
		if (fileHandler().getState(watchIndices_[i]) != fileMonitor::UNMODIFIED)
		{
			modified = watchIndices_[i];
			break;
		}
	}

	if (modified != -1)
	{
		const fileName fName = fileHandler().getFile(watchIndices_.last());

		if (modified == watchIndices_.last())
		{
			Info << "regIOobject::readIfModified() : " << nl
				<< "    Re-reading object " << name()
				<< " from file " << fName << endl;
		}
		else
		{
			Info << "regIOobject::readIfModified() : " << nl
				<< "    Re-reading object " << name()
				<< " from file " << fName
				<< " because of modified file "
				<< fileHandler().getFile(modified)
				<< endl;
		}

		return read();
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //