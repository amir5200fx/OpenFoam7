#include <regIOobject.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>
#include <registerSwitch.hxx>
#include <fileOperation.hxx>

#include <Pstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regIOobject, 0);
}

float tnbLib::regIOobject::fileModificationSkew
(
	tnbLib::debug::floatOptimisationSwitch("fileModificationSkew", 30)
);

registerOptSwitch
(
	"fileModificationSkew",
	float,
	tnbLib::regIOobject::fileModificationSkew
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regIOobject::regIOobject(const IOobject& io, const bool isTime)
	:
	IOobject(io),
	registered_(false),
	ownedByRegistry_(false),
	watchIndices_(),
	eventNo_                // Do not get event for top level Time database
	(
		isTime
		? 0
		: db().getEvent()
	)
{
	// Register with objectRegistry if requested
	if (registerObject())
	{
		checkIn();
	}
}


tnbLib::regIOobject::regIOobject(const regIOobject& rio)
	:
	IOobject(rio),
	registered_(false),
	ownedByRegistry_(false),
	watchIndices_(rio.watchIndices_),
	eventNo_(db().getEvent())
{
	// Do not register copy with objectRegistry
}


tnbLib::regIOobject::regIOobject(const regIOobject& rio, bool registerCopy)
	:
	IOobject(rio),
	registered_(false),
	ownedByRegistry_(false),
	watchIndices_(),
	eventNo_(db().getEvent())
{
	if (registerCopy)
	{
		if (rio.registered_)
		{
			const_cast<regIOobject&>(rio).checkOut();
		}
		checkIn();
	}
}


tnbLib::regIOobject::regIOobject
(
	const word& newName,
	const regIOobject& rio,
	bool registerCopy
)
	:
	IOobject(newName, rio.instance(), rio.local(), rio.db()),
	registered_(false),
	ownedByRegistry_(false),
	watchIndices_(),
	eventNo_(db().getEvent())
{
	if (registerCopy)
	{
		checkIn();
	}
}


tnbLib::regIOobject::regIOobject
(
	const IOobject& io,
	const regIOobject& rio
)
	:
	IOobject(io),
	registered_(false),
	ownedByRegistry_(false),
	watchIndices_(),
	eventNo_(db().getEvent())
{
	if (registerObject())
	{
		checkIn();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regIOobject::~regIOobject()
{
	if (objectRegistry::debug)
	{
		if (this == &db())
		{
			Pout << "Destroying objectRegistry " << name()
				<< " in directory " << rootPath() / caseName() / instance()
				<< endl;
		}
		else
		{
			Pout << "Destroying regIOobject " << name()
				<< " in directory " << path()
				<< endl;
		}
	}

	// Check out of objectRegistry if not owned by the registry
	if (!ownedByRegistry_)
	{
		checkOut();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::regIOobject::checkIn()
{
	if (!registered_)
	{
		// multiple checkin of same object is disallowed - this would mess up
		// any mapping
		registered_ = db().checkIn(*this);

		// check-in on defaultRegion is allowed to fail, since subsetted meshes
		// are created with the same name as their originating mesh
		if (!registered_ && debug && name() != polyMesh::defaultRegion)
		{
			if (debug == 2)
			{
				// for ease of finding where attempted duplicate check-in
				// originated
				FatalErrorInFunction
					<< "failed to register object " << objectPath()
					<< " the name already exists in the objectRegistry" << endl
					<< "Contents:" << db().sortedToc()
					<< abort(FatalError);
			}
			else
			{
				WarningInFunction
					<< "failed to register object " << objectPath()
					<< " the name already exists in the objectRegistry"
					<< endl;
			}
		}
	}

	return registered_;
}


bool tnbLib::regIOobject::checkOut()
{
	if (registered_)
	{
		registered_ = false;

		forAllReverse(watchIndices_, i)
		{
			fileHandler().removeWatch(watchIndices_[i]);
		}
		watchIndices_.clear();
		return db().checkOut(*this);
	}

	return false;
}


tnbLib::label tnbLib::regIOobject::addWatch(const fileName& f)
{
	label index = -1;

	if
		(
			registered_
			&& readOpt() == MUST_READ_IF_MODIFIED
			&& time().runTimeModifiable()
			)
	{
		index = fileHandler().findWatch(watchIndices_, f);

		if (index == -1)
		{
			index = watchIndices_.size();
			watchIndices_.append(fileHandler().addWatch(f));
		}
	}
	return index;
}


void tnbLib::regIOobject::addWatch()
{
	if
		(
			registered_
			&& readOpt() == MUST_READ_IF_MODIFIED
			&& time().runTimeModifiable()
			)
	{
		fileName f = filePath();
		if (!f.size())
		{
			// We don't have this file but would like to re-read it.
			// Possibly if master-only reading mode.
			f = objectPath();
		}

		label index = fileHandler().findWatch(watchIndices_, f);
		if (index != -1)
		{
			FatalErrorIn("regIOobject::addWatch()")
				<< "Object " << objectPath() << " of type " << type()
				<< " already watched with index " << watchIndices_[index]
				<< abort(FatalError);
		}

		// If master-only reading only the master will have all dependencies
		// so scatter these to slaves
		bool masterOnly =
			global()
			&& (
				regIOobject::fileModificationChecking == timeStampMaster
				|| regIOobject::fileModificationChecking == inotifyMaster
				);

		if (masterOnly && Pstream::parRun())
		{
			// Get master watched files
			fileNameList watchFiles;
			if (Pstream::master())
			{
				watchFiles.setSize(watchIndices_.size());
				forAll(watchIndices_, i)
				{
					watchFiles[i] = fileHandler().getFile(watchIndices_[i]);
				}
			}
			Pstream::scatter(watchFiles);

			if (!Pstream::master())
			{
				// unregister current ones
				forAllReverse(watchIndices_, i)
				{
					fileHandler().removeWatch(watchIndices_[i]);
				}

				watchIndices_.clear();
				forAll(watchFiles, i)
				{
					watchIndices_.append(fileHandler().addWatch(watchFiles[i]));
				}
			}
		}

		watchIndices_.append(fileHandler().addWatch(f));
	}
}


bool tnbLib::regIOobject::upToDate(const regIOobject& a) const
{
	if (a.eventNo() >= eventNo_)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate
(
	const regIOobject& a,
	const regIOobject& b
) const
{
	if
		(
			a.eventNo() >= eventNo_
			|| b.eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate
(
	const regIOobject& a,
	const regIOobject& b,
	const regIOobject& c
) const
{
	if
		(
			a.eventNo() >= eventNo_
			|| b.eventNo() >= eventNo_
			|| c.eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::regIOobject::upToDate
(
	const regIOobject& a,
	const regIOobject& b,
	const regIOobject& c,
	const regIOobject& d
) const
{
	if
		(
			a.eventNo() >= eventNo_
			|| b.eventNo() >= eventNo_
			|| c.eventNo() >= eventNo_
			|| d.eventNo() >= eventNo_
			)
	{
		return false;
	}
	else
	{
		return true;
	}
}


void tnbLib::regIOobject::setUpToDate()
{
	eventNo_ = db().getEvent();
}


void tnbLib::regIOobject::rename(const word& newName)
{
	// Check out of objectRegistry
	checkOut();

	IOobject::rename(newName);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}


tnbLib::fileName tnbLib::regIOobject::filePath() const
{
	return localFilePath(type());
}


bool tnbLib::regIOobject::headerOk()
{
	// Note: Should be consistent with IOobject::typeHeaderOk(false)

	bool ok = true;

	fileName fName(filePath());

	ok = tnbLib::fileHandler().readHeader(*this, fName, type());

	if (!ok && IOobject::debug)
	{
		IOWarningInFunction(fName)
			<< "failed to read header of file " << objectPath()
			<< endl;
	}

	return ok;
}


bool tnbLib::regIOobject::global() const
{
	return false;
}


void tnbLib::regIOobject::operator=(const IOobject& io)
{
	// Close any file
	isPtr_.clear();

	// Check out of objectRegistry
	checkOut();

	IOobject::operator=(io);

	if (registerObject())
	{
		// Re-register object with objectRegistry
		checkIn();
	}
}


// ************************************************************************* //