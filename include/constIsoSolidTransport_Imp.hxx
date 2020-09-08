#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::constIsoSolidTransport<Thermo>::constIsoSolidTransport
(
	const dictionary& dict
)
	:
	Thermo(dict),
	kappa_(readScalar(dict.subDict("transport").lookup("kappa")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::constIsoSolidTransport<Thermo>::constIsoSolidTransport::write
(
	Ostream& os
) const
{
	Thermo::write(os);

	dictionary dict("transport");
	dict.add("kappa", kappa_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const constIsoSolidTransport<Thermo>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //