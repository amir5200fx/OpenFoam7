#include <polynomialTransport.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::polynomialTransport<Thermo, PolySize>::polynomialTransport
(
	const dictionary& dict
)
	:
	Thermo(dict),
	muCoeffs_
	(
		dict.subDict("transport").lookup
		(
			"muCoeffs<" + tnbLib::name(PolySize) + '>'
		)
	),
	kappaCoeffs_
	(
		dict.subDict("transport").lookup
		(
			"kappaCoeffs<" + tnbLib::name(PolySize) + '>'
		)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, int PolySize>
void tnbLib::polynomialTransport<Thermo, PolySize>::write(Ostream& os) const
{
	os << this->name() << endl;
	os << token::BEGIN_BLOCK << incrIndent << nl;

	Thermo::write(os);

	dictionary dict("transport");
	dict.add
	(
		word("muCoeffs<" + tnbLib::name(PolySize) + '>'),
		muCoeffs_
	);
	dict.add
	(
		word("kappaCoeffs<" + tnbLib::name(PolySize) + '>'),
		kappaCoeffs_
	);
	os << indent << dict.dictName() << dict;

	os << decrIndent << token::END_BLOCK << nl;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Thermo, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const polynomialTransport<Thermo, PolySize>& pt
	)
{
	pt.write(os);
	return os;
}


// ************************************************************************* //