#include <moleFractionsFunctionObjects.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebugWithName
	(
		psiReactionThermoMoleFractionsFunctionObject,
		"psiReactionThermoMoleFractions",
		0
	);

	addToRunTimeSelectionTable
	(
		functionObject,
		psiReactionThermoMoleFractionsFunctionObject,
		dictionary
	);

	defineTemplateTypeNameAndDebugWithName
	(
		rhoReactionThermoMoleFractionsFunctionObject,
		"rhoReactionThermoMoleFractions",
		0
	);

	addToRunTimeSelectionTable
	(
		functionObject,
		rhoReactionThermoMoleFractionsFunctionObject,
		dictionary
	);
}


// ************************************************************************* //