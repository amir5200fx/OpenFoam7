#include <IOobject.hxx>

#include <Time.hxx>
#include <IFstream.hxx>
#include <fileOperation.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(IOobject, 0);

	template<>
	const char* NamedEnum
		<
		IOobject::fileCheckTypes,
		4
		>::names[] =
	{
		"timeStamp",
		"timeStampMaster",
		"inotify",
		"inotifyMaster"
	};
}


const tnbLib::NamedEnum<tnbLib::IOobject::fileCheckTypes, 4>
tnbLib::IOobject::fileCheckTypesNames;

// Default fileCheck type
tnbLib::IOobject::fileCheckTypes tnbLib::IOobject::fileModificationChecking
(
	fileCheckTypesNames.read
	(
		debug::optimisationSwitches().lookup
		(
			"fileModificationChecking"
		)
	)
);

namespace tnbLib
{
	// Register re-reader
	class addfileModificationCheckingToOpt
		:
		public ::tnbLib::simpleRegIOobject
	{
	public:

		addfileModificationCheckingToOpt(const char* name)
			:
			::tnbLib::simpleRegIOobject(tnbLib::debug::addOptimisationObject, name)
		{}

		virtual ~addfileModificationCheckingToOpt()
		{}

		virtual void readData(tnbLib::Istream& is)
		{
			IOobject::fileModificationChecking =
				IOobject::fileCheckTypesNames.read(is);
		}

		virtual void writeData(tnbLib::Ostream& os) const
		{
			os << IOobject::fileCheckTypesNames
				[IOobject::fileModificationChecking];
		}
	};

	addfileModificationCheckingToOpt addfileModificationCheckingToOpt_
	(
		"fileModificationChecking"
	);
}


// * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * * //

bool tnbLib::IOobject::fileNameComponents
(
	const fileName& path,
	fileName& instance,
	fileName& local,
	word& name
)
{
	instance.clear();
	local.clear();
	name.clear();

	// called with directory
	if (isDir(path))
	{
		WarningInFunction
			<< " called with directory: " << path << endl;

		return false;
	}

	if (path.isAbsolute())
	{
		string::size_type last = path.rfind('/');
		instance = path.substr(0, last);

		// Check afterwards
		name.string::operator=(path.substr(last + 1));
	}
	else
	{
		string::size_type first = path.find('/');

		if (first == string::npos)
		{
			// no '/' found - no instance or local

			// check afterwards
			name.string::operator=(path);
		}
		else
		{
			instance = path.substr(0, first);

			string::size_type last = path.rfind('/');
			if (last > first)
			{
				// with local
				local = path.substr(first + 1, last - first - 1);
			}

			// check afterwards
			name.string::operator=(path.substr(last + 1));
		}
	}


	// Check for valid (and stripped) name, regardless of the debug level
	if (name.empty() || string::stripInvalid<word>(name))
	{
		WarningInFunction
			<< "has invalid word for name: \"" << name
			<< "\"\nwhile processing path: " << path << endl;

		return false;
	}

	return true;
}


tnbLib::word tnbLib::IOobject::group(const word& name)
{
	word::size_type i = name.find_last_of('.');

	if (i == word::npos || i == 0)
	{
		return word::null;
	}
	else
	{
		return name.substr(i + 1, word::npos);
	}
}


