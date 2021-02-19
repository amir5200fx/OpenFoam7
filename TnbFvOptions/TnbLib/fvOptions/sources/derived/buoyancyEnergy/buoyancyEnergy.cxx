#include <buoyancyEnergy.hxx>

#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(buoyancyEnergy, 0);

		addToRunTimeSelectionTable
		(
			option,
			buoyancyEnergy,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::buoyancyEnergy::buoyancyEnergy
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(sourceName, modelType, dict, mesh),
	UName_(coeffs_.lookupOrDefault<word>("U", "U"))
{
	coeffs_.lookup("fields") >> fieldNames_;

	if (fieldNames_.size() != 1)
	{
		FatalErrorInFunction
			<< "settings are:" << fieldNames_ << exit(FatalError);
	}

	applied_.setSize(fieldNames_.size(), false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::buoyancyEnergy::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	const uniformDimensionedVectorField& g =
		mesh_.lookupObject<uniformDimensionedVectorField>("g");

	const volVectorField& U = mesh_.lookupObject<volVectorField>(UName_);

	eqn += rho * (U&g);
}


// ************************************************************************* //