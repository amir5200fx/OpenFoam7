#include <fileName.hxx>

#include <wordList.hxx>
#include <DynamicList.hxx>
#include <OSspecific.hxx>

#include <tnbDebug.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::fileName::typeName = "fileName";
int tnbLib::fileName::debug(debug::debugSwitch(fileName::typeName, 0));
const tnbLib::fileName tnbLib::fileName::null;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fileName::fileName(const wordList& lst)
{
	forAll(lst, elemI)
	{
		operator=((*this) / lst[elemI]);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::fileType tnbLib::fileName::type
(
	const bool checkVariants,
	const bool followLink
) const
{
	return ::tnbLib::type(*this, checkVariants, followLink);
}


bool tnbLib::fileName::isAbsolute() const
{
	return !empty() && operator[](0) == '/';
}


tnbLib::fileName& tnbLib::fileName::toAbsolute()
{
	fileName& f = *this;

	if (!f.isAbsolute())
	{
		f = cwd() / f;
		f.clean();
	}

	return f;
}


bool tnbLib::fileName::clean()
{
	// The top slash - we are never allowed to go above it
	string::size_type top = this->find('/');

	// No slashes - nothing to do
	if (top == string::npos)
	{
		return false;
	}

	// Start with the '/' found:
	char prev = '/';
	string::size_type nChar = top + 1;
	string::size_type maxLen = this->size();

	for
		(
			string::size_type src = nChar;
			src < maxLen;
			)
	{
		char c = operator[](src++);

		if (prev == '/')
		{
			// Repeated '/' - skip it
			if (c == '/')
			{
				continue;
			}

			// Could be '/./' or '/../'
			if (c == '.')
			{
				// Found trailing '/.' - skip it
				if (src >= maxLen)
				{
					continue;
				}


				// Peek at the next character
				char c1 = operator[](src);

				// Found '/./' - skip it
				if (c1 == '/')
				{
					src++;
					continue;
				}

				// It is '/..' or '/../'
				if (c1 == '.' && (src + 1 >= maxLen || operator[](src + 1) == '/'))
				{
					string::size_type parent;

					// Backtrack to find the parent directory
					// Minimum of 3 characters:  '/x/../'
					// Strip it, provided it is above the top point
					if
						(
							nChar > 2
							&& (parent = this->rfind('/', nChar - 2)) != string::npos
							&& parent >= top
							)
					{
						nChar = parent + 1;   // Retain '/' from the parent
						src += 2;
						continue;
					}

					// Bad resolution, eg 'abc/../../'
					// Retain the sequence, but move the top to avoid it being
					// considered a valid parent later
					top = nChar + 2;
				}
			}
		}
		operator[](nChar++) = prev = c;
	}

	// Remove trailing slash
	if (nChar > 1 && operator[](nChar - 1) == '/')
	{
		nChar--;
	}

	this->resize(nChar);

	return (nChar != maxLen);
}


tnbLib::fileName tnbLib::fileName::clean() const
{
	fileName fName(*this);
	fName.clean();
	return fName;
}


tnbLib::word tnbLib::fileName::name() const
{
	size_type i = rfind('/');

	if (i == npos)
	{
		return *this;
	}
	else
	{
		return substr(i + 1, npos);
	}
}


tnbLib::string tnbLib::fileName::caseName() const
{
	string cName = *this;

	const string caseStr(getEnv("FOAM_CASE"));

	const size_type i = find(caseStr);

	if (i == npos)
	{
		return cName;
	}
	else
	{
		return cName.replace(i, caseStr.size(), string("$FOAM_CASE"));
	}
}


tnbLib::word tnbLib::fileName::name(const bool noExt) const
{
	if (noExt)
	{
		size_type beg = rfind('/');
		if (beg == npos)
		{
			beg = 0;
		}
		else
		{
			++beg;
		}

		size_type dot = rfind('.');
		if (dot != npos && dot <= beg)
		{
			dot = npos;
		}

		if (dot == npos)
		{
			return substr(beg, npos);
		}
		else
		{
			return substr(beg, dot - beg);
		}
	}
	else
	{
		return this->name();
	}
}


tnbLib::fileName tnbLib::fileName::path() const
{
	size_type i = rfind('/');

	if (i == npos)
	{
		return ".";
	}
	else if (i)
	{
		return substr(0, i);
	}
	else
	{
		return "/";
	}
}


tnbLib::fileName tnbLib::fileName::lessExt() const
{
	size_type i = find_last_of("./");

	if (i == npos || i == 0 || operator[](i) == '/')
	{
		return *this;
	}
	else
	{
		return substr(0, i);
	}
}


tnbLib::word tnbLib::fileName::ext() const
{
	size_type i = find_last_of("./");

	if (i == npos || i == 0 || operator[](i) == '/')
	{
		return word::null;
	}
	else
	{
		return substr(i + 1, npos);
	}
}


tnbLib::wordList tnbLib::fileName::components(const char delimiter) const
{
	DynamicList<word> wrdList(20);

	size_type beg = 0, end = 0;

	while ((end = find(delimiter, beg)) != npos)
	{
		// Avoid empty element (caused by doubled slashes)
		if (beg < end)
		{
			wrdList.append(substr(beg, end - beg));
		}
		beg = end + 1;
	}

	// Avoid empty trailing element
	if (beg < size())
	{
		wrdList.append(substr(beg, npos));
	}

	// Transfer to wordList
	return wordList(move(wrdList));
}


tnbLib::word tnbLib::fileName::component
(
	const size_type cmpt,
	const char delimiter
) const
{
	return components(delimiter)[cmpt];
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::fileName::operator=(const fileName& str)
{
	string::operator=(str);
}


void tnbLib::fileName::operator=(fileName&& str)
{
	string::operator=(move(str));
}


void tnbLib::fileName::operator=(const word& str)
{
	string::operator=(str);
}


void tnbLib::fileName::operator=(const string& str)
{
	string::operator=(str);
	stripInvalid();
}


void tnbLib::fileName::operator=(const std::string& str)
{
	string::operator=(str);
	stripInvalid();
}


void tnbLib::fileName::operator=(const char* str)
{
	string::operator=(str);
	stripInvalid();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::fileName tnbLib::operator/(const string& a, const string& b)
{
	if (a.size())           // First string non-null
	{
		if (b.size())       // Second string non-null
		{
			return fileName(a + '/' + b);
		}
		else                // Second string null
		{
			return a;
		}
	}
	else                    // First string null
	{
		if (b.size())       // Second string non-null
		{
			return b;
		}
		else                // Second string null
		{
			return fileName();
		}
	}
}


// ************************************************************************* //