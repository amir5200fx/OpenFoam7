#include <cloudAbsorptionEmission.hxx>

#include <thermoCloud.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(cloud, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				cloud,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::cloud::cloud
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	absorptionEmissionModel(dict, mesh),
	coeffsDict_(dict.subDict(typeName + "Coeffs")),
	cloudNames_(coeffsDict_.lookup("cloudNames"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::cloud::~cloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::cloud::aDisp(const label) const
{
	tmp<volScalarField> ta
	(
		volScalarField::New
		(
			"a",
			mesh_,
			dimensionedScalar(dimless / dimLength, 0)
		)
	);

	forAll(cloudNames_, i)
	{
		const thermoCloud& tc
		(
			mesh_.objectRegistry::lookupObject<thermoCloud>(cloudNames_[i])
		);

		ta.ref() += tc.ap();
	}

	return ta;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::cloud::eDisp
(
	const label bandI
) const
{
	tmp<volScalarField> te
	(
		volScalarField::New
		(
			"e",
			mesh_,
			dimensionedScalar(dimless / dimLength, 0)
		)
	);

	return te;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::cloud::EDisp
(
	const label bandI
) const
{
	tmp<volScalarField> tE
	(
		volScalarField::New
		(
			"E",
			mesh_,
			dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
		)
	);

	forAll(cloudNames_, i)
	{
		const thermoCloud& tc
		(
			mesh_.objectRegistry::lookupObject<thermoCloud>(cloudNames_[i])
		);

		tE.ref() += tc.Ep();
	}

	// Total emission is 4 times the projected emission
	return 4 * tE;
}


// ************************************************************************* //