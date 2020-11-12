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
inline bool tnbLib::PairCollisionRecord<Type>::match
(
	label queryOrigProcOfOther,
	label queryOrigIdOfOther
) const
{
	return
		(
			queryOrigProcOfOther == origProcOfOther()
			&& queryOrigIdOfOther == origIdOfOther()
			);
}


template<class Type>
inline tnbLib::label tnbLib::PairCollisionRecord<Type>::origProcOfOther() const
{
	return mag(origProcOfOther_) - 1;
}


template<class Type>
inline tnbLib::label tnbLib::PairCollisionRecord<Type>::origIdOfOther() const
{
	return origIdOfOther_;
}


template<class Type>
inline const Type&
tnbLib::PairCollisionRecord<Type>::collisionData() const
{
	return data_;
}


template<class Type>
inline Type& tnbLib::PairCollisionRecord<Type>::collisionData()
{
	return data_;
}


template<class Type>
inline bool tnbLib::PairCollisionRecord<Type>::accessed() const
{
	return pos0(origProcOfOther_);
}


template<class Type>
inline void tnbLib::PairCollisionRecord<Type>::setAccessed()
{
	origProcOfOther_ = origProcOfOther() + 1;
}


template<class Type>
inline void tnbLib::PairCollisionRecord<Type>::setUnaccessed()
{
	origProcOfOther_ = -(origProcOfOther() + 1);
}


// * * * * * * * * * * * * * * Friend Operators * * * * * * * * * * * * * * //

template<class Type>
inline bool tnbLib::operator==
(
	const PairCollisionRecord<Type>& a,
	const PairCollisionRecord<Type>& b
	)
{
	return
		(
			a.origProcOfOther_ == b.origProcOfOther_
			&& a.origIdOfOther_ == b.origIdOfOther_
			&& a.data_ == b.data_
			);
}


template<class Type>
inline bool tnbLib::operator!=
(
	const PairCollisionRecord<Type>& a,
	const PairCollisionRecord<Type>& b
	)
{
	return !(a == b);
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::PairCollisionRecord<Type>::PairCollisionRecord(Istream& is)
	:
	origProcOfOther_(readLabel(is)),
	origIdOfOther_(readLabel(is)),
	data_(is)
{
	// Check state of Istream
	is.check
	(
		"tnbLib::PairCollisionRecord<Type>::PairCollisionRecord(tnbLib::Istream&)"
	);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Istream& tnbLib::operator>>(Istream& is, PairCollisionRecord<Type>& pCR)
{
	is >> pCR.origProcOfOther_ >> pCR.origIdOfOther_ >> pCR.data_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream&"
		"tnbLib::operator>>(tnbLib::Istream&, tnbLib::PairCollisionRecord<Type>&)"
	);

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const PairCollisionRecord<Type>& pCR
	)
{
	os << pCR.origProcOfOther_
		<< token::SPACE << pCR.origIdOfOther_
		<< token::SPACE << pCR.data_;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::PairCollisionRecord<Type>&)"
	);

	return os;
}


// ************************************************************************* //
// .cxx
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::PairCollisionRecord<Type>::PairCollisionRecord()
	:
	origProcOfOther_(0),
	origIdOfOther_(-1),
	data_(Zero)
{}


template<class Type>
tnbLib::PairCollisionRecord<Type>::PairCollisionRecord
(
	bool accessed,
	label origProcOfOther,
	label origIdOfOther,
	const Type& data
)
	:
	origProcOfOther_(origProcOfOther + 1),
	origIdOfOther_(origIdOfOther),
	data_(data)
{
	// Default assignment to origProcOfOther_ assumes accessed is true

	if (!accessed)
	{
		setUnaccessed();
	}
}


template<class Type>
tnbLib::PairCollisionRecord<Type>::PairCollisionRecord
(
	const PairCollisionRecord<Type>& pCR
)
	:
	origProcOfOther_(pCR.origProcOfOther_),
	origIdOfOther_(pCR.origIdOfOther_),
	data_(pCR.data_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::PairCollisionRecord<Type>::~PairCollisionRecord()
{}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::PairCollisionRecord<Type>::operator=
(
	const PairCollisionRecord<Type>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	origProcOfOther_ = rhs.origProcOfOther_;
	origIdOfOther_ = rhs.origIdOfOther_;
	data_ = rhs.data_;
}


// * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * * * //

//#include <PairCollisionRecordIO.cxx>


// ************************************************************************* //