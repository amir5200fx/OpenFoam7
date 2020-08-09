#include <codedBase.hxx>

#include <SHA1Digest.hxx>
#include <dynamicCode.hxx>
#include <dynamicCodeContext.hxx>
#include <dlLibraryTable.hxx>
#include <PstreamReduceOps.hxx>
#include <OSspecific.hxx>
#include <regIOobject.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(codedBase, 0);
}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

void* tnbLib::codedBase::loadLibrary
(
	const fileName& libPath,
	const string& globalFuncName,
	const dictionary& contextDict
) const
{
	void* lib = 0;

	// avoid compilation by loading an existing library
	if (!libPath.empty())
	{
		if (libs().open(libPath, false))
		{
			lib = libs().findLibrary(libPath);

			// verify the loaded version and unload if needed
			if (lib)
			{
				// provision for manual execution of code after loading
				if (dlSymFound(lib, globalFuncName))
				{
					loaderFunctionType function =
						reinterpret_cast<loaderFunctionType>
						(
							dlSym(lib, globalFuncName)
							);

					if (function)
					{
						(*function)(true);    // force load
					}
					else
					{
						FatalIOErrorInFunction
						(
							contextDict
						) << "Failed looking up symbol " << globalFuncName
							<< nl << "from " << libPath << exit(FatalIOError);
					}
				}
				else
				{
					FatalIOErrorInFunction
					(
						contextDict
					) << "Failed looking up symbol " << globalFuncName << nl
						<< "from " << libPath << exit(FatalIOError);

					lib = 0;
					if (!libs().close(libPath, false))
					{
						FatalIOErrorInFunction
						(
							contextDict
						) << "Failed unloading library "
							<< libPath
							<< exit(FatalIOError);
					}
				}
			}
		}
	}

	return lib;
}


void tnbLib::codedBase::unloadLibrary
(
	const fileName& libPath,
	const string& globalFuncName,
	const dictionary& contextDict
) const
{
	void* lib = 0;

	if (libPath.empty())
	{
		return;
	}

	lib = libs().findLibrary(libPath);

	if (!lib)
	{
		return;
	}

	// provision for manual execution of code before unloading
	if (dlSymFound(lib, globalFuncName))
	{
		loaderFunctionType function =
			reinterpret_cast<loaderFunctionType>
			(
				dlSym(lib, globalFuncName)
				);

		if (function)
		{
			(*function)(false);    // force unload
		}
		else
		{
			FatalIOErrorInFunction
			(
				contextDict
			) << "Failed looking up symbol " << globalFuncName << nl
				<< "from " << libPath << exit(FatalIOError);
		}
	}

	if (!libs().close(libPath, false))
	{
		FatalIOErrorInFunction
		(
			contextDict
		) << "Failed unloading library " << libPath
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::codedBase::createLibrary
(
	dynamicCode& dynCode,
	const dynamicCodeContext& context
) const
{
	bool create =
		Pstream::master()
		|| (regIOobject::fileModificationSkew <= 0);   // not NFS

	if (create)
	{
		// Write files for new library
		if (!dynCode.upToDate(context))
		{
			// filter with this context
			dynCode.reset(context);

			this->prepare(dynCode, context);

			if (!dynCode.copyOrCreateFiles(true))
			{
				FatalIOErrorInFunction
				(
					context.dict()
				) << "Failed writing files for" << nl
					<< dynCode.libRelPath() << nl
					<< exit(FatalIOError);
			}
		}

		if (!dynCode.wmakeLibso())
		{
			FatalIOErrorInFunction
			(
				context.dict()
			) << "Failed wmake " << dynCode.libRelPath() << nl
				<< exit(FatalIOError);
		}
	}


	// all processes must wait for compile to finish
	if (regIOobject::fileModificationSkew > 0)
	{
		//- Since the library has only been compiled on the master the
		//  other nodes need to pick this library up through NFS
		//  We do this by just polling a few times using the
		//  fileModificationSkew.

		const fileName libPath = dynCode.libPath();

		off_t mySize = tnbLib::fileSize(libPath);
		off_t masterSize = mySize;
		Pstream::scatter(masterSize);

		if (debug)
		{
			Pout << endl << "on processor " << Pstream::myProcNo()
				<< " have masterSize:" << masterSize
				<< " and localSize:" << mySize
				<< endl;
		}


		if (mySize < masterSize)
		{
			if (debug)
			{
				Pout << "Local file " << libPath
					<< " not of same size (" << mySize
					<< ") as master ("
					<< masterSize << "). Waiting for "
					<< regIOobject::fileModificationSkew
					<< " seconds." << endl;
			}
			tnbLib::sleep(regIOobject::fileModificationSkew);

			// Recheck local size
			mySize = tnbLib::fileSize(libPath);

			if (mySize < masterSize)
			{
				FatalIOErrorInFunction
				(
					context.dict()
				) << "Cannot read (NFS mounted) library " << nl
					<< libPath << nl
					<< "on processor " << Pstream::myProcNo()
					<< " detected size " << mySize
					<< " whereas master size is " << masterSize
					<< " bytes." << nl
					<< "If your case is not NFS mounted"
					<< " (so distributed) set fileModificationSkew"
					<< " to 0"
					<< exit(FatalIOError);
			}
		}

		if (debug)
		{
			Pout << endl << "on processor " << Pstream::myProcNo()
				<< " after waiting: have masterSize:" << masterSize
				<< " and localSize:" << mySize
				<< endl;
		}
	}
	reduce(create, orOp<bool>());
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::codedBase::updateLibrary
(
	const word& name
) const
{
	const dictionary& dict = this->codeDict();

	dynamicCode::checkSecurity
	(
		"codedBase::updateLibrary()",
		dict
	);

	dynamicCodeContext context(dict, codeKeys());

	// codeName: name + _<sha1>
	// codeDir : name
	dynamicCode dynCode
	(
		name + context.sha1().str(true),
		name
	);
	const fileName libPath = dynCode.libPath();


	// the correct library was already loaded => we are done
	if (libs().findLibrary(libPath))
	{
		return;
	}

	Info << "Using dynamicCode for " << this->description().c_str()
		<< " at line " << dict.startLineNumber()
		<< " in " << dict.name() << endl;


	// remove instantiation of fvPatchField provided by library
	this->clearRedirect();

	// may need to unload old library
	unloadLibrary
	(
		oldLibPath_,
		dynamicCode::libraryBaseName(oldLibPath_),
		context.dict()
	);

	// try loading an existing library (avoid compilation when possible)
	if (!loadLibrary(libPath, dynCode.codeName(), context.dict()))
	{
		createLibrary(dynCode, context);

		if (!loadLibrary(libPath, dynCode.codeName(), context.dict()))
		{
			FatalIOErrorInFunction(context.dict())
				<< "Failed to load " << libPath << exit(FatalIOError);
		}
	}

	// retain for future reference
	oldLibPath_ = libPath;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::codedBase::codedBase()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::codedBase::~codedBase()
{}


// ************************************************************************* //