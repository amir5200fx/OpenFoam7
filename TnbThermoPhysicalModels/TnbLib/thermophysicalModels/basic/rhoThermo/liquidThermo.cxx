#include <liquidThermo.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

	defineTemplateTypeNameAndDebugWithName
	(
		heRhoThermopureMixtureliquidProperties,
		"heRhoThermo<pureMixture<liquid,sensibleInternalEnergy>>",
		0
	);

	addToRunTimeSelectionTable
	(
		basicThermo,
		heRhoThermopureMixtureliquidProperties,
		fvMesh
	);

	addToRunTimeSelectionTable
	(
		fluidThermo,
		heRhoThermopureMixtureliquidProperties,
		fvMesh
	);

	addToRunTimeSelectionTable
	(
		rhoThermo,
		heRhoThermopureMixtureliquidProperties,
		fvMesh
	);


	defineTemplateTypeNameAndDebugWithName
	(
		heRhoThermopureMixtureEnthalpyliquidProperties,
		"heRhoThermo<pureMixture<liquid,sensibleEnthalpy>>",
		0
	);

	addToRunTimeSelectionTable
	(
		basicThermo,
		heRhoThermopureMixtureEnthalpyliquidProperties,
		fvMesh
	);

	addToRunTimeSelectionTable
	(
		fluidThermo,
		heRhoThermopureMixtureEnthalpyliquidProperties,
		fvMesh
	);

	addToRunTimeSelectionTable
	(
		rhoThermo,
		heRhoThermopureMixtureEnthalpyliquidProperties,
		fvMesh
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //