#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::constAnIsoSolidTransport<Thermo>::constAnIsoSolidTransport
(
	const dictionary& dict
)
	:
	Thermo(dict),
	kappa_(dict.subDict("transport").lookup("kappa"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::constAnIsoSolidTransport<Thermo>::constAnIsoSolidTransport::write
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
	const constAnIsoSolidTransport<Thermo>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //