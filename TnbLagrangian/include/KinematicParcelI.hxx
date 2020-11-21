#pragma once
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
inline
tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties()
	:
	dict_(dictionary::null),
	parcelTypeId_(dict_, -1),
	rhoMin_(dict_, 0.0),
	rho0_(dict_, 0.0),
	minParcelMass_(dict_, 0.0)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties
(
	const constantProperties& cp
)
	:
	dict_(cp.dict_),
	parcelTypeId_(cp.parcelTypeId_),
	rhoMin_(cp.rhoMin_),
	rho0_(cp.rho0_),
	minParcelMass_(cp.minParcelMass_)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::constantProperties::constantProperties
(
	const dictionary& parentDict
)
	:
	dict_(parentDict.subOrEmptyDict("constantProperties")),
	parcelTypeId_(dict_, "parcelTypeId", -1),
	rhoMin_(dict_, "rhoMin", 1e-15),
	rho0_(dict_, "rho0"),
	minParcelMass_(dict_, "minParcelMass", 1e-15)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	active_(true),
	typeId_(-1),
	nParticle_(0),
	d_(0.0),
	dTarget_(0.0),
	U_(Zero),
	rho_(0.0),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const vector& position,
	const label celli
)
	:
	ParcelType(owner, position, celli),
	active_(true),
	typeId_(-1),
	nParticle_(0),
	d_(0.0),
	dTarget_(0.0),
	U_(Zero),
	rho_(0.0),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


template<class ParcelType>
inline tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti,
	const label typeId,
	const scalar nParticle0,
	const scalar d0,
	const scalar dTarget0,
	const vector& U0,
	const constantProperties& constProps
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	active_(true),
	typeId_(typeId),
	nParticle_(nParticle0),
	d_(d0),
	dTarget_(dTarget0),
	U_(U0),
	rho_(constProps.rho0()),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::dictionary&
tnbLib::KinematicParcel<ParcelType>::constantProperties::dict() const
{
	return dict_;
}


