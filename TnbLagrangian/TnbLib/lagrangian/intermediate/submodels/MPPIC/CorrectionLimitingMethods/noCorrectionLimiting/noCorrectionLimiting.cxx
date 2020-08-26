#include <noCorrectionLimiting.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
	namespace CorrectionLimitingMethods
	{
		defineTypeNameAndDebug(noCorrectionLimiting, 0);

		addToRunTimeSelectionTable
		(
			CorrectionLimitingMethod,
			noCorrectionLimiting,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::noCorrectionLimiting::noCorrectionLimiting
(
	const dictionary& dict
)
	:
	CorrectionLimitingMethod(dict)
{}


tnbLib::CorrectionLimitingMethods::noCorrectionLimiting::noCorrectionLimiting
(
	const noCorrectionLimiting& cl
)
	:
	CorrectionLimitingMethod(cl)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::noCorrectionLimiting::~noCorrectionLimiting()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::vector
tnbLib::CorrectionLimitingMethods::noCorrectionLimiting::limitedVelocity
(
	const vector uP,
	const vector dU,
	const vector uMean
) const
{
	return dU;
}


// ************************************************************************* //