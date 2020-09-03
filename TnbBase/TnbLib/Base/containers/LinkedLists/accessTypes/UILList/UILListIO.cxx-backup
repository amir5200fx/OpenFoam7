#include <UILList.hxx>

#include <Ostream.hxx>
#include <token.hxx>

// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const UILList<LListBase, T>& lst)
{
	// Write size
	os << nl << lst.size();

	// Write beginning of contents
	os << nl << token::BEGIN_LIST << nl;

	// Write contents
	for
		(
			typename UILList<LListBase, T>::const_iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		os << iter() << nl;
	}

	// Write end of contents
	os << token::END_LIST;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const UILList<LListBase, T>&)");

	return os;
}

// ************************************************************************* //