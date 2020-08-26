#include <absolute.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
	namespace CorrectionLimitingMethods
	{
		defineTypeNameAndDebug(absolute, 0);

		addToRunTimeSelectionTable
		(
			CorrectionLimitingMethod,
			absolute,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::absolute::absolute(const dictionary& dict)
	:
	CorrectionLimitingMethod(dict),
	e_(readScalar(dict.lookup("e")))
{}


tnbLib::CorrectionLimitingMethods::absolute::absolute(const absolute& cl)
	:
	CorrectionLimitingMethod(cl),
	e_(cl.e_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::absolute::~absolute()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::vector tnbLib::CorrectionLimitingMethods::absolute::limitedVelocity
(
	const vector uP,
	const vector dU,
	const vector uMean
) const
{
	const vector uRelative = uP - uMean;

	return minMod
	(
		dU,
		-(1.0 + this->e_)*uRelative
		*mag(uP) / max(mag(uRelative), small)
	);
}


// ************************************************************************* //