#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::fileName::stripInvalid()
{
	if (debug && string::stripInvalid<fileName>(*this))
	{
		std::cerr
			<< "fileName::stripInvalid() called for invalid fileName "
			<< this->c_str() << std::endl;

		if (debug > 1)
		{
			std::cerr
				<< "    For debug level (= " << debug
				<< ") > 1 this is considered fatal" << std::endl;
			std::abort();
		}

		removeRepeated('/');
		removeTrailing('/');
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::fileName::fileName()
	:
	string()
{}


inline tnbLib::fileName::fileName(const fileName& fn)
	:
	string(fn)
{}


inline tnbLib::fileName::fileName(fileName&& fn)
	:
	string(move(fn))
{}


inline tnbLib::fileName::fileName(const word& w)
	:
	string(w)
{}


inline tnbLib::fileName::fileName(const string& str)
	:
	string(str)
{
	stripInvalid();
}


inline tnbLib::fileName::fileName(const std::string& str)
	:
	string(str)
{
	stripInvalid();
}


inline tnbLib::fileName::fileName(const char* str)
	:
	string(str)
{
	stripInvalid();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::fileName::valid(char c)
{
	return
		(
			!isspace(c)
			&& c != '"'   // string quote
			&& c != '\''  // string quote
			);
}


// ************************************************************************* //