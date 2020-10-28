#include <error.hxx>

#include <OStringStream.hxx>
#include <fileName.hxx>
#include <dictionary.hxx>
#include <jobInfo.hxx>
#include <Pstream.hxx>

#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::IOerror::IOerror(const string& title)
	:
	error(title),
	ioFileName_("unknown"),
	ioStartLineNumber_(-1),
	ioEndLineNumber_(-1)
{}


tnbLib::IOerror::IOerror(const dictionary& errDict)
	:
	error(errDict),
	ioFileName_(errDict.lookup("ioFileName")),
	ioStartLineNumber_(readLabel(errDict.lookup("ioStartLineNumber"))),
	ioEndLineNumber_(readLabel(errDict.lookup("ioEndLineNumber")))
{}


tnbLib::IOerror::~IOerror() throw()
{}


tnbLib::OSstream& tnbLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const string& ioFileName,
	const label ioStartLineNumber,
	const label ioEndLineNumber
	)
{
	error::operator()(functionName, sourceFileName, sourceFileLineNumber);
	ioFileName_ = ioFileName;
	ioStartLineNumber_ = ioStartLineNumber;
	ioEndLineNumber_ = ioEndLineNumber;

	return operator OSstream&();
}


tnbLib::OSstream& tnbLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const IOstream& ioStream
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			ioStream.name(),
			ioStream.lineNumber(),
			-1
			);
}


tnbLib::OSstream& tnbLib::IOerror::operator()
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const dictionary& dict
	)
{
	return operator()
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			dict.name(),
			dict.startLineNumber(),
			dict.endLineNumber()
			);
}


void tnbLib::IOerror::SafeFatalIOError
(
	const char* functionName,
	const char* sourceFileName,
	const int sourceFileLineNumber,
	const IOstream& ioStream,
	const string& msg
)
{
	if (jobInfo::constructed)
	{
		FatalIOError
		(
			functionName,
			sourceFileName,
			sourceFileLineNumber,
			ioStream
		) << msg << tnbLib::exit(FatalIOError);
	}
	else
	{
		std::cerr
			<< std::endl
			<< "--> FOAM FATAL IO ERROR:" << std::endl
			<< msg
			<< std::endl
			<< "file: " << ioStream.name()
			<< " at line " << ioStream.lineNumber() << '.'
			<< std::endl << std::endl
			<< "    From function " << functionName
			<< std::endl
			<< "    in file " << sourceFileName
			<< " at line " << sourceFileLineNumber << '.'
			<< std::endl;
		::exit(1);
	}
}


tnbLib::IOerror::operator tnbLib::dictionary() const
{
	dictionary errDict(error::operator dictionary());

	errDict.remove("type");
	errDict.add("type", word("tnbLib::IOerror"));

	errDict.add("ioFileName", ioFileName());
	errDict.add("ioStartLineNumber", ioStartLineNumber());
	errDict.add("ioEndLineNumber", ioEndLineNumber());

	return errDict;
}


void tnbLib::IOerror::exit(const int)
{
	if (!throwExceptions_ && jobInfo::constructed)
	{
		jobInfo_.add("FatalIOError", operator dictionary());
		jobInfo_.exit();
	}

	if (abort_)
	{
		abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nFOAM parallel run exiting\n" << endl;
		Pstream::exit(1);
	}
	else
	{
		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			IOerror errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nFOAM exiting\n" << endl;
			::exit(1);
		}
	}
}


void tnbLib::IOerror::abort()
{
	if (!throwExceptions_ && jobInfo::constructed)
	{
		jobInfo_.add("FatalIOError", operator dictionary());
		jobInfo_.abort();
	}

	if (abort_)
	{
		Perr << endl << *this << endl
			<< "\nFOAM aborting (FOAM_ABORT set)\n" << endl;
		printStack(Perr);
		::abort();
	}

	if (Pstream::parRun())
	{
		Perr << endl << *this << endl
			<< "\nFOAM parallel run aborting\n" << endl;
		printStack(Perr);
		Pstream::abort();
	}
	else
	{
		if (throwExceptions_)
		{
			// Make a copy of the error to throw
			IOerror errorException(*this);

			// Rewind the message buffer for the next error message
			messageStreamPtr_->rewind();

			throw errorException;
		}
		else
		{
			Perr << endl << *this << endl
				<< "\nFOAM aborting\n" << endl;
			printStack(Perr);
			::abort();
		}
	}
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const IOerror& ioErr)
{
	if (!os.bad())
	{
		os << endl
			<< ioErr.title().c_str() << endl
			<< ioErr.message().c_str() << endl << endl;

		os << "file: " << ioErr.ioFileName().c_str();

		if (ioErr.ioStartLineNumber() >= 0 && ioErr.ioEndLineNumber() >= 0)
		{
			os << " from line " << ioErr.ioStartLineNumber()
				<< " to line " << ioErr.ioEndLineNumber() << '.';
		}
		else if (ioErr.ioStartLineNumber() >= 0)
		{
			os << " at line " << ioErr.ioStartLineNumber() << '.';
		}

		if (IOerror::level >= 2 && ioErr.sourceFileLineNumber())
		{
			os << endl << endl
				<< "    From function " << ioErr.functionName().c_str() << endl
				<< "    in file " << ioErr.sourceFileName().c_str()
				<< " at line " << ioErr.sourceFileLineNumber() << '.';
		}
	}

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// Global error definitions

tnbLib::IOerror tnbLib::FatalIOError("--> FOAM FATAL IO ERROR: ");

// ************************************************************************* //