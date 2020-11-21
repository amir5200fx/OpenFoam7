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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline bool tnbLib::WallCollisionRecord<Type>::match
(
	const vector& pRel,
	scalar radius
)
{
	scalar magpRel_ = mag(pRel_);

	scalar magpRel = mag(pRel);

	// Using the new data as the acceptance criterion
	scalar cosAcceptanceAngle = magpRel / radius;

	if (cosAcceptanceAngle > errorCosAngle)
	{
		Info << "pRel_ " << pRel_ << " " << magpRel_ << nl
			<< "pRel " << pRel << " " << magpRel << nl
			<< "unit vector dot product " << (pRel & pRel_) / (magpRel_*magpRel)
			<< nl << "cosAcceptanceAngle " << cosAcceptanceAngle
			<< endl;

		FatalErrorInFunction
			<< "Problem with matching WallCollisionRecord." << nl
			<< "The given radius, " << radius << ", is smaller than distance "
			<< "to the relative position of the WallInteractionSite, "
			<< magpRel << nl
			<< abort(FatalError);
	}

	// Are the test and recorded pRel (relative position vectors)
	// aligned to within the calculated tolerance?
	bool matched = (pRel & pRel_) / (magpRel_*magpRel) > cosAcceptanceAngle;

	if (matched)
	{
		pRel_ = pRel;
	}

	return matched;
}


template<class Type>
inline const tnbLib::vector&
tnbLib::WallCollisionRecord<Type>::pRel() const
{
	return pRel_;
}


template<class Type>
inline const Type&
tnbLib::WallCollisionRecord<Type>::collisionData() const
{
	return data_;
}


template<class Type>
inline Type& tnbLib::WallCollisionRecord<Type>::collisionData()
{
	return data_;
}


template<class Type>
inline bool tnbLib::WallCollisionRecord<Type>::accessed() const
{
	return accessed_;
}


template<class Type>
inline void tnbLib::WallCollisionRecord<Type>::setAccessed()
{
	accessed_ = true;
}


template<class Type>
inline void tnbLib::WallCollisionRecord<Type>::setUnaccessed()
{
	accessed_ = false;
}


// * * * * * * * * * * * * * * Friend Operators * * * * * * * * * * * * * * //

template<class Type>
inline bool tnbLib::operator==
(
	const WallCollisionRecord<Type>& a,
	const WallCollisionRecord<Type>& b
	)
{
	return
		(
			a.accessed_ == b.accessed_
			&& a.pRel_ == b.pRel_
			&& a.data_ == b.data_
			);
}


template<class Type>
inline bool tnbLib::operator!=
(
	const WallCollisionRecord<Type>& a,
	const WallCollisionRecord<Type>& b
	)
{
	return !(a == b);
}


// ************************************************************************* //

// IO.cxx
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
// .cxx
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::scalar tnbLib::WallCollisionRecord<Type>::errorCosAngle(1.0 + 1e-6);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord()
	:
	accessed_(false),
	pRel_(),
	data_(Zero)
{}


template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord
(
	bool accessed,
	const vector& pRel,
	const Type& data
)
	:
	accessed_(accessed),
	pRel_(pRel),
	data_(data)
{}


template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord
(
	const WallCollisionRecord<Type>& wCR
)
	:
	accessed_(wCR.accessed_),
	pRel_(wCR.pRel_),
	data_(wCR.data_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallCollisionRecord<Type>::~WallCollisionRecord()
{}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::WallCollisionRecord<Type>::operator=
(
	const WallCollisionRecord<Type>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	accessed_ = rhs.accessed_;
	pRel_ = rhs.pRel_;
	data_ = rhs.data_;
}


// * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * * * //

//#include <WallCollisionRecordIO.cxx>


// ************************************************************************* //