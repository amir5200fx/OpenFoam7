#include <uncollatedFileOperation.hxx>

#include <Time.hxx>
#include <IFstream.hxx>
#include <OFstream.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <decomposedBlockData.hxx>
#include <dummyISstream.hxx>
#include <unthreadedInitialise.hxx>

#include <IPstream.hxx>  // added by amir
#include <OPstream.hxx>  // added by amir
#include <Pstream.hxx>  // added by amir
#include <IOstreams.hxx>  // added by amir
#include <tmpNrc.hxx>  // added by amir
#include <fileOperation.hxx>  // added by amir
#include <Tuple2.hxx>  // added by amir

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

namespace tnbLib
{
	namespace fileOperations
	{
		defineTypeNameAndDebug(uncollatedFileOperation, 0);
		addToRunTimeSelectionTable(fileOperation, uncollatedFileOperation, word);

		// Mark as not needing threaded mpi
		addNamedToRunTimeSelectionTable
		(
			fileOperationInitialise,
			unthreadedInitialise,
			word,
			uncollated
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::fileName tnbLib::fileOperations::uncollatedFileOperation::filePathInfo
(
	const bool checkGlobal,
	const bool isFile,
	const IOobject& io
) const
{
	if (io.instance().isAbsolute())
	{
		fileName objectPath = io.instance() / io.name();

		if (isFileOrDir(isFile, objectPath))
		{
			return objectPath;
		}
		else
		{
			return fileName::null;
		}
	}
	else
	{
		fileName path = io.path();
		fileName objectPath = path / io.name();

		if (isFileOrDir(isFile, objectPath))
		{
			return objectPath;
		}
		else
		{
			if
				(
					checkGlobal
					&& io.time().processorCase()
					&& (
						io.instance() == io.time().system()
						|| io.instance() == io.time().constant()
						)
					)
			{
				// Constant & system can come from global case

				fileName parentObjectPath =
					io.rootPath() / io.time().globalCaseName()
					/ io.instance() / io.db().dbDir() / io.local() / io.name();

				if (isFileOrDir(isFile, parentObjectPath))
				{
					return parentObjectPath;
				}
			}

			// Check if parallel "procesors" directory
			if (io.time().processorCase())
			{
				tmpNrc<dirIndexList> pDirs
				(
					lookupProcessorsPath(io.objectPath())
				);
				forAll(pDirs(), i)
				{
					const fileName& pDir = pDirs()[i].first();
					fileName objPath =
						processorsPath(io, io.instance(), pDir)
						/ io.name();
					if (objPath != objectPath && isFileOrDir(isFile, objPath))
					{
						return objPath;
					}
				}
			}


			// Check for approximately same time. E.g. if time = 1e-2 and
			// directory is 0.01 (due to different time formats)
			if (!tnbLib::isDir(path))
			{
				word newInstancePath = io.time().findInstancePath
				(
					instant(io.instance())
				);

				if (newInstancePath.size())
				{
					fileName fName
					(
						io.rootPath() / io.caseName()
						/ newInstancePath / io.db().dbDir() / io.local() / io.name()
					);

					if (isFileOrDir(isFile, fName))
					{
						return fName;
					}
				}
			}
		}

		return fileName::null;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileOperations::uncollatedFileOperation::uncollatedFileOperation
(
	const bool verbose
)
	:
	fileOperation(Pstream::worldComm)
{
	if (verbose)
	{
		InfoHeader << "I/O    : " << typeName << endl;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fileOperations::uncollatedFileOperation::~uncollatedFileOperation()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileOperations::uncollatedFileOperation::mkDir
(
	const fileName& dir,
	mode_t mode
) const
{
	return tnbLib::mkDir(dir, mode);
}


bool tnbLib::fileOperations::uncollatedFileOperation::chMod
(
	const fileName& fName,
	mode_t mode
) const
{
	return tnbLib::chMod(fName, mode);
}


tnbLib::mode_t 
tnbLib::fileOperations::uncollatedFileOperation::mode
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::mode(fName, checkVariants, followLink);
}


tnbLib::fileType tnbLib::fileOperations::uncollatedFileOperation::type
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::type(fName, checkVariants, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::exists
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::exists(fName, checkVariants, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::isDir
(
	const fileName& fName,
	const bool followLink
) const
{
	return tnbLib::isDir(fName, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::isFile
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::isFile(fName, checkVariants, followLink);
}


off_t tnbLib::fileOperations::uncollatedFileOperation::fileSize
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::fileSize(fName, checkVariants, followLink);
}


time_t tnbLib::fileOperations::uncollatedFileOperation::lastModified
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::lastModified(fName, checkVariants, followLink);
}


double tnbLib::fileOperations::uncollatedFileOperation::highResLastModified
(
	const fileName& fName,
	const bool checkVariants,
	const bool followLink
) const
{
	return tnbLib::highResLastModified(fName, checkVariants, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::mvBak
(
	const fileName& fName,
	const std::string& ext
) const
{
	return tnbLib::mvBak(fName, ext);
}


bool tnbLib::fileOperations::uncollatedFileOperation::rm
(
	const fileName& fName
) const
{
	return tnbLib::rm(fName);
}


bool tnbLib::fileOperations::uncollatedFileOperation::rmDir
(
	const fileName& dir
) const
{
	return tnbLib::rmDir(dir);
}


tnbLib::fileNameList tnbLib::fileOperations::uncollatedFileOperation::readDir
(
	const fileName& dir,
	const fileType type,
	const bool filtergz,
	const bool followLink
) const
{
	return tnbLib::readDir(dir, type, filtergz, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::cp
(
	const fileName& src,
	const fileName& dst,
	const bool followLink
) const
{
	return tnbLib::cp(src, dst, followLink);
}


bool tnbLib::fileOperations::uncollatedFileOperation::ln
(
	const fileName& src,
	const fileName& dst
) const
{
	return tnbLib::ln(src, dst);
}


bool tnbLib::fileOperations::uncollatedFileOperation::mv
(
	const fileName& src,
	const fileName& dst,
	const bool followLink
) const
{
	return tnbLib::mv(src, dst, followLink);
}


tnbLib::fileName tnbLib::fileOperations::uncollatedFileOperation::filePath
(
	const bool checkGlobal,
	const IOobject& io,
	const word& typeName
) const
{
	if (debug)
	{
		Pout << "uncollatedFileOperation::filePath :"
			<< " objectPath:" << io.objectPath()
			<< " checkGlobal:" << checkGlobal << endl;
	}

	fileName objPath(filePathInfo(checkGlobal, true, io));

	if (debug)
	{
		Pout << "uncollatedFileOperation::filePath :"
			<< " Returning from file searching:" << endl
			<< "    objectPath:" << io.objectPath() << endl
			<< "    filePath  :" << objPath << endl << endl;
	}
	return objPath;
}


tnbLib::fileName tnbLib::fileOperations::uncollatedFileOperation::dirPath
(
	const bool checkGlobal,
	const IOobject& io
) const
{
	if (debug)
	{
		Pout << "uncollatedFileOperation::dirPath :"
			<< " objectPath:" << io.objectPath()
			<< " checkGlobal:" << checkGlobal << endl;
	}

	fileName objPath(filePathInfo(checkGlobal, false, io));

	if (debug)
	{
		Pout << "uncollatedFileOperation::dirPath :"
			<< " Returning from directory searching:" << endl
			<< "    objectPath:" << io.objectPath() << endl
			<< "    dirPath   :" << objPath << endl << endl;
	}
	return objPath;
}


tnbLib::fileNameList tnbLib::fileOperations::uncollatedFileOperation::readObjects
(
	const objectRegistry& db,
	const fileName& instance,
	const fileName& local,
	word& newInstance
) const
{
	if (debug)
	{
		Pout << "uncollatedFileOperation::readObjects :"
			<< " db:" << db.objectPath()
			<< " instance:" << instance << endl;
	}

	//- Use non-time searching version
	fileNameList objectNames
	(
		fileOperation::readObjects(db, instance, local, newInstance)
	);

	if (newInstance.empty())
	{
		// Find similar time
		fileName newInst = db.time().findInstancePath(instant(instance));
		if (!newInst.empty() && newInst != instance)
		{
			// Try with new time
			objectNames = fileOperation::readObjects
			(
				db,
				newInst,
				local,
				newInstance
			);
		}
	}

	if (debug)
	{
		Pout << "uncollatedFileOperation::readObjects :"
			<< " newInstance:" << newInstance
			<< " objectNames:" << objectNames << endl;
	}

	return objectNames;
}


bool tnbLib::fileOperations::uncollatedFileOperation::readHeader
(
	IOobject& io,
	const fileName& fName,
	const word& typeName
) const
{
	if (debug)
	{
		Pout << "uncollatedFileOperation::readHeader :"
			<< " fName:" << fName
			<< " typeName:" << typeName << endl;
	}
	if (fName.empty())
	{
		if (IOobject::debug)
		{
			InfoInFunction
				<< "file " << io.objectPath() << " could not be opened"
				<< endl;
		}

		return false;
	}

	autoPtr<ISstream> isPtr(NewIFstream(fName));

	if (!isPtr.valid() || !isPtr->good())
	{
		return false;
	}

	bool ok = io.readHeader(isPtr());

	if (io.headerClassName() == decomposedBlockData::typeName)
	{
		// Read the header inside the container (master data)
		ok = decomposedBlockData::readMasterHeader(io, isPtr());
	}

	if (debug)
	{
		Pout << "uncollatedFileOperation::readHeader :"
			<< " for fName:" << fName
			<< " ok:" << ok
			<< " headerClassName:" << io.headerClassName() << endl;
	}

	return ok;
}


tnbLib::autoPtr<tnbLib::ISstream>
tnbLib::fileOperations::uncollatedFileOperation::readStream
(
	regIOobject& io,
	const fileName& fName,
	const word& typeName,
	const bool read
) const
{
	autoPtr<ISstream> isPtr;

	if (!read)
	{
		isPtr = autoPtr<ISstream>(new dummyISstream());
		return isPtr;
	}

	if (fName.empty())
	{
		FatalErrorInFunction
			<< "cannot find file " << io.objectPath()
			<< exit(FatalError);
	}

	isPtr = NewIFstream(fName);

	if (!isPtr.valid() || !isPtr->good())
	{
		FatalIOError
		(
			"uncollatedFileOperation::readStream()",
			__FILE__,
			__LINE__,
			fName,
			0
		) << "cannot open file"
			<< exit(FatalIOError);
	}
	else if (!io.readHeader(isPtr()))
	{
		FatalIOErrorInFunction(isPtr())
			<< "problem while reading header for object " << io.name()
			<< exit(FatalIOError);
	}

	if (io.headerClassName() != decomposedBlockData::typeName)
	{
		return isPtr;
	}
	else
	{
		// Analyse the objectpath to find out the processor we're trying
		// to access
		label proci = detectProcessorPath(io.objectPath());

		if (proci == -1)
		{
			FatalIOErrorInFunction(isPtr())
				<< "could not detect processor number"
				<< " from objectPath:" << io.objectPath()
				<< " fName:" << fName
				<< exit(FatalIOError);
		}

		// Analyse the fileName for any processor subset. Note: this
		// should really be part of filePath() which should return
		// both file and index in file.
		fileName path, procDir, local;
		label groupStart, groupSize, nProcs;
		splitProcessorPath
		(
			fName,
			path,
			procDir,
			local,
			groupStart,
			groupSize,
			nProcs
		);
		if (groupStart != -1 && groupSize > 0)
		{
			proci = proci - groupStart;
		}

		// Read data and return as stream
		return decomposedBlockData::readBlock(proci, isPtr(), io);
	}
}


bool tnbLib::fileOperations::uncollatedFileOperation::read
(
	regIOobject& io,
	const bool masterOnly,
	const IOstream::streamFormat format,
	const word& typeName
) const
{
	bool ok = true;
	if (Pstream::master() || !masterOnly)
	{
		if (debug)
		{
			Pout << "uncollatedFileOperation::read :"
				<< " Reading object " << io.objectPath()
				<< " from file " << endl;
		}

		// Read file
		ok = io.readData(io.readStream(typeName));
		io.close();

		if (debug)
		{
			Pout << "uncollatedFileOperation::read :"
				<< " Done reading object " << io.objectPath()
				<< " from file " << endl;
		}
	}

	if (masterOnly && Pstream::parRun())
	{
		// Master reads headerclassname from file. Make sure this gets
		// transferred as well as contents.
		Pstream::scatter(io.headerClassName());
		Pstream::scatter(io.note());

		// Get my communication order
		const List<Pstream::commsStruct>& comms =
			(
			(Pstream::nProcs() < Pstream::nProcsSimpleSum)
				? Pstream::linearCommunication()
				: Pstream::treeCommunication()
				);
		const Pstream::commsStruct& myComm = comms[Pstream::myProcNo()];

		// Receive from up
		if (myComm.above() != -1)
		{
			IPstream fromAbove
			(
				Pstream::commsTypes::scheduled,
				myComm.above(),
				0,
				Pstream::msgType(),
				Pstream::worldComm,
				format
			);
			ok = io.readData(fromAbove);
		}

		// Send to my downstairs neighbours
		forAll(myComm.below(), belowI)
		{
			OPstream toBelow
			(
				Pstream::commsTypes::scheduled,
				myComm.below()[belowI],
				0,
				Pstream::msgType(),
				Pstream::worldComm,
				format
			);
			bool okWrite = io.writeData(toBelow);
			ok = ok && okWrite;
		}
	}
	return ok;
}


tnbLib::autoPtr<tnbLib::ISstream>
tnbLib::fileOperations::uncollatedFileOperation::NewIFstream
(
	const fileName& filePath
) const
{
	return autoPtr<ISstream>(new IFstream(filePath));
}


tnbLib::autoPtr<tnbLib::Ostream>
tnbLib::fileOperations::uncollatedFileOperation::NewOFstream
(
	const fileName& pathName,
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp,
	const bool write
) const
{
	return autoPtr<Ostream>(new OFstream(pathName, fmt, ver, cmp));
}


// ************************************************************************* //