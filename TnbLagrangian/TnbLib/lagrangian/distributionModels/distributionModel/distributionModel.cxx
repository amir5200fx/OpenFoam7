#include <distributionModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(distributionModel, 0);
	defineRunTimeSelectionTable(distributionModel, dictionary);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::distributionModel::check() const
{
	if (minValue() < 0)
	{
		FatalErrorInFunction
			<< type() << "distribution: Minimum value must be greater than "
			<< "zero." << nl << "Supplied minValue = " << minValue()
			<< abort(FatalError);
	}

	if (maxValue() < minValue())
	{
		FatalErrorInFunction
			<< type() << "distribution: Maximum value is smaller than the "
			<< "minimum value:" << nl << "    maxValue = " << maxValue()
			<< ", minValue = " << minValue()
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::distributionModel::distributionModel
(
	const word& name,
	const dictionary& dict,
	Random& rndGen
)
	:
	distributionModelDict_(dict.subDict(name + "Distribution")),
	rndGen_(rndGen)
{}


tnbLib::distributionModel::distributionModel
(
	const distributionModel& p
)
	:
	distributionModelDict_(p.distributionModelDict_),
	rndGen_(p.rndGen_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::distributionModel::~distributionModel()
{}


// ************************************************************************* //