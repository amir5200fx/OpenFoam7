#include <NSRDSfunc14.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(NSRDSfunc14, 0);
	addToRunTimeSelectionTable
	(
		thermophysicalFunction,
		NSRDSfunc14,
		dictionary
	);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::NSRDSfunc14::NSRDSfunc14
(
	const scalar Tc,
	const scalar a,
	const scalar b,
	const scalar c,
	const scalar d
)
	:
	Tc_(Tc),
	a_(a),
	b_(b),
	c_(c),
	d_(d)
{}


tnbLib::NSRDSfunc14::NSRDSfunc14(const dictionary& dict)
	:
	Tc_(readScalar(dict.lookup("Tc"))),
	a_(readScalar(dict.lookup("a"))),
	b_(readScalar(dict.lookup("b"))),
	c_(readScalar(dict.lookup("c"))),
	d_(readScalar(dict.lookup("d")))
{}


// ************************************************************************* //