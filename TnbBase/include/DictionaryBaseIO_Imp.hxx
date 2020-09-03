#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * * //

template<class IDLListType, class T>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const DictionaryBase<IDLListType, T>& dict)
{
	for
		(
			typename IDLListType::const_iterator iter = dict.begin();
			iter != dict.end();
			++iter
			)
	{
		os << *iter;

		// Check stream before going to next entry.
		if (!os.good())
		{
			Info
				<< "operator<<(Ostream&, const DictionaryBase&) : "
				<< "Can't write entry for DictionaryBase"
				<< endl;

			return os;
		}
	}

	return os;
}


// ************************************************************************* //