#pragma once
#include <cstring>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::SHA1::SHA1()
{
	clear();
}


inline tnbLib::SHA1::SHA1(const std::string& str)
{
	clear();
	append(str);
}


inline tnbLib::SHA1::SHA1(const char* str)
{
	clear();
	append(str);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::SHA1& tnbLib::SHA1::append(const char* data, size_t len)
{
	processBytes(data, len);
	return *this;
}


inline tnbLib::SHA1& tnbLib::SHA1::append(const std::string& str)
{
	processBytes(str.data(), str.size());
	return *this;
}


inline tnbLib::SHA1& tnbLib::SHA1::append(const char* str)
{
	if (str)
	{
		processBytes(str, strlen(str));
	}
	return *this;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::SHA1::operator==(const SHA1& rhs) const
{
	return this->digest() == rhs.digest();
}


inline bool tnbLib::SHA1::operator==(const SHA1Digest& rhs) const
{
	return this->digest() == rhs;
}


inline bool tnbLib::SHA1::operator==(const std::string& hexdigits) const
{
	return this->digest() == hexdigits;
}


inline bool tnbLib::SHA1::operator==(const char* hexdigits) const
{
	return this->digest() == hexdigits;
}


inline bool tnbLib::SHA1::operator!=(const SHA1& rhs) const
{
	return !this->operator==(rhs);
}


inline bool tnbLib::SHA1::operator!=(const SHA1Digest& rhs) const
{
	return !this->operator==(rhs);
}


inline bool tnbLib::SHA1::operator!=(const std::string& rhs) const
{
	return !this->operator==(rhs);
}


inline bool tnbLib::SHA1::operator!=(const char* rhs) const
{
	return !this->operator==(rhs);
}


inline tnbLib::SHA1::operator tnbLib::SHA1Digest() const
{
	return digest();
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const SHA1& sha)
{
	return os << sha.digest();
}


// ************************************************************************* //