#include <relaxationRateFlameAreaModels.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvm.hxx>
#include <LESModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace reactionRateFlameAreaModels
	{
		defineTypeNameAndDebug(relaxation, 0);
		addToRunTimeSelectionTable
		(
			reactionRateFlameArea,
			relaxation,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::reactionRateFlameAreaModels::relaxation::relaxation
(
	const word modelType,
	const dictionary& dict,
	const fvMesh& mesh,
	const combustionModel& combModel
)
	:
	reactionRateFlameArea(modelType, dict, mesh, combModel),
	correlation_(dict.optionalSubDict(typeName + "Coeffs").subDict(fuel_)),
	C_(readScalar(dict.optionalSubDict(typeName + "Coeffs").lookup("C"))),
	alpha_
	(
		readScalar(dict.optionalSubDict(typeName + "Coeffs").lookup("alpha"))
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::reactionRateFlameAreaModels::relaxation::~relaxation()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::reactionRateFlameAreaModels::relaxation::correct
(
	const volScalarField& sigma
)
{
	dimensionedScalar omega0
	(
		"omega0",
		dimensionSet(1, -2, -1, 0, 0, 0, 0),
		correlation_.omega0()
	);

	dimensionedScalar sigmaExt
	(
		"sigmaExt",
		dimensionSet(0, 0, -1, 0, 0, 0, 0),
		correlation_.sigmaExt()
	);

	dimensionedScalar omegaMin
	(
		"omegaMin",
		omega0.dimensions(),
		1e-4
	);

	dimensionedScalar kMin
	(
		"kMin",
		sqr(dimVelocity),
		small
	);

	const compressibleTurbulenceModel& turbulence = combModel_.turbulence();

	// Total strain
	const volScalarField sigmaTotal
	(
		sigma + alpha_ * turbulence.epsilon() / (turbulence.k() + kMin)
	);

	const volScalarField omegaInf(correlation_.omega0Sigma(sigmaTotal));

	dimensionedScalar sigma0("sigma0", sigma.dimensions(), 0.0);

	const volScalarField tau(C_*mag(sigmaTotal));

	volScalarField Rc
	(
		(tau*omegaInf*(omega0 - omegaInf) + sqr(omegaMin)*sigmaExt)
		/ (sqr(omega0 - omegaInf) + sqr(omegaMin))
	);

	const volScalarField& rho = combModel_.rho();
	const tmp<surfaceScalarField> tphi = combModel_.phi();
	const surfaceScalarField& phi = tphi();

	solve
	(
		fvm::ddt(rho, omega_)
		+ fvm::div(phi, omega_)
		==
		rho * Rc*omega0
		- fvm::SuSp(rho*(tau + Rc), omega_)
	);

	omega_.min(omega0);
	omega_.max(0.0);
}


bool  tnbLib::reactionRateFlameAreaModels::relaxation::read
(
	const dictionary& dict
)
{
	if (reactionRateFlameArea::read(dict))
	{
		coeffDict_ = dict.optionalSubDict(typeName + "Coeffs");
		coeffDict_.lookup("C") >> C_;
		coeffDict_.lookup("alpha") >> alpha_;
		correlation_.read
		(
			coeffDict_.subDict(fuel_)
		);
		return true;
	}
	else
	{
		return false;
	}
}

// ************************************************************************* //