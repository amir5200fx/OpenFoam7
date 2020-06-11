#include <tnbString.hxx>

#include <stringOps.hxx>
#include <tnbDebug.hxx> // added by amir

/* * * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * */

const char* const tnbLib::string::typeName = "string";
int tnbLib::string::debug(tnbLib::debug::debugSwitch(string::typeName, 0));
const tnbLib::string tnbLib::string::null;


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::string::size_type tnbLib::string::count(const char c) const
{
	size_type cCount = 0;

	for (const_iterator iter = begin(); iter != end(); ++iter)
	{
		if (*iter == c)
		{
			++cCount;
		}
	}

	return cCount;
}


tnbLib::string& tnbLib::string::replace
(
	const string& oldStr,
	const string& newStr,
	size_type start
)
{
	size_type newStart = start;

	if ((newStart = find(oldStr, newStart)) != npos)
	{
		std::string::replace(newStart, oldStr.size(), newStr);
	}

	return *this;
}


tnbLib::string& tnbLib::string::replaceAll
(
	const string& oldStr,
	const string& newStr,
	size_type start
)
{
	if (oldStr.size())
	{
		size_type newStart = start;

		while ((newStart = find(oldStr, newStart)) != npos)
		{
			std::string::replace(newStart, oldStr.size(), newStr);
			newStart += newStr.size();
		}
	}

	return *this;
}


tnbLib::string& tnbLib::string::expand(const bool allowEmpty)
{
	stringOps::inplaceExpand(*this, allowEmpty);
	return *this;
}


bool tnbLib::string::removeRepeated(const char character)
{
	bool changed = false;

	if (character && find(character) != npos)
	{
		string::size_type nChar = 0;
		iterator iter2 = begin();

		char prev = 0;

		for
			(
				string::const_iterator iter1 = iter2;
				iter1 != end();
				iter1++
				)
		{
			char c = *iter1;

			if (prev == c && c == character)
			{
				changed = true;
			}
			else
			{
				*iter2 = prev = c;
				++iter2;
				++nChar;
			}
		}
		resize(nChar);
	}

	return changed;
}


tnbLib::string tnbLib::string::removeRepeated(const char character) const
{
	string str(*this);
	str.removeRepeated(character);
	return str;
}


bool tnbLib::string::removeTrailing(const char character)
{
	bool changed = false;

	string::size_type nChar = size();
	if (character && nChar > 1 && operator[](nChar - 1) == character)
	{
		resize(nChar - 1);
		changed = true;
	}

	return changed;
}


tnbLib::string tnbLib::string::removeTrailing(const char character) const
{
	string str(*this);
	str.removeTrailing(character);
	return str;
}


// ************************************************************************* //