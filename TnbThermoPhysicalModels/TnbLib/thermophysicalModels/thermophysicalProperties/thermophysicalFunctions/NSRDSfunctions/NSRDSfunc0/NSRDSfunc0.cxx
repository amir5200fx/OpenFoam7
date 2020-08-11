#include <NSRDSfunc0.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc0, 0);
	addToRunTimeSelectionTable(thermophysicalFunction, NSRDSfunc0, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc0::NSRDSfunc0
(
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d,
	const scalar e,
	const scalar f
)
	:
	a_(a),
	b_(b),
	c_(c),
	d_(d),
	e_(e),
	f_(f)
{}


tnbLib::NSRDSfunc0::NSRDSfunc0(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d"))),
	e_(readScalar(dict.lookup("e"))),
	f_(readScalar(dict.lookup("f")))
{}


// ************************************************************************* //