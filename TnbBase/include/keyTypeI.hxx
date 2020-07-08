#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::keyType::keyType()
	:
	word(),
	isPattern_(false)
{}


inline tnbLib::keyType::keyType(const keyType& s)
	:
	word(s, false),
	isPattern_(s.isPattern())
{}


inline tnbLib::keyType::keyType(const word& s)
	:
	word(s, false),
	isPattern_(false)
{}


inline tnbLib::keyType::keyType(const string& s)
	:
	word(s, false),
	isPattern_(true)
{}


inline tnbLib::keyType::keyType(const char* s)
	:
	word(s, false),
	isPattern_(false)
{}


inline tnbLib::keyType::keyType
(
	const std::string& s,
	const bool isPattern
)
	:
	word(s, false),
	isPattern_(isPattern)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::keyType::isPattern() const
{
	return isPattern_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::keyType::operator=(const keyType& s)
{
	// Bypass checking
	string::operator=(s);
	isPattern_ = s.isPattern_;
}


inline void tnbLib::keyType::operator=(const word& s)
{
	word::operator=(s);
	isPattern_ = false;
}


inline void tnbLib::keyType::operator=(const string& s)
{
	// Bypass checking
	string::operator=(s);
	isPattern_ = true;
}


inline void tnbLib::keyType::operator=(const char* s)
{
	// Bypass checking
	string::operator=(s);
	isPattern_ = false;
}


// ************************************************************************* //