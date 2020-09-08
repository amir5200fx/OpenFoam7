#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Specie, int PolySize>
	icoPolynomial<Specie, PolySize>::icoPolynomial(const dictionary& dict)
		:
		Specie(dict),
		rhoCoeffs_
		(
			dict.subDict("equationOfState").lookup
			(
				"rhoCoeffs<" + tnbLib::name(PolySize) + '>'
			)
		)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Specie, int PolySize>
	void icoPolynomial<Specie, PolySize>::write(Ostream& os) const
	{
		Specie::write(os);

		dictionary dict("equationOfState");
		dict.add
		(
			word("rhoCoeffs<" + tnbLib::name(PolySize) + '>'),
			rhoCoeffs_
		);

		os << indent << dict.dictName() << dict;
	}


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	template<class Specie, int PolySize>
	Ostream& operator<<(Ostream& os, const icoPolynomial<Specie, PolySize>& ip)
	{
		ip.write(os);
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //