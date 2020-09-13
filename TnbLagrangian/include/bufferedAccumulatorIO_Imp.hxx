#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream&
tnbLib::operator<<(Ostream& os, const bufferedAccumulator<Type>& bA)
{

	os << bA.averagesTaken_
		<< static_cast<const List<Field<Type>>&>(bA)
		<< bA.bufferOffsets();

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::bufferedAccumulator&)"
	);

	return os;
}


// ************************************************************************* //