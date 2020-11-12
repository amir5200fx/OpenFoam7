#include <MPPICParcel.hxx>

//#include <IOstreams.hxx>
//#include <IOField.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::string tnbLib::MPPICParcel<ParcelType>::propertyList_ =
//tnbLib::MPPICParcel<ParcelType>::propertyList();
//
//template<class ParcelType>
//const std::size_t tnbLib::MPPICParcel<ParcelType>::sizeofFields_
//(
//	sizeof(MPPICParcel<ParcelType>) - sizeof(ParcelType)
//);
//
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::MPPICParcel<ParcelType>::MPPICParcel
//(
//	const polyMesh& mesh,
//	Istream& is,
//	bool readFields
//)
//	:
//	ParcelType(mesh, is, readFields),
//	UCorrect_(Zero)
//{
//	if (readFields)
//	{
//		if (is.format() == IOstream::ASCII)
//		{
//			is >> UCorrect_;
//		}
//		else
//		{
//			is.read(reinterpret_cast<char*>(&UCorrect_), sizeofFields_);
//		}
//	}
//
//	is.check
//	(
//		"MPPICParcel<ParcelType>::Collisions"
//		"(const polyMesh&, Istream&, bool)"
//	);
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::MPPICParcel<ParcelType>::readFields(CloudType& c)
//{
//	bool valid = c.size();
//
//	ParcelType::readFields(c);
//
//	IOField<vector> UCorrect
//	(
//		c.fieldIOobject("UCorrect", IOobject::MUST_READ),
//		valid
//	);
//	c.checkFieldIOobject(c, UCorrect);
//
//	label i = 0;
//
//	forAllIter(typename CloudType, c, iter)
//	{
//		MPPICParcel<ParcelType>& p = iter();
//
//		p.UCorrect_ = UCorrect[i];
//
//		i++;
//	}
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::MPPICParcel<ParcelType>::writeFields(const CloudType& c)
//{
//	ParcelType::writeFields(c);
//
//	label np = c.size();
//
//	IOField<vector>
//		UCorrect(c.fieldIOobject("UCorrect", IOobject::NO_READ), np);
//
//	label i = 0;
//
//	forAllConstIter(typename CloudType, c, iter)
//	{
//		const MPPICParcel<ParcelType>& p = iter();
//
//		UCorrect[i] = p.UCorrect();
//
//		i++;
//	}
//
//	UCorrect.write(np > 0);
//}
//
//
//// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const MPPICParcel<ParcelType>& p
//	)
//{
//	if (os.format() == IOstream::ASCII)
//	{
//		os << static_cast<const ParcelType&>(p)
//			<< token::SPACE << p.UCorrect();
//	}
//	else
//	{
//		os << static_cast<const ParcelType&>(p);
//		os.write
//		(
//			reinterpret_cast<const char*>(&p.UCorrect_),
//			MPPICParcel<ParcelType>::sizeofFields_
//		);
//	}
//
//	os.check
//	(
//		"Ostream& operator<<(Ostream&, const MPPICParcel<ParcelType>&)"
//	);
//
//	return os;
//}
//
//
//// ************************************************************************* //