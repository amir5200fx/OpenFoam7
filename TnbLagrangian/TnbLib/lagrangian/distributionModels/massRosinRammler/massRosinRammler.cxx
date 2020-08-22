#include <massRosinRammler.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		defineTypeNameAndDebug(massRosinRammler, 0);
		addToRunTimeSelectionTable(distributionModel, massRosinRammler, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModels::massRosinRammler::massRosinRammler
(
	const dictionary& dict,
	Random& rndGen
)
	:
	distributionModel(typeName, dict, rndGen),
	minValue_(readScalar(distributionModelDict_.lookup("minValue"))),
	maxValue_(readScalar(distributionModelDict_.lookup("maxValue"))),
	d_(readScalar(distributionModelDict_.lookup("d"))),
	n_(readScalar(distributionModelDict_.lookup("n")))
{
	check();
}


tnbLib::distributionModels::massRosinRammler::massRosinRammler
(
	const massRosinRammler& p
)
	:
	distributionModel(p),
	minValue_(p.minValue_),
	maxValue_(p.maxValue_),
	d_(p.d_),
	n_(p.n_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModels::massRosinRammler::~massRosinRammler()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::distributionModels::massRosinRammler::sample() const
{
	scalar d;

	// Re-sample if the calculated d is out of the physical range
	do
	{
		const scalar a = 3 / n_ + 1;
		const scalar P = rndGen_.sample01<scalar>();
		const scalar x = invIncGamma(a, P);
		d = d_ * pow(x, 1 / n_);
	} while (d < minValue_ || d > maxValue_);

	return d;
}


tnbLib::scalar tnbLib::distributionModels::massRosinRammler::minValue() const
{
	return minValue_;
}


tnbLib::scalar tnbLib::distributionModels::massRosinRammler::maxValue() const
{
	return maxValue_;
}


tnbLib::scalar tnbLib::distributionModels::massRosinRammler::meanValue() const
{
	return d_;
}


// ************************************************************************* //