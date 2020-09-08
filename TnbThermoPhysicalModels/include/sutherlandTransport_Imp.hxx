#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Thermo>
tnbLib::scalar tnbLib::sutherlandTransport<Thermo>::readCoeff
(
	const word& coeffName,
	const dictionary& dict
)
{
	return readScalar(dict.subDict("transport").lookup(coeffName));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::sutherlandTransport<Thermo>::sutherlandTransport(const dictionary& dict)
	:
	Thermo(dict),
	As_(readCoeff("As", dict)),
	Ts_(readCoeff("Ts", dict))
{}


template<class Thermo>
tnbLib::sutherlandTransport<Thermo>::sutherlandTransport
(
	const Thermo& t,
	const dictionary& dict
)
	:
	Thermo(t),
	As_(readCoeff("As", dict)),
	Ts_(readCoeff("Ts", dict))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::sutherlandTransport<Thermo>::write(Ostream& os) const
{
	os << this->specie::name() << endl
		<< token::BEGIN_BLOCK << incrIndent << nl;

	Thermo::write(os);

	dictionary dict("transport");
	dict.add("As", As_);
	dict.add("Ts", Ts_);

	os << indent << dict.dictName() << dict
		<< decrIndent << token::END_BLOCK << nl;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const sutherlandTransport<Thermo>& st
	)
{
	st.write(os);
	return os;
}


// ************************************************************************* //