#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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
inline tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const polyMesh& owner,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(owner, coordinates, celli, tetFacei, tetPti),
	UCorrect_(Zero)
{}


template<class ParcelType>
inline tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const polyMesh& owner,
	const vector& position,
	const label celli
)
	:
	ParcelType(owner, position, celli),
	UCorrect_(Zero)
{}


template<class ParcelType>
inline tnbLib::MPPICParcel<ParcelType>::MPPICParcel
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
	const vector& UCorrect0,
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
	UCorrect_(UCorrect0)
{}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::vector& tnbLib::MPPICParcel<ParcelType>::UCorrect() const
{
	return UCorrect_;
}


template<class ParcelType>
inline tnbLib::vector& tnbLib::MPPICParcel<ParcelType>::UCorrect()
{
	return UCorrect_;
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>
#include <IOField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::MPPICParcel<ParcelType>::propertyList_ =
tnbLib::MPPICParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::MPPICParcel<ParcelType>::sizeofFields_
(
	sizeof(MPPICParcel<ParcelType>) - sizeof(ParcelType)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	UCorrect_(Zero)
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			is >> UCorrect_;
		}
		else
		{
			is.read(reinterpret_cast<char*>(&UCorrect_), sizeofFields_);
		}
	}

	is.check
	(
		"MPPICParcel<ParcelType>::Collisions"
		"(const polyMesh&, Istream&, bool)"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::MPPICParcel<ParcelType>::readFields(CloudType& c)
{
	bool valid = c.size();

	ParcelType::readFields(c);

	IOField<vector> UCorrect
	(
		c.fieldIOobject("UCorrect", IOobject::MUST_READ),
		valid
	);
	c.checkFieldIOobject(c, UCorrect);

	label i = 0;

	forAllIter(typename CloudType, c, iter)
	{
		MPPICParcel<ParcelType>& p = iter();

		p.UCorrect_ = UCorrect[i];

		i++;
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::MPPICParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);

	label np = c.size();

	IOField<vector>
		UCorrect(c.fieldIOobject("UCorrect", IOobject::NO_READ), np);

	label i = 0;

	forAllConstIter(typename CloudType, c, iter)
	{
		const MPPICParcel<ParcelType>& p = iter();

		UCorrect[i] = p.UCorrect();

		i++;
	}

	UCorrect.write(np > 0);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const MPPICParcel<ParcelType>& p
	)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << p.UCorrect();
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.UCorrect_),
			MPPICParcel<ParcelType>::sizeofFields_
		);
	}

	os.check
	(
		"Ostream& operator<<(Ostream&, const MPPICParcel<ParcelType>&)"
	);

	return os;
}


// ************************************************************************* //

// .cxx

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const MPPICParcel<ParcelType>& p
)
	:
	ParcelType(p),
	UCorrect_(p.UCorrect_)
{}


template<class ParcelType>
tnbLib::MPPICParcel<ParcelType>::MPPICParcel
(
	const MPPICParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	UCorrect_(p.UCorrect_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::MPPICParcel<ParcelType>::move
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
	case trackingData::tpLinearTrack:
	{
		ParcelType::move(cloud, td, trackTime);

		break;
	}
	case trackingData::tpDampingNoTrack:
	{
		p.UCorrect() =
			cloud.dampingModel().velocityCorrection(p, trackTime);

		td.keepParticle = true;
		td.switchProcessor = false;

		break;
	}
	case trackingData::tpPackingNoTrack:
	{
		p.UCorrect() =
			cloud.packingModel().velocityCorrection(p, trackTime);

		td.keepParticle = true;
		td.switchProcessor = false;

		break;
	}
	case trackingData::tpCorrectTrack:
	{
		const scalar f = p.stepFraction();
		const scalar a = p.age();

		Swap(p.U(), p.UCorrect());

		ParcelType::move(cloud, td, trackTime);

		Swap(p.U(), p.UCorrect());

		p.U() += (p.stepFraction() - f) * p.UCorrect();

		p.age() = a;

		break;
	}
	}

	return td.keepParticle;
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

//#include <MPPICParcelIO.cxx>

// ************************************************************************* //