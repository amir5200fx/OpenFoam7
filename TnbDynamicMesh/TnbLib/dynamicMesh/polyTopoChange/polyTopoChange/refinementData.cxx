#include <refinementData.hxx>

#include <token.hxx>  // added by amir
#include <Istream.hxx>  // added by amir

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::refinementData& wDist
	)
{
	if (os.format() == IOstream::ASCII)
	{
		os << wDist.refinementCount_ << token::SPACE << wDist.count_;
	}
	else
	{
		os.write
		(
			reinterpret_cast<const char*>(&wDist.refinementCount_),
			sizeof(refinementData)
		);
	}

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const refinementData&)");
	return os;
}


tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, tnbLib::refinementData& wDist)
{
	if (is.format() == IOstream::ASCII)
	{
		is >> wDist.refinementCount_ >> wDist.count_;
	}
	else
	{
		is.read
		(
			reinterpret_cast<char*>(&wDist.refinementCount_),
			sizeof(refinementData)
		);
	}

	// Check state of Istream
	is.check("Istream& operator>>(Istream&, refinementData&)");
	return is;
}


// ************************************************************************* //