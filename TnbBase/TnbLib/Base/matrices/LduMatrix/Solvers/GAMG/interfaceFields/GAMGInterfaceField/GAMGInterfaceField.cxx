#include <GAMGInterfaceField.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGInterfaceField, 0);
	defineRunTimeSelectionTable(GAMGInterfaceField, lduInterface);
	defineRunTimeSelectionTable(GAMGInterfaceField, lduInterfaceField);
}

// ************************************************************************* //