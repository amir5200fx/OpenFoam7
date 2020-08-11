#include <NSRDSfunc6.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc6, 0);
	addToRunTimeSelectionTable(thermophysicalFunction, NSRDSfunc6, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc6::NSRDSfunc6
(
	const scalar Tc,
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d,
	const scalar e
)
	:
	Tc_(Tc),
	a_(a),
	b_(b),
	c_(c),
	d_(d),
	e_(e)
{}


tnbLib::NSRDSfunc6::NSRDSfunc6(const dictionary& dict)
	:
	Tc_(readScalar(dict.lookup("Tc"))),
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d"))),
	e_(readScalar(dict.lookup("e")))
{}


// ************************************************************************* //