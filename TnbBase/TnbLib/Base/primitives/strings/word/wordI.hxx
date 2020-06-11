#pragma once
#include <cctype>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::word::stripInvalid()
{
	// skip stripping unless debug is active to avoid
	// costly operations
	if (debug && string::stripInvalid<word>(*this))
	{
		std::cerr
			<< "word::stripInvalid() called for word "
			<< this->c_str() << std::endl;

		if (debug > 1)
		{
			std::cerr
				<< "    For debug level (= " << debug
				<< ") > 1 this is considered fatal" << std::endl;
			std::abort();
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::word::word(const word& w)
	:
	string(w)
{}


inline tnbLib::word::word()
	:
	string()
{}


inline tnbLib::word::word(const string& s, const bool doStripInvalid)
	:
	string(s)
{
	if (doStripInvalid)
	{
		stripInvalid();
	}
}


inline tnbLib::word::word(const std::string& s, const bool doStripInvalid)
	:
	string(s)
{
	if (doStripInvalid)
	{
		stripInvalid();
	}
}


inline tnbLib::word::word(const char* s, const bool doStripInvalid)
	:
	string(s)
{
	if (doStripInvalid)
	{
		stripInvalid();
	}
}

inline tnbLib::word::word
(
	const char* s,
	const size_type n,
	const bool doStripInvalid
)
	:
	string(s, n)
{
	if (doStripInvalid)
	{
		stripInvalid();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::word::valid(char c)
{
	return
		(
			!isspace(c)
			&& c != '"'   // string quote
			&& c != '\''  // string quote
			&& c != '/'   // path separator
			&& c != ';'   // end statement
			&& c != '{'   // beg subdict
			&& c != '}'   // end subdict
			);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::word::operator=(const word& q)
{
	string::operator=(q);
}


inline void tnbLib::word::operator=(const string& q)
{
	string::operator=(q);
	stripInvalid();
}


inline void tnbLib::word::operator=(const std::string& q)
{
	string::operator=(q);
	stripInvalid();
}


inline void tnbLib::word::operator=(const char* q)
{
	string::operator=(q);
	stripInvalid();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

inline tnbLib::word tnbLib::operator&(const word& a, const word& b)
{
	if (b.size())
	{
		string ub = b;
		ub.string::operator[](0) = char(toupper(ub.string::operator[](0)));

		return a + ub;
	}
	else
	{
		return a;
	}
}


// ************************************************************************* //