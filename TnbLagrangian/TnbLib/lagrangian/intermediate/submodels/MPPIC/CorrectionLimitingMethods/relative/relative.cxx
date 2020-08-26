#include <relative.hxx>

#include <addToRunTimeSelectionTable.hxx>

namespace tnbLib
{
	namespace CorrectionLimitingMethods
	{
		defineTypeNameAndDebug(relative, 0);

		addToRunTimeSelectionTable
		(
			CorrectionLimitingMethod,
			relative,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::relative::relative(const dictionary& dict)
	:
	CorrectionLimitingMethod(dict),
	e_(readScalar(dict.lookup("e")))
{}


tnbLib::CorrectionLimitingMethods::relative::relative(const relative& cl)
	:
	CorrectionLimitingMethod(cl),
	e_(cl.e_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::CorrectionLimitingMethods::relative::~relative()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::vector tnbLib::CorrectionLimitingMethods::relative::limitedVelocity
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
	);
}


// ************************************************************************* //