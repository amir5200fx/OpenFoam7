#include <buoyancyForce.hxx>

#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(buoyancyForce, 0);

		addToRunTimeSelectionTable
		(
			option,
			buoyancyForce,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::buoyancyForce::buoyancyForce
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(sourceName, modelType, dict, mesh),
	g_
	(
		IOobject
		(
			"g",
			mesh.time().constant(),
			mesh,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	)
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

void tnbLib::fv::buoyancyForce::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	eqn += g_;
}


void tnbLib::fv::buoyancyForce::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	eqn += rho * g_;
}


// ************************************************************************* //