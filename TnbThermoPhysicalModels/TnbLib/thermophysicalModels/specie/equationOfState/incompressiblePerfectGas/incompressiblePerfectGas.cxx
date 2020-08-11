#include <incompressiblePerfectGas.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::incompressiblePerfectGas<Specie>::incompressiblePerfectGas
(
	const dictionary& dict
)
	:
	Specie(dict),
	pRef_(readScalar(dict.subDict("equationOfState").lookup("pRef")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::incompressiblePerfectGas<Specie>::write(Ostream& os) const
{
	Specie::write(os);
	dictionary dict("equationOfState");
	dict.add("pRef", pRef_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const incompressiblePerfectGas<Specie>& pg
	)
{
	pg.write(os);
	return os;
}


// ************************************************************************* //