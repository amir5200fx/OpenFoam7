#include <radiation.hxx>

#include <fluidThermo.hxx>
#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(radiation, 0);

		addToRunTimeSelectionTable
		(
			option,
			radiation,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::radiation::radiation
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(sourceName, modelType, dict, mesh)
{
	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>(basicThermo::dictName);

	fieldNames_.setSize(1);
	fieldNames_[0] = thermo.he().name();
	applied_.setSize(fieldNames_.size(), false);

	radiation_ = radiationModel::New(thermo.T());
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::radiation::read(const dictionary& dict)
{
	return option::read(dict);
}


void tnbLib::fv::radiation::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>(basicThermo::dictName);

	radiation_->correct();

	eqn += radiation_->Sh(thermo, eqn.psi());
}


// ************************************************************************* //