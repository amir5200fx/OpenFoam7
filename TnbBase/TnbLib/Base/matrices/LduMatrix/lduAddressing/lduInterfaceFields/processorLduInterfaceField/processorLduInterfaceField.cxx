#include <processorLduInterfaceField.hxx>

#include <diagTensorField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorLduInterfaceField, 0);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::processorLduInterfaceField::~processorLduInterfaceField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::processorLduInterfaceField::transformCoupleField
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