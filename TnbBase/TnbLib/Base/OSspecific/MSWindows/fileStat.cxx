#include <fileStat.hxx>

#include <IOstreams.hxx>
#include <timer.hxx>

#include <signal.h>
//#include <unistd.h>
//#include <sys/sysmacros.h>

#include <FixedList.hxx>  // added by amir

#undef major
#undef minor
#undef makedev

# define major(dev) ((int)(((dev) >> 8) & 0xff))
# define minor(dev) ((int)((dev) & 0xff))
# define makedev(major, minor) ((((unsigned int) (major)) << 8) \
    | ((unsigned int) (minor)))

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::label tnbLib::fileStat::nVariants_ = 2;

const char* tnbLib::fileStat::variantExts_[] = { "gz", "orig" };


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileStat::fileStat()
	:
	isValid_(false)
{}

// Construct from components
tnbLib::fileStat::fileStat(const fileName& fName, const unsigned int maxTime)
{
	// Work on volatile
	volatile bool locIsValid = false;

	timer myTimer(maxTime);

	if (!timedOut(myTimer))
	{
		if (::stat(fName.c_str(), &status_) != 0)
		{
			locIsValid = false;
		}
		else
		{
			locIsValid = true;
		}
	}

	// Copy into (non-volatile, possible register based) member var
	isValid_ = locIsValid;
}


//tnbLib::fileStat::fileStat
//(
//	const fileName& fName,
//	const bool checkVariants,
//	const bool followLink,
//	const unsigned int maxTime
//)
//{
//	// Work on volatile
//	volatile bool locIsValid = false;
//
//	timer myTimer(maxTime);
//
//	if (!timedOut(myTimer))
//	{
//		int(*getFileStatus)(const char *, struct stat *) =
//			followLink ? ::stat : ::lstat;
//
//		if (getFileStatus(fName.c_str(), &status_) == 0)
//		{
//			locIsValid = true;
//		}
//		else if (checkVariants)
//		{
//			for (label i = 0; !locIsValid && i < nVariants_; ++i)
//			{
//				const fileName fNameVar = fName + "." + variantExts_[i];
//				if (getFileStatus(fNameVar.c_str(), &status_) == 0)
//				{
//					locIsValid = true;
//				}
//			}
//		}
//	}
//
//	// Copy into (non-volatile, possible register based) member var
//	isValid_ = locIsValid;
//}


tnbLib::fileStat::fileStat(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fileStat::sameDevice(const fileStat& stat2) const
{
	return
		isValid_
		&& (
			major(status_.st_dev) == major(stat2.status().st_dev)
			&& minor(status_.st_dev) == minor(stat2.status().st_dev)
			);
}


bool tnbLib::fileStat::sameINode(const fileStat& stat2) const
{
	return isValid_ && (status_.st_ino == stat2.status().st_ino);
}


bool tnbLib::fileStat::sameINode(const label iNode) const
{
	return isValid_ && (status_.st_ino == ino_t(iNode));
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, fileStat& fStat)
{
	FixedList<label, 13> stat(is);

	fStat.isValid_ = stat[0];

	dev_t st_dev = makedev(stat[1], stat[2]);
	fStat.status_.st_dev = st_dev;

	fStat.status_.st_ino = stat[3];
	fStat.status_.st_mode = stat[4];
	fStat.status_.st_uid = stat[5];
	fStat.status_.st_gid = stat[6];

	dev_t st_rdev = makedev(stat[7], stat[8]);
	fStat.status_.st_rdev = st_rdev;

	fStat.status_.st_size = stat[9];
	fStat.status_.st_atime = stat[10];
	fStat.status_.st_mtime = stat[11];
	fStat.status_.st_ctime = stat[12];

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, fileStat&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const fileStat& fStat)
{
	FixedList<label, 13> stat;

	stat[0] = label(fStat.isValid_);
	stat[1] = label(major(fStat.status_.st_dev));
	stat[2] = label(minor(fStat.status_.st_dev));
	stat[3] = label(fStat.status_.st_ino);
	stat[4] = label(fStat.status_.st_mode);
	stat[5] = label(fStat.status_.st_uid);
	stat[6] = label(fStat.status_.st_gid);
	stat[7] = label(major(fStat.status_.st_rdev));
	stat[8] = label(minor(fStat.status_.st_rdev));
	stat[9] = label(fStat.status_.st_size);
	stat[10] = label(fStat.status_.st_atime);
	stat[11] = label(fStat.status_.st_mtime);
	stat[12] = label(fStat.status_.st_ctime);

	return os << stat;
}


// ************************************************************************* //