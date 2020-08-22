#include <exponential.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		defineTypeNameAndDebug(exponential, 0);
		addToRunTimeSelectionTable(distributionModel, exponential, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModels::exponential::exponential
(
	const dictionary& dict,
	Random& rndGen
)
	:
	distributionModel(typeName, dict, rndGen),
	minValue_(readScalar(distributionModelDict_.lookup("minValue"))),
	maxValue_(readScalar(distributionModelDict_.lookup("maxValue"))),
	lambda_(readScalar(distributionModelDict_.lookup("lambda")))
{
	check();
}


tnbLib::distributionModels::exponential::exponential(const exponential& p)
	:
	distributionModel(p),
	minValue_(p.minValue_),
	maxValue_(p.maxValue_),
	lambda_(p.lambda_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModels::exponential::~exponential()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::distributionModels::exponential::sample() const
{
	scalar y = rndGen_.sample01<scalar>();
	scalar K = exp(-lambda_ * maxValue_) - exp(-lambda_ * minValue_);
	return -(1.0 / lambda_)*log(exp(-lambda_ * minValue_) + y * K);
}


tnbLib::scalar tnbLib::distributionModels::exponential::minValue() const
{
	return minValue_;
}


tnbLib::scalar tnbLib::distributionModels::exponential::maxValue() const
{
	return maxValue_;
}


tnbLib::scalar tnbLib::distributionModels::exponential::meanValue() const
{
	return 1.0 / lambda_;
}


// ************************************************************************* //