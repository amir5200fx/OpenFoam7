#include <masterOFstream.hxx>

#include <OFstream.hxx>
#include <OSspecific.hxx>
#include <PstreamBuffers.hxx>
#include <masterUncollatedFileOperation.hxx>
#include <boolList.hxx>

//- added by amir!
#include <Pstream.hxx>
#include <UIPstream.hxx>
#include <UOPstream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::masterOFstream::checkWrite
(
	const fileName& fName,
	const string& str
)
{
	mkDir(fName.path());

	OFstream os
	(
		fName,
		IOstream::BINARY,
		version(),
		compression_,
		append_
	);

	if (!os.good())
	{
		FatalIOErrorInFunction(os)
			<< "Could not open file " << fName
			<< exit(FatalIOError);
	}

	os.writeQuoted(str, false);
	if (!os.good())
	{
		FatalIOErrorInFunction(os)
			<< "Failed writing to " << fName
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::masterOFstream::masterOFstream
(
	const fileName& pathName,
	streamFormat format,
	versionNumber version,
	compressionType compression,
	const bool append,
	const bool write
)
	:
	OStringStream(format, version),
	pathName_(pathName),
	compression_(compression),
	append_(append),
	write_(write)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::masterOFstream::~masterOFstream()
{
	if (Pstream::parRun())
	{
		List<fileName> filePaths(Pstream::nProcs());
		filePaths[Pstream::myProcNo()] = pathName_;
		Pstream::gatherList(filePaths);

		bool uniform =
			fileOperations::masterUncollatedFileOperation::uniformFile
			(
				filePaths
			);

		Pstream::scatter(uniform);

		if (uniform)
		{
			if (Pstream::master() && write_)
			{
				checkWrite(pathName_, str());
			}
			return;
		}
		boolList write(Pstream::nProcs());
		write[Pstream::myProcNo()] = write_;
		Pstream::gatherList(write);


		// Different files
		PstreamBuffers pBufs(Pstream::commsTypes::nonBlocking);

		// Send my buffer to master
		if (!Pstream::master())
		{
			UOPstream os(Pstream::masterNo(), pBufs);
			string s(this->str());
			os.write(&s[0], s.size());
		}

		labelList recvSizes;
		pBufs.finishedSends(recvSizes);

		if (Pstream::master())
		{
			// Write my own data
			{
				if (write[Pstream::myProcNo()])
				{
					checkWrite(filePaths[Pstream::myProcNo()], str());
				}
			}

			for (label proci = 1; proci < Pstream::nProcs(); proci++)
			{
				UIPstream is(proci, pBufs);
				List<char> buf(recvSizes[proci]);

				is.read(buf.begin(), buf.size());

				if (write[proci])
				{
					checkWrite
					(
						filePaths[proci],
						string(buf.begin(), buf.size())
					);
				}
			}
		}
	}
	else
	{
		checkWrite(pathName_, str());
	}
}


// ************************************************************************* //