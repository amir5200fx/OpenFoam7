#include <NSRDSfunc2.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc2, 0);
	addToRunTimeSelectionTable(thermophysicalFunction, NSRDSfunc2, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc2::NSRDSfunc2
(
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d
)
	:
	a_(a),
	b_(b),
	c_(c),
	d_(d)
{}


tnbLib::NSRDSfunc2::NSRDSfunc2(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d")))
{}


// ************************************************************************* //