tnbLib::word tnbLib::IOobject::member(const word& name)
{
	word::size_type i = name.find_last_of('.');

	if (i == word::npos || i == 0)
	{
		return name;
	}
	else
	{
		return name.substr(0, i);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOobject::IOobject
(
	const word& name,
	const fileName& instance,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(name),
	headerClassName_(typeName),
	note_(),
	instance_(instance),
	local_(),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (objectRegistry::debug)
	{
		InfoInFunction
			<< "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const word& name,
	const fileName& instance,
	const fileName& local,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(name),
	headerClassName_(typeName),
	note_(),
	instance_(instance),
	local_(local),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (objectRegistry::debug)
	{
		InfoInFunction
			<< "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const fileName& path,
	const objectRegistry& registry,
	readOption ro,
	writeOption wo,
	bool registerObject
)
	:
	name_(),
	headerClassName_(typeName),
	note_(),
	instance_(),
	local_(),
	db_(registry),
	rOpt_(ro),
	wOpt_(wo),
	registerObject_(registerObject),
	objState_(GOOD)
{
	if (!fileNameComponents(path, instance_, local_, name_))
	{
		FatalErrorInFunction
			<< " invalid path specification"
			<< exit(FatalError);
	}

	if (objectRegistry::debug)
	{
		InfoInFunction
			<< "Constructing IOobject called " << name_
			<< " of type " << headerClassName_
			<< endl;
	}
}


tnbLib::IOobject::IOobject
(
	const IOobject& io,
	const objectRegistry& registry
)
	:
	name_(io.name_),
	headerClassName_(io.headerClassName_),
	note_(io.note_),
	instance_(io.instance_),
	local_(io.local_),
	db_(registry),
	rOpt_(io.rOpt_),
	wOpt_(io.wOpt_),
	registerObject_(io.registerObject_),
	objState_(io.objState_)
{}


tnbLib::IOobject::IOobject
(
	const IOobject& io,
	const word& name
)
	:
	name_(name),
	headerClassName_(io.headerClassName_),
	note_(io.note_),
	instance_(io.instance_),
	local_(io.local_),
	db_(io.db_),
	rOpt_(io.rOpt_),
	wOpt_(io.wOpt_),
	registerObject_(io.registerObject_),
	objState_(io.objState_)
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

tnbLib::IOobject::~IOobject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::objectRegistry& tnbLib::IOobject::db() const
{
	return db_;
}


const tnbLib::Time& tnbLib::IOobject::time() const
{
	return db_.time();
}


const tnbLib::fileName& tnbLib::IOobject::caseName() const
{
	return time().caseName();
}


tnbLib::word tnbLib::IOobject::group() const
{
	return group(name_);
}


tnbLib::word tnbLib::IOobject::member() const
{
	return member(name_);
}


const tnbLib::fileName& tnbLib::IOobject::rootPath() const
{
	return time().rootPath();
}


tnbLib::fileName tnbLib::IOobject::path() const
{
	if (instance().isAbsolute())
	{
		return instance();
	}
	else
	{
		return rootPath() / caseName() / instance() / db_.dbDir() / local();
	}
}


tnbLib::fileName tnbLib::IOobject::path
(
	const word& instance,
	const fileName& local
) const
{
	// Note: can only be called with relative instance since is word type
	return rootPath() / caseName() / instance / db_.dbDir() / local;
}


tnbLib::fileName tnbLib::IOobject::localFilePath(const word& typeName) const
{
	// Do not check for undecomposed files
	return fileHandler().filePath(false, *this, typeName);
}


tnbLib::fileName tnbLib::IOobject::globalFilePath(const word& typeName) const
{
	// Check for undecomposed files
	return fileHandler().filePath(true, *this, typeName);
}


void tnbLib::IOobject::setBad(const string& s)
{
	if (objState_ != GOOD)
	{
		FatalErrorInFunction
			<< "Recurrent failure for object " << s
			<< exit(FatalError);
	}

	if (error::level)
	{
		InfoInFunction
			<< "Broken object " << s << info() << endl;
	}

	objState_ = BAD;
}


void tnbLib::IOobject::operator=(const IOobject& io)
{
	name_ = io.name_;
	headerClassName_ = io.headerClassName_;
	note_ = io.note_;
	instance_ = io.instance_;
	local_ = io.local_;
	rOpt_ = io.rOpt_;
	wOpt_ = io.wOpt_;
	objState_ = io.objState_;
}


// ************************************************************************* //