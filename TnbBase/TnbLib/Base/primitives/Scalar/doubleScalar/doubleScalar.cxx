#include <doubleScalar.hxx>

#include <token.hxx>
#include <Istream.hxx>  // added by amir
#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<doubleScalar>::typeName = "scalar";
	const doubleScalar pTraits<doubleScalar>::zero = 0.0;
	const doubleScalar pTraits<doubleScalar>::one = 1.0;
	const doubleScalar pTraits<doubleScalar>::min = -doubleScalarVGreat;
	const doubleScalar pTraits<doubleScalar>::max = doubleScalarVGreat;
	const doubleScalar pTraits<doubleScalar>::rootMin = -doubleScalarRootVGreat;
	const doubleScalar pTraits<doubleScalar>::rootMax = doubleScalarRootVGreat;

	const char* const pTraits<doubleScalar>::componentNames[] = { "" };

	pTraits<doubleScalar>::pTraits(const doubleScalar& p)
		:
		p_(p)
	{}


	pTraits<doubleScalar>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	word name(const doubleScalar val)
	{
		std::ostringstream buf;
		buf << val;
		return buf.str();
	}


	// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

	doubleScalar readDoubleScalar(Istream& is)
	{
		doubleScalar rs;
		is >> rs;

		return rs;
	}


	void writeEntry(Ostream& os, const doubleScalar value)
	{
		os << value;
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	Istream& operator>>(Istream& is, doubleScalar& s)
	{
		token t(is);

		if (!t.good())
		{
			is.setBad();
			return is;
		}

		if (t.isNumber())
		{
			s = t.number();
		}
		else
		{
			is.setBad();
			FatalIOErrorInFunction(is)
				<< "wrong token type - expected doubleScalar, found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, doubleScalar&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const doubleScalar s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const doubleScalar&)");
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //