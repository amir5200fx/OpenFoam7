#include <specie.hxx>

#include <constants.hxx>

/* * * * * * * * * * * * * * * public constants  * * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(specie, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::specie::specie(const dictionary& dict)
	:
	name_(dict.dictName()),
	Y_(dict.subDict("specie").lookupOrDefault("massFraction", 1.0)),
	molWeight_(readScalar(dict.subDict("specie").lookup("molWeight")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::specie::write(Ostream& os) const
{
	dictionary dict("specie");
	if (Y_ != 1)
	{
		dict.add("massFraction", Y_);
	}
	dict.add("molWeight", molWeight_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const specie& st)
{
	st.write(os);
	os.check("Ostream& operator<<(Ostream& os, const specie& st)");
	return os;
}


// ************************************************************************* //