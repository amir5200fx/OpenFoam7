#include <exponentialSolidTransport.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo>
tnbLib::exponentialSolidTransport<Thermo>::exponentialSolidTransport
(
	const dictionary& dict
)
	:
	Thermo(dict),
	kappa0_(0.0),
	n0_(0.0),
	Tref_(0.0)
{
	const dictionary& subDict = dict.subDict("transport");
	kappa0_ = readScalar(subDict.lookup("kappa0"));
	n0_ = readScalar(subDict.lookup("n0"));
	Tref_ = readScalar(subDict.lookup("Tref"));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo>
void tnbLib::exponentialSolidTransport<Thermo>::exponentialSolidTransport::write
(
	Ostream& os
) const
{
	Thermo::write(os);

	dictionary dict("transport");
	dict.add("kappa0", kappa0_);
	dict.add("n0", n0_);
	dict.add("Tref", Tref_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os, const exponentialSolidTransport<Thermo>& et
	)
{
	et.write(os);
	return os;
}


// ************************************************************************* //