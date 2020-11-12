#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::constantProperties::
constantProperties()
	:
	ParcelType::constantProperties(),
	youngsModulus_(this->dict_, 0.0),
	poissonsRatio_(this->dict_, 0.0)
{}


template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::constantProperties::constantProperties
(
	const constantProperties& cp
)
	:
	ParcelType::constantProperties(cp),
	youngsModulus_(cp.youngsModulus_),
	poissonsRatio_(cp.poissonsRatio_)
{}


template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::constantProperties::constantProperties
(
	const dictionary& parentDict
)
	:
	ParcelType::constantProperties(parentDict),
	youngsModulus_(this->dict_, "youngsModulus"),
	poissonsRatio_(this->dict_, "poissonsRatio")
{}


template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::CollidingParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	f_(Zero),
	angularMomentum_(Zero),
	torque_(Zero),
	collisionRecords_()
{}


template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::CollidingParcel
(
	const polyMesh& owner,
	const vector& position,
	const label celli
)
	:
	ParcelType(owner, position, celli),
	f_(Zero),
	angularMomentum_(Zero),
	torque_(Zero),
	collisionRecords_()
{}


template<class ParcelType>
inline tnbLib::CollidingParcel<ParcelType>::CollidingParcel
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
	const vector& f0,
	const vector& angularMomentum0,
	const vector& torque0,
	const typename ParcelType::constantProperties& constProps
)
	:
	ParcelType
	(
		owner,
		coordinates,
		celli,
		tetFacei,
		tetPti,
		typeId,
		nParticle0,
		d0,
		dTarget0,
		U0,
		constProps
	),
	f_(f0),
	angularMomentum_(angularMomentum0),
	torque_(torque0),
	collisionRecords_()
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::scalar
tnbLib::CollidingParcel<ParcelType>::constantProperties::youngsModulus() const
{
	return youngsModulus_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::CollidingParcel<ParcelType>::constantProperties::poissonsRatio() const
{
	return poissonsRatio_.value();
}


// * * * * * * * * * * CollidingParcel Member Functions  * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::vector& tnbLib::CollidingParcel<ParcelType>::f() const
{
	return f_;
}


template<class ParcelType>
inline const tnbLib::vector&
tnbLib::CollidingParcel<ParcelType>::angularMomentum() const
{
	return angularMomentum_;
}


template<class ParcelType>
inline const tnbLib::vector& tnbLib::CollidingParcel<ParcelType>::torque() const
{
	return torque_;
}


template<class ParcelType>
inline const tnbLib::collisionRecordList&
tnbLib::CollidingParcel<ParcelType>::collisionRecords() const
{
	return collisionRecords_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::CollidingParcel<ParcelType>::f()
{
	return f_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::CollidingParcel<ParcelType>::angularMomentum()
{
	return angularMomentum_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::CollidingParcel<ParcelType>::torque()
{
	return torque_;
}


template<class ParcelType>
inline tnbLib::collisionRecordList&
tnbLib::CollidingParcel<ParcelType>::collisionRecords()
{
	return collisionRecords_;
}


template<class ParcelType>
inline tnbLib::vector tnbLib::CollidingParcel<ParcelType>::omega() const
{
	return angularMomentum_ / this->momentOfInertia();
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>
#include <IOField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::CollidingParcel<ParcelType>::propertyList_ =
tnbLib::CollidingParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::CollidingParcel<ParcelType>::sizeofFields_
(
	offsetof(CollidingParcel<ParcelType>, collisionRecords_)
	- offsetof(CollidingParcel<ParcelType>, f_)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::CollidingParcel<ParcelType>::CollidingParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	f_(Zero),
	angularMomentum_(Zero),
	torque_(Zero),
	collisionRecords_()
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			is >> f_;
			is >> angularMomentum_;
			is >> torque_;
		}
		else
		{
			is.read(reinterpret_cast<char*>(&f_), sizeofFields_);
		}

		is >> collisionRecords_;
	}

	// Check state of Istream
	is.check
	(
		"CollidingParcel<ParcelType>::Collisions"
		"(const polyMesh&, Istream&, bool)"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::CollidingParcel<ParcelType>::readFields(CloudType& c)
{
	bool write = c.size();

	ParcelType::readFields(c);

	IOField<vector> f(c.fieldIOobject("f", IOobject::MUST_READ), write);
	c.checkFieldIOobject(c, f);

	IOField<vector> angularMomentum
	(
		c.fieldIOobject("angularMomentum", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, angularMomentum);

	IOField<vector> torque
	(
		c.fieldIOobject("torque", IOobject::MUST_READ),
		write
	);
	c.checkFieldIOobject(c, torque);

	labelFieldCompactIOField collisionRecordsPairAccessed
	(
		c.fieldIOobject("collisionRecordsPairAccessed", IOobject::MUST_READ),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsPairAccessed);

	labelFieldCompactIOField collisionRecordsPairOrigProcOfOther
	(
		c.fieldIOobject
		(
			"collisionRecordsPairOrigProcOfOther",
			IOobject::MUST_READ
		),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsPairOrigProcOfOther);

	labelFieldCompactIOField collisionRecordsPairOrigIdOfOther
	(
		c.fieldIOobject
		(
			"collisionRecordsPairOrigIdOfOther",
			IOobject::MUST_READ
		),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsPairOrigProcOfOther);

	pairDataFieldCompactIOField collisionRecordsPairData
	(
		c.fieldIOobject("collisionRecordsPairData", IOobject::MUST_READ),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsPairData);

	labelFieldCompactIOField collisionRecordsWallAccessed
	(
		c.fieldIOobject("collisionRecordsWallAccessed", IOobject::MUST_READ),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsWallAccessed);

	vectorFieldCompactIOField collisionRecordsWallPRel
	(
		c.fieldIOobject("collisionRecordsWallPRel", IOobject::MUST_READ),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsWallPRel);

	wallDataFieldCompactIOField collisionRecordsWallData
	(
		c.fieldIOobject("collisionRecordsWallData", IOobject::MUST_READ),
		write
	);
	c.checkFieldFieldIOobject(c, collisionRecordsWallData);

	label i = 0;

	forAllIter(typename CloudType, c, iter)
	{
		CollidingParcel<ParcelType>& p = iter();

		p.f_ = f[i];
		p.angularMomentum_ = angularMomentum[i];
		p.torque_ = torque[i];

		p.collisionRecords_ = collisionRecordList
		(
			collisionRecordsPairAccessed[i],
			collisionRecordsPairOrigProcOfOther[i],
			collisionRecordsPairOrigIdOfOther[i],
			collisionRecordsPairData[i],
			collisionRecordsWallAccessed[i],
			collisionRecordsWallPRel[i],
			collisionRecordsWallData[i]
		);

		i++;
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::CollidingParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);

	label np = c.size();

	IOField<vector> f(c.fieldIOobject("f", IOobject::NO_READ), np);
	IOField<vector> angularMomentum
	(
		c.fieldIOobject("angularMomentum", IOobject::NO_READ),
		np
	);
	IOField<vector> torque(c.fieldIOobject("torque", IOobject::NO_READ), np);

	labelFieldCompactIOField collisionRecordsPairAccessed
	(
		c.fieldIOobject("collisionRecordsPairAccessed", IOobject::NO_READ),
		np
	);
	labelFieldCompactIOField collisionRecordsPairOrigProcOfOther
	(
		c.fieldIOobject
		(
			"collisionRecordsPairOrigProcOfOther",
			IOobject::NO_READ
		),
		np
	);
	labelFieldCompactIOField collisionRecordsPairOrigIdOfOther
	(
		c.fieldIOobject("collisionRecordsPairOrigIdOfOther", IOobject::NO_READ),
		np
	);
	pairDataFieldCompactIOField collisionRecordsPairData
	(
		c.fieldIOobject("collisionRecordsPairData", IOobject::NO_READ),
		np
	);
	labelFieldCompactIOField collisionRecordsWallAccessed
	(
		c.fieldIOobject("collisionRecordsWallAccessed", IOobject::NO_READ),
		np
	);
	vectorFieldCompactIOField collisionRecordsWallPRel
	(
		c.fieldIOobject("collisionRecordsWallPRel", IOobject::NO_READ),
		np
	);
	wallDataFieldCompactIOField collisionRecordsWallData
	(
		c.fieldIOobject("collisionRecordsWallData", IOobject::NO_READ),
		np
	);

	label i = 0;

	forAllConstIter(typename CloudType, c, iter)
	{
		const CollidingParcel<ParcelType>& p = iter();

		f[i] = p.f();
		angularMomentum[i] = p.angularMomentum();
		torque[i] = p.torque();

		collisionRecordsPairAccessed[i] = p.collisionRecords().pairAccessed();
		collisionRecordsPairOrigProcOfOther[i] =
			p.collisionRecords().pairOrigProcOfOther();
		collisionRecordsPairOrigIdOfOther[i] =
			p.collisionRecords().pairOrigIdOfOther();
		collisionRecordsPairData[i] = p.collisionRecords().pairData();
		collisionRecordsWallAccessed[i] = p.collisionRecords().wallAccessed();
		collisionRecordsWallPRel[i] = p.collisionRecords().wallPRel();
		collisionRecordsWallData[i] = p.collisionRecords().wallData();

		i++;
	}

	const bool write = (np > 0);

	f.write(write);
	angularMomentum.write(write);
	torque.write(write);

	collisionRecordsPairAccessed.write(write);
	collisionRecordsPairOrigProcOfOther.write(write);
	collisionRecordsPairOrigIdOfOther.write(write);
	collisionRecordsPairData.write(write);
	collisionRecordsWallAccessed.write(write);
	collisionRecordsWallPRel.write(write);
	collisionRecordsWallData.write(write);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CollidingParcel<ParcelType>& p
	)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << p.f_
			<< token::SPACE << p.angularMomentum_
			<< token::SPACE << p.torque_
			<< token::SPACE << p.collisionRecords_;
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.f_),
			CollidingParcel<ParcelType>::sizeofFields_
		);
		os << p.collisionRecords();
	}

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<(Ostream&, const CollidingParcel<ParcelType>&)"
	);

	return os;
}


// ************************************************************************* //

// .cxx
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::CollidingParcel<ParcelType>::CollidingParcel
(
	const CollidingParcel<ParcelType>& p
)
	:
	ParcelType(p),
	f_(p.f_),
	angularMomentum_(p.angularMomentum_),
	torque_(p.torque_),
	collisionRecords_(p.collisionRecords_)
{}


template<class ParcelType>
tnbLib::CollidingParcel<ParcelType>::CollidingParcel
(
	const CollidingParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	f_(p.f_),
	angularMomentum_(p.angularMomentum_),
	torque_(p.torque_),
	collisionRecords_(p.collisionRecords_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::CollidingParcel<ParcelType>::move
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar trackTime
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);

	switch (td.part())
	{
	case trackingData::tpVelocityHalfStep:
	{
		// First and last leapfrog velocity adjust part, required
		// before and after tracking and force calculation

		p.U() += 0.5 * trackTime * p.f() / p.mass();

		p.angularMomentum() += 0.5 * trackTime * p.torque();

		td.keepParticle = true;
		td.switchProcessor = false;

		break;
	}

	case trackingData::tpLinearTrack:
	{
		ParcelType::move(cloud, td, trackTime);

		break;
	}

	case trackingData::tpRotationalTrack:
	{
		NotImplemented;

		break;
	}

	default:
	{
		FatalErrorInFunction
			<< td.part() << " is an invalid part of the tracking method."
			<< abort(FatalError);
	}
	}

	return td.keepParticle;
}


template<class ParcelType>
void tnbLib::CollidingParcel<ParcelType>::transformProperties(const tensor& T)
{
	ParcelType::transformProperties(T);

	f_ = transform(T, f_);

	angularMomentum_ = transform(T, angularMomentum_);

	torque_ = transform(T, torque_);
}


template<class ParcelType>
void tnbLib::CollidingParcel<ParcelType>::transformProperties
(
	const vector& separation
)
{
	ParcelType::transformProperties(separation);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

//#include <CollidingParcelIO.cxx>

// ************************************************************************* //