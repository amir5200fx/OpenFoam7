#pragma once
#include <SLList.hxx>
#include <Istream.hxx>
#include <Ostream.hxx>
#include <INew.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class T>
template<class INew>
void tnbLib::PtrList<T>::read(Istream& is, const INew& inewt)
{
	is.fatalCheck("PtrList<T>::read(Istream&, const INew&)");

	token firstToken(is);

	is.fatalCheck
	(
		"PtrList<T>::read(Istream&, const INew&) : "
		"reading first token"
	);

	if (firstToken.isLabel())
	{
		// Read size of list
		label s = firstToken.labelToken();

		setSize(s);

		// Read beginning of contents
		char delimiter = is.readBeginList("PtrList");

		if (s)
		{
			if (delimiter == token::BEGIN_LIST)
			{
				forAll(*this, i)
				{
					set(i, inewt(is));

					is.fatalCheck
					(
						"PtrList<T>::read(Istream&, const INew&) : "
						"reading entry"
					);
				}
			}
			else
			{
				T* tPtr = inewt(is).ptr();
				set(0, tPtr);

				is.fatalCheck
				(
					"PtrList<T>::read(Istream&, const INew&) : "
					"reading the single entry"
				);

				for (label i = 1; i < s; i++)
				{
					set(i, tPtr->clone());
				}
			}
		}

		// Read end of contents
		is.readEndList("PtrList");
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

		SLList<T*> sllPtrs;

		token lastToken(is);
		while
			(
				!(
					lastToken.isPunctuation()
					&& lastToken.pToken() == token::END_LIST
					)
				)
		{
			is.putBack(lastToken);

			if (is.eof())
			{
				FatalIOErrorInFunction
				(
					is
				) << "Premature EOF after reading " << lastToken.info()
					<< exit(FatalIOError);
			}

			sllPtrs.append(inewt(is).ptr());
			is >> lastToken;
		}

		setSize(sllPtrs.size());

		label i = 0;
		for
			(
				typename SLList<T*>::iterator iter = sllPtrs.begin();
				iter != sllPtrs.end();
				++iter
				)
		{
			set(i++, iter());
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
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
template<class INew>
tnbLib::PtrList<T>::PtrList(Istream& is, const INew& inewt)
{
	read(is, inewt);
}


template<class T>
tnbLib::PtrList<T>::PtrList(Istream& is)
{
	read(is, INew<T>());
}


// * * * * * * * * * * * * * * * Istream Operator  * * * * * * * * * * * * * //

template<class T>
tnbLib::Istream& tnbLib::operator>>(Istream& is, PtrList<T>& L)
{
	L.clear();
	L.read(is, INew<T>());

	return is;
}


// ************************************************************************* //