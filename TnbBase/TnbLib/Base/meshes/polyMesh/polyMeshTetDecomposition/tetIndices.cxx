#include <tetIndices.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tetIndices::tetIndices()
	:
	celli_(-1),
	facei_(-1),
	tetPti_(-1)
{}


tnbLib::tetIndices::tetIndices
(
	label celli,
	label facei,
	label tetPtI
)
	:
	celli_(celli),
	facei_(facei),
	tetPti_(tetPtI)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::tetIndices::~tetIndices()
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, tetIndices& tI)
{
	is >> tI.cell() >> tI.face() >> tI.tetPt();

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>(tnbLib::Istream&, tnbLib::tetIndices&)"
	);

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const tetIndices& tI)
{
	os << tI.cell() << token::SPACE
		<< tI.face() << token::SPACE
		<< tI.tetPt() << token::SPACE
		<< endl;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::tetIndices&)"
	);

	return os;
}


// ************************************************************************* //