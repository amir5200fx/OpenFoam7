#include <fixedValue.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace distributionModels
	{
		defineTypeNameAndDebug(fixedValue, 0);
		addToRunTimeSelectionTable(distributionModel, fixedValue, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModels::fixedValue::fixedValue
(
	const dictionary& dict,
	Random& rndGen
)
	:
	distributionModel(typeName, dict, rndGen),
	value_(readScalar(distributionModelDict_.lookup("value")))
{}


tnbLib::distributionModels::fixedValue::fixedValue(const fixedValue& p)
	:
	distributionModel(p),
	value_(p.value_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModels::fixedValue::~fixedValue()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::distributionModels::fixedValue::fixedValue::sample() const
{
	return value_;
}


tnbLib::scalar tnbLib::distributionModels::fixedValue::fixedValue::minValue() const
{
	return value_;
}


tnbLib::scalar tnbLib::distributionModels::fixedValue::fixedValue::maxValue() const
{
	return value_;
}


tnbLib::scalar tnbLib::distributionModels::fixedValue::fixedValue::meanValue() const
{
	return value_;
}


// ************************************************************************* //