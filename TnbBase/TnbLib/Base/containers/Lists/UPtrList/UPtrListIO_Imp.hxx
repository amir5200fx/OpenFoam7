#pragma once
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class T>
void tnbLib::writeEntry(Ostream& os, const UPtrList<T>& l)
{
	writeListEntry(os, l);
}


// * * * * * * * * * * * * * * * Ostream Operators * * * * * * * * * * * * * //

template<class T>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const UPtrList<T>& L)
{
	// Write size and start delimiter
	os << nl << indent << L.size() << nl
		<< indent << token::BEGIN_LIST << incrIndent;

	// Write contents
	forAll(L, i)
	{
		os << nl << L[i];
	}

	// Write end delimiter
	os << nl << decrIndent << indent << token::END_LIST << nl;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const UPtrList&)");

	return os;
}


// ************************************************************************* //