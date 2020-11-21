#include <memInfo.hxx>

#include <token.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::memInfo::memInfo()
	:
	peak_(-1),
	size_(-1),
	rss_(-1)
{
	update();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::memInfo::~memInfo()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::memInfo& tnbLib::memInfo::update()
{
	// reset to invalid values first
	peak_ = size_ = rss_ = -1;
	IFstream is("/proc/" + name(pid()) + "/status");

	while (is.good())
	{
		string line;
		is.getLine(line);
		char tag[32];
		int value;

		if (sscanf(line.c_str(), "%30s %d", tag, &value) == 2)
		{
			if (!strcmp(tag, "VmPeak:"))
			{
				peak_ = value;
			}
			else if (!strcmp(tag, "VmSize:"))
			{
				size_ = value;
			}
			else if (!strcmp(tag, "VmRSS:"))
			{
				rss_ = value;
			}
		}
	}

	return *this;
}


bool tnbLib::memInfo::valid() const
{
	return peak_ != -1;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, memInfo& m)
{
	is.readBegin("memInfo");

	is >> m.peak_ >> m.size_ >> m.rss_;

	is.readEnd("memInfo");

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream&, tnbLib::memInfo&)"
	);

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const memInfo& m)
{
	os << token::BEGIN_LIST
		<< m.peak_ << token::SPACE << m.size_ << token::SPACE << m.rss_
		<< token::END_LIST;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::memInfo&)"
	);

	return os;
}


// ************************************************************************* //