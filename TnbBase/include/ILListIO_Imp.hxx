#pragma once
#include <Istream.hxx>
#include <IOstreams.hxx>
#include <INew.hxx>


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class LListBase, class T>
template<class INew>
void tnbLib::ILList<LListBase, T>::read(Istream& is, const INew& iNew)
{
	is.fatalCheck("operator>>(Istream&, ILList<LListBase, T>&)");

	token firstToken(is);

	is.fatalCheck
	(
		"operator>>(Istream&, ILList<LListBase, T>&) : reading first token"
	);

	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Read beginning of contents
		char delimiter = is.readBeginList("ILList<LListBase, T>");

		if (s)
		{
			if (delimiter == token::BEGIN_LIST)
			{
				for (label i = 0; i < s; ++i)
				{
					this->append(iNew(is).ptr());

					is.fatalCheck
					(
						"operator>>(Istream&, ILList<LListBase, T>&) : "
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
					"operator>>(Istream&, ILList<LListBase, T>&) : "
					"reading entry"
				);

				for (label i = 1; i < s; ++i)
				{
					this->append(new T(*tPtr));
				}
			}
		}

		// Read end of contents
		is.readEndList("ILList<LListBase, T>");
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
		is.fatalCheck("operator>>(Istream&, ILList<LListBase, T>&)");

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
			is.fatalCheck("operator>>(Istream&, ILList<LListBase, T>&)");
		}
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	is.fatalCheck("operator>>(Istream&, ILList<LListBase, T>&)");
}


template<class LListBase, class T>
template<class INew>
tnbLib::ILList<LListBase, T>::ILList(Istream& is, const INew& iNew)
{
	this->read(is, iNew);
}


template<class LListBase, class T>
tnbLib::ILList<LListBase, T>::ILList(Istream& is)
{
	this->read(is, INew<T>());
}


// * * * * * * * * * * * * * * * Istream Operator  * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::Istream& tnbLib::operator>>(Istream& is, ILList<LListBase, T>& L)
{
	L.clear();
	L.read(is, INew<T>());

	return is;
}


// ************************************************************************* //