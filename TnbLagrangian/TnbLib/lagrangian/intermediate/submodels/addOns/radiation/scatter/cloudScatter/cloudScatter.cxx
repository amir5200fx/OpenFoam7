#include <cloudScatter.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <thermoCloud.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace scatterModels
		{
			defineTypeNameAndDebug(cloud, 0);

			addToRunTimeSelectionTable
			(
				scatterModel,
				cloud,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::cloud::cloud
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	scatterModel(dict, mesh),
	coeffsDict_(dict.subDict(typeName + "Coeffs")),
	cloudNames_(coeffsDict_.lookup("cloudNames"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::scatterModels::cloud::~cloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::scatterModels::cloud::sigmaEff() const
{
	tmp<volScalarField> tsigma
	(
		volScalarField::New
		(
			"sigma",
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

		tsigma.ref() += tc.sigmap();
	}

	return 3.0*tsigma;
}


// ************************************************************************* //