#include <jobInfo.hxx>

#include <OSspecific.hxx>
#include <clock.hxx>
#include <OFstream.hxx>
#include <Pstream.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

bool tnbLib::jobInfo::writeJobControl
(
	tnbLib::debug::infoSwitch("writeJobControl", 0)
);

bool tnbLib::jobInfo::writeJobInfo
(
	tnbLib::debug::infoSwitch("writeJobInfo", 0)
);

tnbLib::jobInfo tnbLib::jobInfo_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::jobInfo::jobInfo()
	:
	runningJobPath_(),
	finishedJobPath_(),
	cpuTime_()
{
	//name() = "jobInfo";

	//if (Pstream::master())
	//{

	//	cout << "writeJobControl = " << writeJobControl << std::endl;
	//	system("pause");
	//	//if (writeJobControl)
	//		if (1)
	//	{
	//		string baseDir = getEnv("FOAM_JOB_DIR");
	//		string jobFile = hostName() + '.' + tnbLib::name(pid());
	//		cout << "base dir = " << baseDir << std::endl;
	//		cout << "job file= " << jobFile << std::endl;
	//		system("pause");
	//		fileName runningDir(baseDir / "runningJobs");
	//		fileName finishedDir(baseDir / "finishedJobs");

	//		runningJobPath_ = runningDir / jobFile;
	//		finishedJobPath_ = finishedDir / jobFile;
	//		cout << "job path = " << runningJobPath_ << std::endl;
	//		if (baseDir.empty())
	//		{
	//			FatalErrorInFunction
	//				<< "Cannot get jobInfo directory $FOAM_JOB_DIR"
	//				<< tnbLib::exit(FatalError);
	//		}

	//		if (!isDir(runningDir) && !mkDir(runningDir))
	//		{
	//			FatalErrorInFunction
	//				<< "Cannot make jobInfo directory " << runningDir
	//				<< tnbLib::exit(FatalError);
	//		}

	//		if (!isDir(finishedDir) && !mkDir(finishedDir))
	//		{
	//			FatalErrorInFunction
	//				<< "Cannot make jobInfo directory " << finishedDir
	//				<< tnbLib::exit(FatalError);
	//		}

	//		writeJobInfo = true;
	//	}
	//}

	//constructed = true;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::jobInfo::~jobInfo()
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::jobInfo::write(Ostream& os) const
{
	if (writeJobInfo && Pstream::master())
	{
		if (os.good())
		{
			dictionary::write(os, false);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}


void tnbLib::jobInfo::write
(
	const word& executable,
	const fileName& casePath
) const
{
	if (writeJobInfo && Pstream::master())
	{
		if (!writeJobControl)
		{
			const fileName jobInfoPath(casePath / "jobInfo");

			if (!isDir(jobInfoPath) && !mkDir(jobInfoPath))
			{
				FatalErrorInFunction
					<< "Cannot make jobInfo directory " << jobInfoPath
					<< tnbLib::exit(FatalError);
			}

			const word jobFile = executable + '.' + tnbLib::name(pid());

			runningJobPath_ = jobInfoPath / jobFile;
			finishedJobPath_ = jobInfoPath / jobFile;
		}

		if (!write(OFstream(runningJobPath_)()))
		{
			FatalErrorInFunction
				<< "Failed to write to jobInfo file "
				<< runningJobPath_
				<< tnbLib::exit(FatalError);
		}
	}
}


void tnbLib::jobInfo::end(const word& terminationType)
{
	if (writeJobInfo && constructed && Pstream::master())
	{
		add("cpuTime", cpuTime_.elapsedCpuTime());
		add("endDate", clock::date());
		add("endTime", clock::clockTime());

		if (!found("termination"))
		{
			add("termination", terminationType);
		}

		rm(runningJobPath_);
		write(OFstream(finishedJobPath_)());
	}

	constructed = false;
}


void tnbLib::jobInfo::end()
{
	end("normal");
}


void tnbLib::jobInfo::exit()
{
	end("exit");
}


void tnbLib::jobInfo::abort()
{
	end("abort");
}


void tnbLib::jobInfo::signalEnd() const
{
	if (writeJobControl && constructed && Pstream::master())
	{
		mv(runningJobPath_, finishedJobPath_);
	}

	constructed = false;
}

void tnbLib::jobInfo::perform()
{
	name() = "jobInfo";

	if (Pstream::master())
	{
		if (writeJobControl)
		{
			string baseDir = getEnv("FOAM_JOB_DIR");
			string jobFile = hostName() + '.' + tnbLib::name(pid());

			fileName runningDir(baseDir / "runningJobs");
			fileName finishedDir(baseDir / "finishedJobs");

			runningJobPath_ = runningDir / jobFile;
			finishedJobPath_ = finishedDir / jobFile;

			if (baseDir.empty())
			{
				FatalErrorInFunction
					<< "Cannot get jobInfo directory $FOAM_JOB_DIR"
					<< tnbLib::exit(FatalError);
			}

			if (!isDir(runningDir) && !mkDir(runningDir))
			{
				FatalErrorInFunction
					<< "Cannot make jobInfo directory " << runningDir
					<< tnbLib::exit(FatalError);
			}

			if (!isDir(finishedDir) && !mkDir(finishedDir))
			{
				FatalErrorInFunction
					<< "Cannot make jobInfo directory " << finishedDir
					<< tnbLib::exit(FatalError);
			}

			writeJobInfo = true;
		}
	}

	constructed = true;
}


// ************************************************************************* //