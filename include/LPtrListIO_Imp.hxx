#pragma once
#include <Istream.hxx>
#include <Ostream.hxx>
#include <INew.hxx>
#include <error.hxx> // added by amir
#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class LListBase, class T>
template<class INew>
void tnbLib::LPtrList<LListBase, T>::read(Istream& is, const INew& iNew)
{
	is.fatalCheck
	(
		"LPtrList<LListBase, T>::read(Istream&, const INew&)"
	);

	token firstToken(is);

	is.fatalCheck
	(
		"LPtrList<LListBase, T>::read(Istream&, const INew&) : "
		"reading first token"
	);

	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Read beginning of contents
		char delimiter = is.readBeginList("LPtrList<LListBase, T>");

		if (s)
		{
			if (delimiter == token::BEGIN_LIST)
			{
				for (label i = 0; i < s; ++i)
				{
					this->append(iNew(is).ptr());

					is.fatalCheck
					(
						"LPtrList<LListBase, T>::read(Istream&, const INew&) : "
						"reading entry"
					);
				}
			}
			else
			{
				T* tPtr = iNew(is).ptr();
				this->append(tPtr);

				is.fatalCheck
				(
					"LPtrList<LListBase, T>::read(Istream&, const INew&) : "
					"reading entry"
				);

				for (label i = 1; i < s; ++i)
				{
					this->append(tPtr->clone().ptr());
				}
			}
		}

		// Read end of contents
		is.readEndList("LPtrList<LListBase, T>");
	}
	else if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorInFunction
			(
				is
			) << "incorrect first token, '(', found " << firstToken.info()
				<< exit(FatalIOError);
		}

		token lastToken(is);
		is.fatalCheck("LPtrList<LListBase, T>::read(Istream&, const INew&)");

		while
			(
				!(
					lastToken.isPunctuation()
					&& lastToken.pToken() == token::END_LIST
					)
				)
		{
			is.putBack(lastToken);
			this->append(iNew(is).ptr());

			is >> lastToken;
			is.fatalCheck
			(
				"LPtrList<LListBase, T>::read(Istream&, const INew&)"
			);
		}
	}
	else
	{
		FatalIOErrorInFunction
		(
			is
		) << "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	is.fatalCheck("LPtrList<LListBase, T>::read(Istream&, const INew&)");
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class LListBase, class T>
template<class INew>
tnbLib::LPtrList<LListBase, T>::LPtrList(Istream& is, const INew& iNew)
{
	this->read(is, iNew);
}


template<class LListBase, class T>
tnbLib::LPtrList<LListBase, T>::LPtrList(Istream& is)
{
	this->read(is, INew<T>());
}


// * * * * * * * * * * * * * * * Istream Operator  * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::Istream& tnbLib::operator>>(Istream& is, LPtrList<LListBase, T>& L)
{
	L.clear();
	L.read(is, INew<T>());

	return is;
}


// * * * * * * * * * * * * * * * Ostream Operators * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const LPtrList<LListBase, T>& lst)
{
	// Write size
	os << nl << lst.size();

	// Write beginning of contents
	os << nl << token::BEGIN_LIST << nl;

	// Write contents
	for
		(
			typename LPtrList<LListBase, T>::const_iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		os << iter() << nl;
	}

	// Write end of contents
	os << token::END_LIST;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const LPtrList<LListBase, T>&)");

	return os;
}

// ************************************************************************* //