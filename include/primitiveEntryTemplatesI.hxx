#pragma once
#include <PtrList.hxx>  // added by amir
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::primitiveEntry::primitiveEntry(const keyType& key, const T& t)
	:
	entry(key),
	ITstream(key, tokenList(10))
{
	OStringStream os;
	os << t << token::END_STATEMENT;
	readEntry(dictionary::null, IStringStream(os.str())());
}


// ************************************************************************* //