template<class ParcelType>
inline tnbLib::label
tnbLib::KinematicParcel<ParcelType>::constantProperties::parcelTypeId() const
{
	return parcelTypeId_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::rhoMin() const
{
	return rhoMin_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::rho0() const
{
	return rho0_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::KinematicParcel<ParcelType>::constantProperties::minParcelMass() const
{
	return minParcelMass_.value();
}


// * * * * * * * KinematicParcel Member Functions  * * * * * * * //

template<class ParcelType>
inline bool tnbLib::KinematicParcel<ParcelType>::active() const
{
	return active_;
}


template<class ParcelType>
inline tnbLib::label tnbLib::KinematicParcel<ParcelType>::typeId() const
{
	return typeId_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::nParticle() const
{
	return nParticle_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::d() const
{
	return d_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::dTarget() const
{
	return dTarget_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::U() const
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::rho() const
{
	return rho_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::age() const
{
	return age_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::tTurb() const
{
	return tTurb_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::UTurb() const
{
	return UTurb_;
}


template<class ParcelType>
inline bool& tnbLib::KinematicParcel<ParcelType>::active()
{
	return active_;
}


template<class ParcelType>
inline tnbLib::label& tnbLib::KinematicParcel<ParcelType>::typeId()
{
	return typeId_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::nParticle()
{
	return nParticle_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::d()
{
	return d_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::dTarget()
{
	return dTarget_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::U()
{
	return U_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::rho()
{
	return rho_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::age()
{
	return age_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::KinematicParcel<ParcelType>::tTurb()
{
	return tTurb_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::KinematicParcel<ParcelType>::UTurb()
{
	return UTurb_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::massCell
(
	const trackingData& td
) const
{
	return td.rhoc()*this->mesh().cellVolumes()[this->cell()];
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::mass() const
{
	return rho_ * volume();
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::momentOfInertia() const
{
	return 0.1*mass()*sqr(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::volume() const
{
	return volume(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::volume(const scalar d)
{
	return pi / 6.0*pow3(d);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaP() const
{
	return areaP(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaP(const scalar d)
{
	return 0.25*areaS(d);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaS() const
{
	return areaS(d_);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::areaS(const scalar d)
{
	return pi * d*d;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Re
(
	const trackingData& td
) const
{
	return Re(td.rhoc(), U_, td.Uc(), d_, td.muc());
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Re
(
	const scalar rhoc,
	const vector& U,
	const vector& Uc,
	const scalar d,
	const scalar muc
)
{
	return rhoc * mag(U - Uc)*d / max(muc, rootVSmall);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::We
(
	const trackingData& td,
	const scalar sigma
) const
{
	return We(td.rhoc(), U_, td.Uc(), d_, sigma);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::We
(
	const scalar rhoc,
	const vector& U,
	const vector& Uc,
	const scalar d,
	const scalar sigma
)
{
	return rhoc * magSqr(U - Uc)*d / max(sigma, rootVSmall);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Eo
(
	const trackingData& td,
	const scalar sigma
) const
{
	return Eo(td.g(), rho_, td.rhoc(), U_, d_, sigma);
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::KinematicParcel<ParcelType>::Eo
(
	const vector& g,
	const scalar rho,
	const scalar rhoc,
	const vector& U,
	const scalar d,
	const scalar sigma
)
{
	const vector dir = U / max(mag(U), rootVSmall);
	return mag(g & dir)*mag(rho - rhoc)*sqr(d) / max(sigma, rootVSmall);
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>
#include <IOField.hxx>
#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::KinematicParcel<ParcelType>::propertyList_ =
tnbLib::KinematicParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::KinematicParcel<ParcelType>::sizeofFields_
(
	sizeof(KinematicParcel<ParcelType>)
	- offsetof(KinematicParcel<ParcelType>, active_)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	active_(false),
	typeId_(0),
	nParticle_(0.0),
	d_(0.0),
	dTarget_(0.0),
	U_(Zero),
	rho_(0.0),
	age_(0.0),
	tTurb_(0.0),
	UTurb_(Zero)
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			active_ = readBool(is);
			typeId_ = readLabel(is);
			nParticle_ = readScalar(is);
			d_ = readScalar(is);
			dTarget_ = readScalar(is);
			is >> U_;
			rho_ = readScalar(is);
			age_ = readScalar(is);
			tTurb_ = readScalar(is);
			is >> UTurb_;
		}
		else
		{
			is.read(reinterpret_cast<char*>(&active_), sizeofFields_);
		}
	}

	// Check state of Istream
	is.check
	(
		"KinematicParcel<ParcelType>::KinematicParcel"
		"(const polyMesh&, Istream&, bool)"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::KinematicParcel<ParcelType>::readFields(CloudType& c)
{
	bool write = c.size();

	ParcelType::readFields(c);

	IOField<label> active
	(
		c.fieldIOobject("active", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, active);

	IOField<label> typeId
	(
		c.fieldIOobject("typeId", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, typeId);

	IOField<scalar> nParticle
	(
		c.fieldIOobject("nParticle", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, nParticle);

	IOField<scalar> d
	(
		c.fieldIOobject("d", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, d);

	IOField<scalar> dTarget
	(
		c.fieldIOobject("dTarget", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, dTarget);

	IOField<vector> U
	(
		c.fieldIOobject("U", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, U);

	IOField<scalar> rho
	(
		c.fieldIOobject("rho", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, rho);

	IOField<scalar> age
	(
		c.fieldIOobject("age", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, age);

	IOField<scalar> tTurb
	(
		c.fieldIOobject("tTurb", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, tTurb);

	IOField<vector> UTurb
	(
		c.fieldIOobject("UTurb", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, UTurb);

	label i = 0;

	forAllIter(typename CloudType, c, iter)
	{
		KinematicParcel<ParcelType>& p = iter();

		p.active_ = active[i];
		p.typeId_ = typeId[i];
		p.nParticle_ = nParticle[i];
		p.d_ = d[i];
		p.dTarget_ = dTarget[i];
		p.U_ = U[i];
		p.rho_ = rho[i];
		p.age_ = age[i];
		p.tTurb_ = tTurb[i];
		p.UTurb_ = UTurb[i];

		i++;
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::KinematicParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);

	label np = c.size();

	IOField<label> active(c.fieldIOobject("active", IOobject::NO_READ), np);
	IOField<label> typeId(c.fieldIOobject("typeId", IOobject::NO_READ), np);
	IOField<scalar> nParticle
	(
		c.fieldIOobject("nParticle", IOobject::NO_READ),
		np
	);
	IOField<scalar> d(c.fieldIOobject("d", IOobject::NO_READ), np);
	IOField<scalar> dTarget(c.fieldIOobject("dTarget", IOobject::NO_READ), np);
	IOField<vector> U(c.fieldIOobject("U", IOobject::NO_READ), np);
	IOField<scalar> rho(c.fieldIOobject("rho", IOobject::NO_READ), np);
	IOField<scalar> age(c.fieldIOobject("age", IOobject::NO_READ), np);
	IOField<scalar> tTurb(c.fieldIOobject("tTurb", IOobject::NO_READ), np);
	IOField<vector> UTurb(c.fieldIOobject("UTurb", IOobject::NO_READ), np);

	label i = 0;

	forAllConstIter(typename CloudType, c, iter)
	{
		const KinematicParcel<ParcelType>& p = iter();

		active[i] = p.active();
		typeId[i] = p.typeId();
		nParticle[i] = p.nParticle();
		d[i] = p.d();
		dTarget[i] = p.dTarget();
		U[i] = p.U();
		rho[i] = p.rho();
		age[i] = p.age();
		tTurb[i] = p.tTurb();
		UTurb[i] = p.UTurb();

		i++;
	}

	const bool write = np > 0;

	active.write(write);
	typeId.write(write);
	nParticle.write(write);
	d.write(write);
	dTarget.write(write);
	U.write(write);
	rho.write(write);
	age.write(write);
	tTurb.write(write);
	UTurb.write(write);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const KinematicParcel<ParcelType>& p
	)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << p.active()
			<< token::SPACE << p.typeId()
			<< token::SPACE << p.nParticle()
			<< token::SPACE << p.d()
			<< token::SPACE << p.dTarget()
			<< token::SPACE << p.U()
			<< token::SPACE << p.rho()
			<< token::SPACE << p.age()
			<< token::SPACE << p.tTurb()
			<< token::SPACE << p.UTurb();
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.active_),
			KinematicParcel<ParcelType>::sizeofFields_
		);
	}

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<(Ostream&, const KinematicParcel<ParcelType>&)"
	);

	return os;
}


// ************************************************************************* //

// .cxx
#include <forceSuSp.hxx>
#include <integrationScheme.hxx>
#include <meshTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::label tnbLib::KinematicParcel<ParcelType>::maxTrackAttempts = 1;


// * * * * * * * * * * *  Protected Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::setCellValues
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	tetIndices tetIs = this->currentTetIndices();

	td.rhoc() = td.rhoInterp().interpolate(this->coordinates(), tetIs);

	if (td.rhoc() < cloud.constProps().rhoMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed density in cell " << this->cell()
				<< " to " << cloud.constProps().rhoMin() << nl << endl;
		}

		td.rhoc() = cloud.constProps().rhoMin();
	}

	td.Uc() = td.UInterp().interpolate(this->coordinates(), tetIs);

	td.muc() = td.muInterp().interpolate(this->coordinates(), tetIs);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::calcDispersion
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() = cloud.dispersion().update
	(
		dt,
		this->cell(),
		U_,
		td.Uc(),
		UTurb_,
		tTurb_
	);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::cellValueSourceCorrection
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() += cloud.UTrans()[this->cell()] / massCell(td);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::calc
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	// Define local properties at beginning of time step
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const scalar np0 = nParticle_;
	const scalar mass0 = mass();

	// Reynolds number
	const scalar Re = this->Re(td);


	// Sources
	//~~~~~~~~

	// Explicit momentum source for particle
	vector Su = Zero;

	// Linearised momentum source coefficient
	scalar Spu = 0.0;

	// Momentum transfer from the particle to the carrier phase
	vector dUTrans = Zero;


	// Motion
	// ~~~~~~

	// Calculate new particle velocity
	this->U_ =
		calcVelocity(cloud, td, dt, Re, td.muc(), mass0, Su, dUTrans, Spu);


	// Accumulate carrier phase source terms
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (cloud.solution().coupled())
	{
		// Update momentum transfer
		cloud.UTrans()[this->cell()] += np0 * dUTrans;

		// Update momentum transfer coefficient
		cloud.UCoeff()[this->cell()] += np0 * Spu;
	}
}


template<class ParcelType>
template<class TrackCloudType>
const tnbLib::vector tnbLib::KinematicParcel<ParcelType>::calcVelocity
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar Re,
	const scalar mu,
	const scalar mass,
	const vector& Su,
	vector& dUTrans,
	scalar& Spu
) const
{
	const typename TrackCloudType::parcelType& p =
		static_cast<const typename TrackCloudType::parcelType&>(*this);
	typename TrackCloudType::parcelType::trackingData& ttd =
		static_cast<typename TrackCloudType::parcelType::trackingData&>(td);

	const typename TrackCloudType::forceType& forces = cloud.forces();

	// Momentum source due to particle forces
	const forceSuSp Fcp = forces.calcCoupled(p, ttd, dt, mass, Re, mu);
	const forceSuSp Fncp = forces.calcNonCoupled(p, ttd, dt, mass, Re, mu);
	const scalar massEff = forces.massEff(p, ttd, mass);

	/*
	// Proper splitting ...
	// Calculate the integration coefficients
	const vector acp = (Fcp.Sp()*td.Uc() + Fcp.Su())/massEff;
	const vector ancp = (Fncp.Sp()*td.Uc() + Fncp.Su() + Su)/massEff;
	const scalar bcp = Fcp.Sp()/massEff;
	const scalar bncp = Fncp.Sp()/massEff;

	// Integrate to find the new parcel velocity
	const vector deltaUcp =
		cloud.UIntegrator().partialDelta
		(
			U_, dt, acp + ancp, bcp + bncp, acp, bcp
		);
	const vector deltaUncp =
		cloud.UIntegrator().partialDelta
		(
			U_, dt, acp + ancp, bcp + bncp, ancp, bncp
		);
	const vector deltaT = deltaUcp + deltaUncp;
	*/

	// Shortcut splitting assuming no implicit non-coupled force ...
	// Calculate the integration coefficients
	const vector acp = (Fcp.Sp() * td.Uc() + Fcp.Su()) / massEff;
	const vector ancp = (Fncp.Su() + Su) / massEff;
	const scalar bcp = Fcp.Sp() / massEff;

	// Integrate to find the new parcel velocity
	const vector deltaU = cloud.UIntegrator().delta(U_, dt, acp + ancp, bcp);
	const vector deltaUncp = ancp * dt;
	const vector deltaUcp = deltaU - deltaUncp;

	// Calculate the new velocity and the momentum transfer terms
	vector Unew = U_ + deltaU;

	dUTrans -= massEff * deltaUcp;

	Spu = dt * Fcp.Sp();

	// Apply correction to velocity and dUTrans for reduced-D cases
	const polyMesh& mesh = cloud.pMesh();
	meshTools::constrainDirection(mesh, mesh.solutionD(), Unew);
	meshTools::constrainDirection(mesh, mesh.solutionD(), dUTrans);

	return Unew;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const KinematicParcel<ParcelType>& p
)
	:
	ParcelType(p),
	active_(p.active_),
	typeId_(p.typeId_),
	nParticle_(p.nParticle_),
	d_(p.d_),
	dTarget_(p.dTarget_),
	U_(p.U_),
	rho_(p.rho_),
	age_(p.age_),
	tTurb_(p.tTurb_),
	UTurb_(p.UTurb_)
{}


template<class ParcelType>
tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const KinematicParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	active_(p.active_),
	typeId_(p.typeId_),
	nParticle_(p.nParticle_),
	d_(p.d_),
	dTarget_(p.dTarget_),
	U_(p.U_),
	rho_(p.rho_),
	age_(p.age_),
	tTurb_(p.tTurb_),
	UTurb_(p.UTurb_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::KinematicParcel<ParcelType>::move
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar trackTime
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);
	typename TrackCloudType::parcelType::trackingData& ttd =
		static_cast<typename TrackCloudType::parcelType::trackingData&>(td);

	ttd.switchProcessor = false;
	ttd.keepParticle = true;

	const scalarField& cellLengthScale = cloud.cellLengthScale();
	const scalar maxCo = cloud.solution().maxCo();

	while (ttd.keepParticle && !ttd.switchProcessor && p.stepFraction() < 1)
	{
		// Cache the current position, cell and step-fraction
		const point start = p.position();
		const scalar sfrac = p.stepFraction();

		// Total displacement over the time-step
		const vector s = trackTime * U_;

		// Cell length scale
		const scalar l = cellLengthScale[p.cell()];

		// Deviation from the mesh centre for reduced-D cases
		const vector d = p.deviationFromMeshCentre();

		// Fraction of the displacement to track in this loop. This is limited
		// to ensure that the both the time and distance tracked is less than
		// maxCo times the total value.
		scalar f = 1 - p.stepFraction();
		f = min(f, maxCo);
		f = min(f, maxCo * l / max(small * l, mag(s)));
		if (p.active())
		{
			// Track to the next face
			p.trackToFace(f * s - d, f);
		}
		else
		{
			// At present the only thing that sets active_ to false is a stick
			// wall interaction. We want the position of the particle to remain
			// the same relative to the face that it is on. The local
			// coordinates therefore do not change. We still advance in time and
			// perform the relevant interactions with the fixed particle.
			p.stepFraction() += f;
		}

		const scalar dt = (p.stepFraction() - sfrac) * trackTime;

		// Avoid problems with extremely small timesteps
		if (dt > rootVSmall)
		{
			// Update cell based properties
			p.setCellValues(cloud, ttd);

			p.calcDispersion(cloud, ttd, dt);

			if (cloud.solution().cellValueSourceCorrection())
			{
				p.cellValueSourceCorrection(cloud, ttd, dt);
			}

			p.calc(cloud, ttd, dt);
		}

		p.age() += dt;

		if (p.active() && p.onFace())
		{
			cloud.functions().postFace(p, ttd.keepParticle);
		}

		cloud.functions().postMove(p, dt, start, ttd.keepParticle);

		if (p.active() && p.onFace() && ttd.keepParticle)
		{
			p.hitFace(f * s - d, f, cloud, ttd);
		}
	}

	return ttd.keepParticle;
}


template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::KinematicParcel<ParcelType>::hitPatch
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);

	const polyPatch& pp = p.mesh().boundaryMesh()[p.patch()];

	// Invoke post-processing model
	cloud.functions().postPatch(p, pp, td.keepParticle);

	// Invoke surface film model
	if (cloud.surfaceFilm().transferParcel(p, pp, td.keepParticle))
	{
		// All interactions done
		return true;
	}
	else if (pp.coupled())
	{
		// Don't apply the patchInteraction models to coupled boundaries
		return false;
	}
	else
	{
		// Invoke patch interaction model
		return cloud.patchInteraction().correct(p, pp, td.keepParticle);
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::hitProcessorPatch
(
	TrackCloudType&,
	trackingData& td
)
{
	td.switchProcessor = true;
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::hitWallPatch
(
	TrackCloudType&,
	trackingData&
)
{
	// wall interactions are handled by the generic hitPatch method
}


template<class ParcelType>
void tnbLib::KinematicParcel<ParcelType>::transformProperties(const tensor& T)
{
	ParcelType::transformProperties(T);

	U_ = transform(T, U_);
}


template<class ParcelType>
void tnbLib::KinematicParcel<ParcelType>::transformProperties
(
	const vector& separation
)
{
	ParcelType::transformProperties(separation);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

//#include <KinematicParcelIO.cxx>

// ************************************************************************* //