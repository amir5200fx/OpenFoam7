#include <coupledFvPatch.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coupledFvPatch, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::coupledFvPatch::~coupledFvPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::vectorField> tnbLib::coupledFvPatch::delta() const
{
	return Cf() - Cn();
}


// ************************************************************************* //