#include <CollidingParcel.hxx>

//#include <IOstreams.hxx>
//#include <IOField.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::string tnbLib::CollidingParcel<ParcelType>::propertyList_ =
//tnbLib::CollidingParcel<ParcelType>::propertyList();
//
//template<class ParcelType>
//const std::size_t tnbLib::CollidingParcel<ParcelType>::sizeofFields_
//(
//	offsetof(CollidingParcel<ParcelType>, collisionRecords_)
//	- offsetof(CollidingParcel<ParcelType>, f_)
//);
//
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::CollidingParcel<ParcelType>::CollidingParcel
//(
//	const polyMesh& mesh,
//	Istream& is,
//	bool readFields
//)
//	:
//	ParcelType(mesh, is, readFields),
//	f_(Zero),
//	angularMomentum_(Zero),
//	torque_(Zero),
//	collisionRecords_()
//{
//	if (readFields)
//	{
//		if (is.format() == IOstream::ASCII)
//		{
//			is >> f_;
//			is >> angularMomentum_;
//			is >> torque_;
//		}
//		else
//		{
//			is.read(reinterpret_cast<char*>(&f_), sizeofFields_);
//		}
//
//		is >> collisionRecords_;
//	}
//
//	// Check state of Istream
//	is.check
//	(
//		"CollidingParcel<ParcelType>::Collisions"
//		"(const polyMesh&, Istream&, bool)"
//	);
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::CollidingParcel<ParcelType>::readFields(CloudType& c)
//{
//	bool write = c.size();
//
//	ParcelType::readFields(c);
//
//	IOField<vector> f(c.fieldIOobject("f", IOobject::MUST_READ), write);
//	c.checkFieldIOobject(c, f);
//
//	IOField<vector> angularMomentum
//	(
//		c.fieldIOobject("angularMomentum", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, angularMomentum);
//
//	IOField<vector> torque
//	(
//		c.fieldIOobject("torque", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, torque);
//
//	labelFieldCompactIOField collisionRecordsPairAccessed
//	(
//		c.fieldIOobject("collisionRecordsPairAccessed", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsPairAccessed);
//
//	labelFieldCompactIOField collisionRecordsPairOrigProcOfOther
//	(
//		c.fieldIOobject
//		(
//			"collisionRecordsPairOrigProcOfOther",
//			IOobject::MUST_READ
//		),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsPairOrigProcOfOther);
//
//	labelFieldCompactIOField collisionRecordsPairOrigIdOfOther
//	(
//		c.fieldIOobject
//		(
//			"collisionRecordsPairOrigIdOfOther",
//			IOobject::MUST_READ
//		),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsPairOrigProcOfOther);
//
//	pairDataFieldCompactIOField collisionRecordsPairData
//	(
//		c.fieldIOobject("collisionRecordsPairData", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsPairData);
//
//	labelFieldCompactIOField collisionRecordsWallAccessed
//	(
//		c.fieldIOobject("collisionRecordsWallAccessed", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsWallAccessed);
//
//	vectorFieldCompactIOField collisionRecordsWallPRel
//	(
//		c.fieldIOobject("collisionRecordsWallPRel", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsWallPRel);
//
//	wallDataFieldCompactIOField collisionRecordsWallData
//	(
//		c.fieldIOobject("collisionRecordsWallData", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldFieldIOobject(c, collisionRecordsWallData);
//
//	label i = 0;
//
//	forAllIter(typename CloudType, c, iter)
//	{
//		CollidingParcel<ParcelType>& p = iter();
//
//		p.f_ = f[i];
//		p.angularMomentum_ = angularMomentum[i];
//		p.torque_ = torque[i];
//
//		p.collisionRecords_ = collisionRecordList
//		(
//			collisionRecordsPairAccessed[i],
//			collisionRecordsPairOrigProcOfOther[i],
//			collisionRecordsPairOrigIdOfOther[i],
//			collisionRecordsPairData[i],
//			collisionRecordsWallAccessed[i],
//			collisionRecordsWallPRel[i],
//			collisionRecordsWallData[i]
//		);
//
//		i++;
//	}
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::CollidingParcel<ParcelType>::writeFields(const CloudType& c)
//{
//	ParcelType::writeFields(c);
//
//	label np = c.size();
//
//	IOField<vector> f(c.fieldIOobject("f", IOobject::NO_READ), np);
//	IOField<vector> angularMomentum
//	(
//		c.fieldIOobject("angularMomentum", IOobject::NO_READ),
//		np
//	);
//	IOField<vector> torque(c.fieldIOobject("torque", IOobject::NO_READ), np);
//
//	labelFieldCompactIOField collisionRecordsPairAccessed
//	(
//		c.fieldIOobject("collisionRecordsPairAccessed", IOobject::NO_READ),
//		np
//	);
//	labelFieldCompactIOField collisionRecordsPairOrigProcOfOther
//	(
//		c.fieldIOobject
//		(
//			"collisionRecordsPairOrigProcOfOther",
//			IOobject::NO_READ
//		),
//		np
//	);
//	labelFieldCompactIOField collisionRecordsPairOrigIdOfOther
//	(
//		c.fieldIOobject("collisionRecordsPairOrigIdOfOther", IOobject::NO_READ),
//		np
//	);
//	pairDataFieldCompactIOField collisionRecordsPairData
//	(
//		c.fieldIOobject("collisionRecordsPairData", IOobject::NO_READ),
//		np
//	);
//	labelFieldCompactIOField collisionRecordsWallAccessed
//	(
//		c.fieldIOobject("collisionRecordsWallAccessed", IOobject::NO_READ),
//		np
//	);
//	vectorFieldCompactIOField collisionRecordsWallPRel
//	(
//		c.fieldIOobject("collisionRecordsWallPRel", IOobject::NO_READ),
//		np
//	);
//	wallDataFieldCompactIOField collisionRecordsWallData
//	(
//		c.fieldIOobject("collisionRecordsWallData", IOobject::NO_READ),
//		np
//	);
//
//	label i = 0;
//
//	forAllConstIter(typename CloudType, c, iter)
//	{
//		const CollidingParcel<ParcelType>& p = iter();
//
//		f[i] = p.f();
//		angularMomentum[i] = p.angularMomentum();
//		torque[i] = p.torque();
//
//		collisionRecordsPairAccessed[i] = p.collisionRecords().pairAccessed();
//		collisionRecordsPairOrigProcOfOther[i] =
//			p.collisionRecords().pairOrigProcOfOther();
//		collisionRecordsPairOrigIdOfOther[i] =
//			p.collisionRecords().pairOrigIdOfOther();
//		collisionRecordsPairData[i] = p.collisionRecords().pairData();
//		collisionRecordsWallAccessed[i] = p.collisionRecords().wallAccessed();
//		collisionRecordsWallPRel[i] = p.collisionRecords().wallPRel();
//		collisionRecordsWallData[i] = p.collisionRecords().wallData();
//
//		i++;
//	}
//
//	const bool write = (np > 0);
//
//	f.write(write);
//	angularMomentum.write(write);
//	torque.write(write);
//
//	collisionRecordsPairAccessed.write(write);
//	collisionRecordsPairOrigProcOfOther.write(write);
//	collisionRecordsPairOrigIdOfOther.write(write);
//	collisionRecordsPairData.write(write);
//	collisionRecordsWallAccessed.write(write);
//	collisionRecordsWallPRel.write(write);
//	collisionRecordsWallData.write(write);
//}
//
//
//// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const CollidingParcel<ParcelType>& p
//	)
//{
//	if (os.format() == IOstream::ASCII)
//	{
//		os << static_cast<const ParcelType&>(p)
//			<< token::SPACE << p.f_
//			<< token::SPACE << p.angularMomentum_
//			<< token::SPACE << p.torque_
//			<< token::SPACE << p.collisionRecords_;
//	}
//	else
//	{
//		os << static_cast<const ParcelType&>(p);
//		os.write
//		(
//			reinterpret_cast<const char*>(&p.f_),
//			CollidingParcel<ParcelType>::sizeofFields_
//		);
//		os << p.collisionRecords();
//	}
//
//	// Check state of Ostream
//	os.check
//	(
//		"Ostream& operator<<(Ostream&, const CollidingParcel<ParcelType>&)"
//	);
//
//	return os;
//}
//
//
//// ************************************************************************* //