#include <NSRDSfunc3.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc3, 0);
	addToRunTimeSelectionTable(thermophysicalFunction, NSRDSfunc3, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc3::NSRDSfunc3
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


tnbLib::NSRDSfunc3::NSRDSfunc3(const dictionary& dict)
	:
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d")))
{}


// ************************************************************************* //