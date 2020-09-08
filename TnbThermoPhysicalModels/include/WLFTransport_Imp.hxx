#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Thermo>
tnbLib::scalar tnbLib::WLFTransport<Thermo>::readCoeff
(
	const word& coeffName,
	const dictionary& dict
)
{
	return readScalar(dict.subDict("transport").lookup(coeffName));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::WLFTransport<Thermo>::WLFTransport(const dictionary& dict)
	:
	Thermo(dict),
	mu0_(readCoeff("mu0", dict)),
	Tr_(readCoeff("Tr", dict)),
	C1_(readCoeff("C1", dict)),
	C2_(readCoeff("C2", dict)),
	rPr_(1.0 / readScalar(dict.subDict("transport").lookup("Pr")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::WLFTransport<Thermo>::write(Ostream& os) const
{
	os << this->specie::name() << endl
		<< token::BEGIN_BLOCK << incrIndent << nl;

	Thermo::write(os);

	dictionary dict("transport");
	dict.add("mu0", mu0_);
	dict.add("Tr", Tr_);
	dict.add("C1", C1_);
	dict.add("C2", C2_);
	dict.add("Pr", 1.0 / rPr_);

	os << indent << dict.dictName() << dict
		<< decrIndent << token::END_BLOCK << nl;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const WLFTransport<Thermo>& wlft
	)
{
	wlft.write(os);
	return os;
}


// ************************************************************************* //