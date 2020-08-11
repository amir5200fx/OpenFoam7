#include <APIdiffCoefFunc.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(APIdiffCoefFunc, 0);
	addToRunTimeSelectionTable
	(
		thermophysicalFunction,
		APIdiffCoefFunc,
		dictionary
	);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::APIdiffCoefFunc::APIdiffCoefFunc
(
	const scalar a,
	const scalar b,
	const scalar wf,
	const scalar wa
)
	:
	a_(a),
	b_(b),
	wf_(wf),
	wa_(wa),
	alpha_(sqrt(1 / wf_ + 1 / wa_)),
	beta_(sqr(cbrt(a_) + cbrt(b_)))
{}


tnbLib::APIdiffCoefFunc::APIdiffCoefFunc(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	wf_(readScalar(dict.lookup("wf"))),
	wa_(readScalar(dict.lookup("wa"))),
	alpha_(sqrt(1 / wf_ + 1 / wa_)),
	beta_(sqr((cbrt(a_) + cbrt(b_))))
{}


// ************************************************************************* //