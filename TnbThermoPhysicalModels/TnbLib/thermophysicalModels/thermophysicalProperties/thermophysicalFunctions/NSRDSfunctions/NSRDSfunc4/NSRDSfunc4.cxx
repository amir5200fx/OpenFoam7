#include <NSRDSfunc4.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc4, 0);
	addToRunTimeSelectionTable(thermophysicalFunction, NSRDSfunc4, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc4::NSRDSfunc4
(
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d,
	const scalar e
)
	:
	a_(a),
	b_(b),
	c_(c),
	d_(d),
	e_(e)
{}


tnbLib::NSRDSfunc4::NSRDSfunc4(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d"))),
	e_(readScalar(dict.lookup("e")))
{}


// ************************************************************************* //