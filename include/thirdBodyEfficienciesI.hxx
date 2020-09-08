#pragma once
#include <Tuple2.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::thirdBodyEfficiencies::thirdBodyEfficiencies
(
	const speciesTable& species,
	const scalarList& efficiencies
)
	:
	scalarList(efficiencies),
	species_(species)
{
	if (size() != species_.size())
	{
		FatalErrorInFunction
			<< "number of efficiencies = " << size()
			<< " is not equal to the number of species " << species_.size()
			<< exit(FatalError);
	}
}


inline tnbLib::thirdBodyEfficiencies::thirdBodyEfficiencies
(
	const speciesTable& species,
	const dictionary& dict
)
	:
	scalarList(species.size()),
	species_(species)
{
	if (dict.found("coeffs"))
	{
		List<Tuple2<word, scalar>> coeffs(dict.lookup("coeffs"));
		if (coeffs.size() != species_.size())
		{
			FatalErrorInFunction
				<< "number of efficiencies = " << coeffs.size()
				<< " is not equat to the number of species " << species_.size()
				<< exit(FatalIOError);
		}

		forAll(coeffs, i)
		{
			operator[](species[coeffs[i].first()]) = coeffs[i].second();
		}
	}
	else
	{
		scalar defaultEff = readScalar(dict.lookup("defaultEfficiency"));
		scalarList::operator=(defaultEff);
	}
}


// * * * * * * * * * * * * * * * Member functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::thirdBodyEfficiencies::M(const scalarList& c) const
{
	scalar M = 0;
	forAll(*this, i)
	{
		M += operator[](i)*c[i];
	}

	return M;
}


inline void tnbLib::thirdBodyEfficiencies::write(Ostream& os) const
{
	List<Tuple2<word, scalar>> coeffs(species_.size());
	forAll(coeffs, i)
	{
		coeffs[i].first() = species_[i];
		coeffs[i].second() = operator[](i);
	}

	writeEntry(os, "coeffs", coeffs);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const thirdBodyEfficiencies& tbes
	)
{
	tbes.write(os);
	return os;
}


// ************************************************************************* //