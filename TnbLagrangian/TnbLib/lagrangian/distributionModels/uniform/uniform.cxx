#include <uniform.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		defineTypeNameAndDebug(uniform, 0);
		addToRunTimeSelectionTable(distributionModel, uniform, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModels::uniform::uniform
(
	const dictionary& dict,
	Random& rndGen
)
	:
	distributionModel(typeName, dict, rndGen),
	minValue_(readScalar(distributionModelDict_.lookup("minValue"))),
	maxValue_(readScalar(distributionModelDict_.lookup("maxValue")))
{
	check();
}


tnbLib::distributionModels::uniform::uniform(const uniform& p)
	:
	distributionModel(p),
	minValue_(p.minValue_),
	maxValue_(p.maxValue_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModels::uniform::~uniform()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::distributionModels::uniform::sample() const
{
	return rndGen_.scalarAB(minValue_, maxValue_);
}


tnbLib::scalar tnbLib::distributionModels::uniform::minValue() const
{
	return minValue_;
}


tnbLib::scalar tnbLib::distributionModels::uniform::maxValue() const
{
	return maxValue_;
}


tnbLib::scalar tnbLib::distributionModels::uniform::meanValue() const
{
	return 0.5*(minValue_ + maxValue_);
}


// ************************************************************************* //