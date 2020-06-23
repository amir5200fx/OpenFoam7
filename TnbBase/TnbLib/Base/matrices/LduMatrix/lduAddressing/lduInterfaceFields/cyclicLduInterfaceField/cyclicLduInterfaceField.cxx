#include <cyclicLduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicLduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicLduInterfaceField::~cyclicLduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicLduInterfaceField::transformCoupleField
(
	scalarField& f,
	const direction cmpt
) const
{
	if (doTransform())
	{
		if (forwardT().size() == 1)
		{
			f *= pow(diag(forwardT()[0]).component(cmpt), rank());
		}
		else
		{
			f *= pow(diag(forwardT())().component(cmpt), rank());
		}
	}
}


// ************************************************************************* //