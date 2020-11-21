#include <KinematicParcel.hxx>

//#include <IOstreams.hxx>
//#include <IOField.hxx>
//#include <CloudTemplate.hxx>
//
//// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::string tnbLib::KinematicParcel<ParcelType>::propertyList_ =
//tnbLib::KinematicParcel<ParcelType>::propertyList();
//
//template<class ParcelType>
//const std::size_t tnbLib::KinematicParcel<ParcelType>::sizeofFields_
//(
//	sizeof(KinematicParcel<ParcelType>)
//	- offsetof(KinematicParcel<ParcelType>, active_)
//);
//
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::KinematicParcel<ParcelType>::KinematicParcel
//(
//	const polyMesh& mesh,
//	Istream& is,
//	bool readFields
//)
//	:
//	ParcelType(mesh, is, readFields),
//	active_(false),
//	typeId_(0),
//	nParticle_(0.0),
//	d_(0.0),
//	dTarget_(0.0),
//	U_(Zero),
//	rho_(0.0),
//	age_(0.0),
//	tTurb_(0.0),
//	UTurb_(Zero)
//{
//	if (readFields)
//	{
//		if (is.format() == IOstream::ASCII)
//		{
//			active_ = readBool(is);
//			typeId_ = readLabel(is);
//			nParticle_ = readScalar(is);
//			d_ = readScalar(is);
//			dTarget_ = readScalar(is);
//			is >> U_;
//			rho_ = readScalar(is);
//			age_ = readScalar(is);
//			tTurb_ = readScalar(is);
//			is >> UTurb_;
//		}
//		else
//		{
//			is.read(reinterpret_cast<char*>(&active_), sizeofFields_);
//		}
//	}
//
//	// Check state of Istream
//	is.check
//	(
//		"KinematicParcel<ParcelType>::KinematicParcel"
//		"(const polyMesh&, Istream&, bool)"
//	);
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::KinematicParcel<ParcelType>::readFields(CloudType& c)
//{
//	bool write = c.size();
//
//	ParcelType::readFields(c);
//
//	IOField<label> active
//	(
//		c.fieldIOobject("active", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, active);
//
//	IOField<label> typeId
//	(
//		c.fieldIOobject("typeId", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, typeId);
//
//	IOField<scalar> nParticle
//	(
//		c.fieldIOobject("nParticle", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, nParticle);
//
//	IOField<scalar> d
//	(
//		c.fieldIOobject("d", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, d);
//
//	IOField<scalar> dTarget
//	(
//		c.fieldIOobject("dTarget", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, dTarget);
//
//	IOField<vector> U
//	(
//		c.fieldIOobject("U", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, U);
//
//	IOField<scalar> rho
//	(
//		c.fieldIOobject("rho", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, rho);
//
//	IOField<scalar> age
//	(
//		c.fieldIOobject("age", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, age);
//
//	IOField<scalar> tTurb
//	(
//		c.fieldIOobject("tTurb", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, tTurb);
//
//	IOField<vector> UTurb
//	(
//		c.fieldIOobject("UTurb", IOobject::MUST_READ),
//		write
//	);
//	c.checkFieldIOobject(c, UTurb);
//
//	label i = 0;
//
//	forAllIter(typename CloudType, c, iter)
//	{
//		KinematicParcel<ParcelType>& p = iter();
//
//		p.active_ = active[i];
//		p.typeId_ = typeId[i];
//		p.nParticle_ = nParticle[i];
//		p.d_ = d[i];
//		p.dTarget_ = dTarget[i];
//		p.U_ = U[i];
//		p.rho_ = rho[i];
//		p.age_ = age[i];
//		p.tTurb_ = tTurb[i];
//		p.UTurb_ = UTurb[i];
//
//		i++;
//	}
//}
//
//
//template<class ParcelType>
//template<class CloudType>
//void tnbLib::KinematicParcel<ParcelType>::writeFields(const CloudType& c)
//{
//	ParcelType::writeFields(c);
//
//	label np = c.size();
//
//	IOField<label> active(c.fieldIOobject("active", IOobject::NO_READ), np);
//	IOField<label> typeId(c.fieldIOobject("typeId", IOobject::NO_READ), np);
//	IOField<scalar> nParticle
//	(
//		c.fieldIOobject("nParticle", IOobject::NO_READ),
//		np
//	);
//	IOField<scalar> d(c.fieldIOobject("d", IOobject::NO_READ), np);
//	IOField<scalar> dTarget(c.fieldIOobject("dTarget", IOobject::NO_READ), np);
//	IOField<vector> U(c.fieldIOobject("U", IOobject::NO_READ), np);
//	IOField<scalar> rho(c.fieldIOobject("rho", IOobject::NO_READ), np);
//	IOField<scalar> age(c.fieldIOobject("age", IOobject::NO_READ), np);
//	IOField<scalar> tTurb(c.fieldIOobject("tTurb", IOobject::NO_READ), np);
//	IOField<vector> UTurb(c.fieldIOobject("UTurb", IOobject::NO_READ), np);
//
//	label i = 0;
//
//	forAllConstIter(typename CloudType, c, iter)
//	{
//		const KinematicParcel<ParcelType>& p = iter();
//
//		active[i] = p.active();
//		typeId[i] = p.typeId();
//		nParticle[i] = p.nParticle();
//		d[i] = p.d();
//		dTarget[i] = p.dTarget();
//		U[i] = p.U();
//		rho[i] = p.rho();
//		age[i] = p.age();
//		tTurb[i] = p.tTurb();
//		UTurb[i] = p.UTurb();
//
//		i++;
//	}
//
//	const bool write = np > 0;
//
//	active.write(write);
//	typeId.write(write);
//	nParticle.write(write);
//	d.write(write);
//	dTarget.write(write);
//	U.write(write);
//	rho.write(write);
//	age.write(write);
//	tTurb.write(write);
//	UTurb.write(write);
//}
//
//
//// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //
//
//template<class ParcelType>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const KinematicParcel<ParcelType>& p
//	)
//{
//	if (os.format() == IOstream::ASCII)
//	{
//		os << static_cast<const ParcelType&>(p)
//			<< token::SPACE << p.active()
//			<< token::SPACE << p.typeId()
//			<< token::SPACE << p.nParticle()
//			<< token::SPACE << p.d()
//			<< token::SPACE << p.dTarget()
//			<< token::SPACE << p.U()
//			<< token::SPACE << p.rho()
//			<< token::SPACE << p.age()
//			<< token::SPACE << p.tTurb()
//			<< token::SPACE << p.UTurb();
//	}
//	else
//	{
//		os << static_cast<const ParcelType&>(p);
//		os.write
//		(
//			reinterpret_cast<const char*>(&p.active_),
//			KinematicParcel<ParcelType>::sizeofFields_
//		);
//	}
//
//	// Check state of Ostream
//	os.check
//	(
//		"Ostream& operator<<(Ostream&, const KinematicParcel<ParcelType>&)"
//	);
//
//	return os;
//}
//
//
//// ************************************************************************* //