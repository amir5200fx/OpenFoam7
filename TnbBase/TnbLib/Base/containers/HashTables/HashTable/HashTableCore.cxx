#include <HashTable.hxx>

#include <uLabel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(HashTableCore, 0);
}

const tnbLib::label tnbLib::HashTableCore::maxTableSize
(
	tnbLib::HashTableCore::canonicalSize
	(
		tnbLib::labelMax / 2
	)
);


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::HashTableCore::canonicalSize(const label size)
{
	if (size < 1)
	{
		return 0;
	}

	// enforce power of two
	uLabel goodSize = size;

	if (goodSize & (goodSize - 1))
	{
		// brute-force is fast enough
		goodSize = 1;
		while (goodSize < unsigned(size))
		{
			goodSize <<= 1;
		}
	}

	return goodSize;
}


// ************************************************************************* //