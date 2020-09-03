#pragma once
#include <Istream.hxx>
#include <Ostream.hxx>
#include <token.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class T, unsigned Size>
void tnbLib::writeEntry(Ostream& os, const FixedList<T, Size>& l)
{
	writeListEntry(os, l);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T, unsigned Size>
tnbLib::FixedList<T, Size>::FixedList(Istream& is)
{
	operator>>(is, *this);
}


template<class T, unsigned Size>
tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream& is, FixedList<T, Size>& L)
{
	is.fatalCheck("operator>>(Istream&, FixedList<T, Size>&)");

	if (is.format() == IOstream::ASCII || !contiguous<T>())
	{
		token firstToken(is);

		is.fatalCheck
		(
			"operator>>(Istream&, FixedList<T, Size>&) : reading first token"
		);

		if (firstToken.isCompound())
		{
			L = dynamicCast<token::Compound<List<T>>>
				(
					firstToken.transferCompoundToken(is)
					);
		}
		else if (firstToken.isLabel())
		{
			label s = firstToken.labelToken();

			// Set list length to that read
			L.checkSize(s);
		}
		else if (!firstToken.isPunctuation())
		{
			FatalIOErrorInFunction(is)
				<< "incorrect first token, expected <label> "
				"or '(' or '{', found "
				<< firstToken.info()
				<< exit(FatalIOError);
		}
		else
		{
			// Putback the opening bracket
			is.putBack(firstToken);
		}

		// Read beginning of contents
		char delimiter = is.readBeginList("FixedList");

		if (delimiter == token::BEGIN_LIST)
		{
			for (unsigned i = 0; i < Size; i++)
			{
				is >> L[i];

				is.fatalCheck
				(
					"operator>>(Istream&, FixedList<T, Size>&) : "
					"reading entry"
				);
			}
		}
		else
		{
			T element;
			is >> element;

			is.fatalCheck
			(
				"operator>>(Istream&, FixedList<T, Size>&) : "
				"reading the single entry"
			);

			for (unsigned i = 0; i < Size; i++)
			{
				L[i] = element;
			}
		}

		// Read end of contents
		is.readEndList("FixedList");
	}
	else
	{
		is.read(reinterpret_cast<char*>(L.data()), Size * sizeof(T));

		is.fatalCheck
		(
			"operator>>(Istream&, FixedList<T, Size>&) : "
			"reading the binary block"
		);
	}

	return is;
}


// * * * * * * * * * * * * * * * Ostream Operator *  * * * * * * * * * * * * //

template<class T, unsigned Size>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const FixedList<T, Size>& L)
{
	// Write list contents depending on data format
	if (os.format() == IOstream::ASCII || !contiguous<T>())
	{
		bool uniform = false;

		if (Size > 1 && contiguous<T>())
		{
			uniform = true;

			forAll(L, i)
			{
				if (L[i] != L[0])
				{
					uniform = false;
					break;
				}
			}
		}

		if (uniform)
		{
			// Write size (so it is valid dictionary entry) and start delimiter
			os << L.size() << token::BEGIN_BLOCK;

			// Write contents
			os << L[0];

			// Write end delimiter
			os << token::END_BLOCK;
		}
		else if (Size <= 1 || (Size < 11 && contiguous<T>()))
		{
			// Write start delimiter
			os << token::BEGIN_LIST;

			// Write contents
			forAll(L, i)
			{
				if (i > 0) os << token::SPACE;
				os << L[i];
			}

			// Write end delimiter
			os << token::END_LIST;
		}
		else
		{
			// Write start delimiter
			os << nl << token::BEGIN_LIST;

			// Write contents
			forAll(L, i)
			{
				os << nl << L[i];
			}

			// Write end delimiter
			os << nl << token::END_LIST << nl;
		}
	}
	else
	{
		os.write(reinterpret_cast<const char*>(L.cdata()), Size * sizeof(T));
	}

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const FixedList&)");

	return os;
}


// ************************************************************************* //