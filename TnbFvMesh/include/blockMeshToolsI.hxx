#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void tnbLib::blockMeshTools::read
(
	Istream& is,
	List<T>& L,
	const dictionary& dict
)
{
	token firstToken(is);

	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Set list length to that read
		L.setSize(s);

		// Read list contents depending on data format

		// Read beginning of contents
		char delimiter = is.readBeginList("List");

		if (s)
		{
			if (delimiter == token::BEGIN_LIST)
			{
				for (label i = 0; i < s; i++)
				{
					read(is, L[i], dict);
				}
			}
		}

		// Read end of contents
		is.readEndList("List");
	}
	else if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorInFunction(is)
				<< "incorrect first token, expected '(', found "
				<< firstToken.info()
				<< exit(FatalIOError);
		}

		SLList<T> sll;

		while (true)
		{
			token t(is);
			if (t.isPunctuation() && t.pToken() == token::END_LIST)
			{
				break;
			}
			is.putBack(t);
			T elem;
			read(is, elem, dict);
			sll.append(elem);
		}

		// Convert the singly-linked list to this list
		L = sll;
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}
}


template<class T>
tnbLib::List<T> tnbLib::blockMeshTools::read
(
	Istream& is,
	const dictionary& dict
)
{
	List<T> L;
	read(is, L, dict);
	return L;
}


// ************************************************************************* //