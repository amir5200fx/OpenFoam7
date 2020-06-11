#include <floatScalar.hxx>

#include <token.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	const char* const pTraits<floatScalar>::typeName = "scalar";
	const floatScalar pTraits<floatScalar>::zero = 0.0;
	const floatScalar pTraits<floatScalar>::one = 1.0;
	const floatScalar pTraits<floatScalar>::min = -ScalarVGreat;
	const floatScalar pTraits<floatScalar>::max = ScalarVGreat;
	const floatScalar pTraits<floatScalar>::rootMin = -ScalarRootVGreat;
	const floatScalar pTraits<floatScalar>::rootMax = ScalarRootVGreat;

	const char* const pTraits<floatScalar>::componentNames[] = { "" };

	pTraits<floatScalar>::pTraits(const floatScalar& p)
		:
		p_(p)
	{}


	pTraits<floatScalar>::pTraits(Istream& is)
	{
		is >> p_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	word name(const floatScalar val)
	{
		std::ostringstream buf;
		buf << val;
		return buf.str();
	}


	// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

	floatScalar readFloatScalar(Istream& is)
	{
		floatScalar rs;
		is >> rs;

		return rs;
	}


	void writeEntry(Ostream& os, const floatScalar value)
	{
		os << value;
	}


	// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

	Istream& operator>>(Istream& is, floatScalar& s)
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
				<< "wrong token type - expected floatScalar, found " << t.info()
				<< exit(FatalIOError);

			return is;
		}

		// Check state of Istream
		is.check("Istream& operator>>(Istream&, floatScalar&)");

		return is;
	}


	Ostream& operator<<(Ostream& os, const floatScalar s)
	{
		os.write(s);
		os.check("Ostream& operator<<(Ostream&, const floatScalar&)");
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //