#include <polynomialSolidTransport.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::polynomialSolidTransport<Thermo, PolySize>::polynomialSolidTransport
(
	const dictionary& dict
)
	:
	Thermo(dict),
	kappaCoeffs_
	(
		dict.subDict("transport").lookup
		(
			"kappaCoeffs<" + tnbLib::name(PolySize) + '>'
		)
	)
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
void tnbLib::polynomialSolidTransport<Thermo, PolySize>::write(Ostream& os) const
{
	Thermo::write(os);

	dictionary dict("transport");

	dict.add
	(
		word("kappaCoeffs<" + tnbLib::name(PolySize) + '>'),
		kappaCoeffs_
	);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const polynomialSolidTransport<Thermo, PolySize>& pt
	)
{
	pt.write(os);
	return os;
}


// ************************************************************************* //