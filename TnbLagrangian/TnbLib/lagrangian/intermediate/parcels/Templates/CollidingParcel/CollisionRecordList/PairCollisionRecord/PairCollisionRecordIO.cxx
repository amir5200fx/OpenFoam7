#include <PairCollisionRecord.hxx>

//#include <IOstreams.hxx>
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class Type>
//tnbLib::PairCollisionRecord<Type>::PairCollisionRecord(Istream& is)
//	:
//	origProcOfOther_(readLabel(is)),
//	origIdOfOther_(readLabel(is)),
//	data_(is)
//{
//	// Check state of Istream
//	is.check
//	(
//		"tnbLib::PairCollisionRecord<Type>::PairCollisionRecord(tnbLib::Istream&)"
//	);
//}
//
//
//// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //
//
//template<class Type>
//tnbLib::Istream& tnbLib::operator>>(Istream& is, PairCollisionRecord<Type>& pCR)
//{
//	is >> pCR.origProcOfOther_ >> pCR.origIdOfOther_ >> pCR.data_;
//
//	// Check state of Istream
//	is.check
//	(
//		"tnbLib::Istream&"
//		"tnbLib::operator>>(tnbLib::Istream&, tnbLib::PairCollisionRecord<Type>&)"
//	);
//
//	return is;
//}
//
//
//template<class Type>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const PairCollisionRecord<Type>& pCR
//	)
//{
//	os << pCR.origProcOfOther_
//		<< token::SPACE << pCR.origIdOfOther_
//		<< token::SPACE << pCR.data_;
//
//	// Check state of Ostream
//	os.check
//	(
//		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
//		"const tnbLib::PairCollisionRecord<Type>&)"
//	);
//
//	return os;
//}
//
//
//// ************************************************************************* //