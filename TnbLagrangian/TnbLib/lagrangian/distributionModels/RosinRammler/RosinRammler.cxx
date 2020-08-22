#include <RosinRammler.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		defineTypeNameAndDebug(RosinRammler, 0);
		addToRunTimeSelectionTable(distributionModel, RosinRammler, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModels::RosinRammler::RosinRammler
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


tnbLib::distributionModels::RosinRammler::RosinRammler(const RosinRammler& p)
	:
	distributionModel(p),
	minValue_(p.minValue_),
	maxValue_(p.maxValue_),
	d_(p.d_),
	n_(p.n_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModels::RosinRammler::~RosinRammler()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::distributionModels::RosinRammler::sample() const
{
	scalar K = 1.0 - exp(-pow((maxValue_ - minValue_) / d_, n_));
	scalar y = rndGen_.sample01<scalar>();
	scalar x = minValue_ + d_ * ::pow(-log(1.0 - y * K), 1.0 / n_);
	return x;
}


tnbLib::scalar tnbLib::distributionModels::RosinRammler::minValue() const
{
	return minValue_;
}


tnbLib::scalar tnbLib::distributionModels::RosinRammler::maxValue() const
{
	return maxValue_;
}


tnbLib::scalar tnbLib::distributionModels::RosinRammler::meanValue() const
{
	return d_;
}


// ************************************************************************* //