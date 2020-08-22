#include <WallCollisionRecord.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord(Istream& is)
	:
	accessed_(is),
	pRel_(is),
	data_(is)
{
	// Check state of Istream
	is.check
	(
		"tnbLib::WallCollisionRecord<Type>::WallCollisionRecord(tnbLib::Istream&)"
	);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Istream& tnbLib::operator>>(Istream& is, WallCollisionRecord<Type>& wCR)
{
	is >> wCR.accessed_ >> wCR.pRel_ >> wCR.data_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream&"
		"tnbLib::operator>>(tnbLib::Istream&, tnbLib::WallCollisionRecord<Type>&)"
	);

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const WallCollisionRecord<Type>& wCR
	)
{
	os << wCR.accessed_
		<< token::SPACE << wCR.pRel_
		<< token::SPACE << wCR.data_;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::WallCollisionRecord<Type>&)"
	);

	return os;
}


// ************************************************************************* //