#include <reducedUnits.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const  tnbLib::scalar tnbLib::reducedUnits::kb = 1.3806504e-23;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::reducedUnits::calcRefValues()
{
	if
		(
			refTime_ < vSmall
			|| refLength_ < vSmall
			|| refMass_ < vSmall
			)
	{
		FatalErrorInFunction
			<< "One of more referencence values too small for floating point "
			<< "calculation: "
			<< "refTime_ = " << refTime_
			<< ", refLength = " << refTemp_
			<< ", refMass = " << refMass_
			<< nl << abort(FatalError);
	}

	refEnergy_ = refLength_ * refLength_*refMass_ / (refTime_*refTime_);

	refTemp_ = refEnergy_ / kb;

	refForce_ = refEnergy_ / refLength_;

	refVelocity_ = tnbLib::sqrt(refEnergy_ / refMass_);

	refVolume_ = tnbLib::pow(refLength_, 3.0);

	refPressure_ = refEnergy_ / refVolume_;

	refMassDensity_ = refMass_ / refVolume_;

	refNumberDensity_ = 1.0 / refVolume_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::reducedUnits::reducedUnits()
	:
	refLength_(1e-9),
	refTime_(1e-12),
	refMass_(1.660538782e-27)
{
	calcRefValues();
}


tnbLib::reducedUnits::reducedUnits
(
	scalar refLength,
	scalar refTime,
	scalar refMass
)
	:
	refLength_(refLength),
	refTime_(refTime),
	refMass_(refMass)
{
	calcRefValues();
}


tnbLib::reducedUnits::reducedUnits(const IOdictionary& reducedUnitsDict)
	:
	refLength_(),
	refTime_(),
	refMass_()
{
	setRefValues(reducedUnitsDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::reducedUnits::~reducedUnits()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::reducedUnits::setRefValues
(
	scalar refLength,
	scalar refTime,
	scalar refMass
)
{
	refLength_ = refLength;

	refTime_ = refTime;

	refMass_ = refMass;

	calcRefValues();
}


void tnbLib::reducedUnits::setRefValues
(
	const IOdictionary& reducedUnitsDict
)
{
	refLength_ = readScalar(reducedUnitsDict.lookup("refLength"));

	refTime_ = readScalar(reducedUnitsDict.lookup("refTime"));

	refMass_ = readScalar(reducedUnitsDict.lookup("refMass"));

	calcRefValues();
}


// ************************************************************************* //