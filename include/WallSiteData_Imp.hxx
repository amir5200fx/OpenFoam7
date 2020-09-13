#pragma once
#include <Istream.hxx>  // added by amir
#include <Ostream.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallSiteData<Type>::WallSiteData()
	:
	patchi_(),
	wallData_()
{}


template<class Type>
tnbLib::WallSiteData<Type>::WallSiteData
(
	label patchi,
	const Type& wallData
)
	:
	patchi_(patchi),
	wallData_(wallData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallSiteData<Type>::~WallSiteData()
{}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::WallSiteData<Type>::operator==
(
	const WallSiteData<Type>& rhs
	) const
{
	return patchi_ == rhs.patchi_ && wallData_ == rhs.wallData_;
}


template<class Type>
bool tnbLib::WallSiteData<Type>::operator!=
(
	const WallSiteData<Type>& rhs
	) const
{
	return !(*this == rhs);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	WallSiteData<Type>& wIS
	)
{
	is >> wIS.patchi_ >> wIS.wallData_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>"
		"(tnbLib::Istream&, tnbLib::WallSiteData<Type>&)"
	);

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const WallSiteData<Type>& wIS
	)
{
	os << wIS.patchi_ << token::SPACE << wIS.wallData_;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<"
		"(Ostream&, const WallSiteData<Type>&)"
	);

	return os;
}


// ************************************************************************* //