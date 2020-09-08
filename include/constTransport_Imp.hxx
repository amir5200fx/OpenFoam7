#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::constTransport<Thermo>::constTransport(const dictionary& dict)
	:
	Thermo(dict),
	mu_(readScalar(dict.subDict("transport").lookup("mu"))),
	rPr_(1.0 / readScalar(dict.subDict("transport").lookup("Pr")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::constTransport<Thermo>::constTransport::write(Ostream& os) const
{
	os << this->name() << endl;
	os << token::BEGIN_BLOCK << incrIndent << nl;

	Thermo::write(os);

	dictionary dict("transport");
	dict.add("mu", mu_);
	dict.add("Pr", 1.0 / rPr_);
	os << indent << dict.dictName() << dict;

	os << decrIndent << token::END_BLOCK << nl;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const constTransport<Thermo>& ct)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //