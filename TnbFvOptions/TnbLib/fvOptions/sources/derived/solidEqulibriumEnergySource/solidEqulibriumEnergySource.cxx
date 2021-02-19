#include <solidEqulibriumEnergySource.hxx>

#include <fvmDdt.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(solidEqulibriumEnergySource, 0);
		addToRunTimeSelectionTable
		(
			option,
			solidEqulibriumEnergySource,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::volScalarField& tnbLib::fv::solidEqulibriumEnergySource::alpha() const
{
	const word alphaName = IOobject::groupName("alpha", phaseName_);

	if (!mesh_.foundObject<volScalarField>(alphaName))
	{
		volScalarField* alphaPtr =
			new volScalarField
			(
				IOobject
				(
					alphaName,
					mesh_.time().constant(),
					mesh_,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				mesh_
			);

		alphaPtr->store();
	}

	return mesh_.lookupObject<volScalarField>(alphaName);
}


const tnbLib::solidThermo& tnbLib::fv::solidEqulibriumEnergySource::thermo() const
{
	const word thermoName =
		IOobject::groupName(basicThermo::dictName, phaseName_);

	if (!mesh_.foundObject<solidThermo>(thermoName))
	{
		solidThermo* thermoPtr = solidThermo::New(mesh_, phaseName_).ptr();

		thermoPtr->store();
	}

	return mesh_.lookupObject<solidThermo>(thermoName);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::solidEqulibriumEnergySource::solidEqulibriumEnergySource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(name, modelType, dict, mesh),
	phaseName_(dict.lookupType<word>("phase"))
{
	read(dict);
	alpha();
	thermo();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::solidEqulibriumEnergySource::~solidEqulibriumEnergySource()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::fv::solidEqulibriumEnergySource::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	const volScalarField alphahe(thermo().alphahe());

	const volScalarField& A = this->alpha();
	const volScalarField B(1 - A);

	eqn -=
		A / B * fvm::ddt(thermo().rho(), eqn.psi());
	-1 / B * fvm::laplacian
	(
		A*alphahe,
		eqn.psi(),
		"laplacian(" + alphahe.name() + "," + eqn.psi().name() + ")"
	);
}


void tnbLib::fv::solidEqulibriumEnergySource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	const volScalarField alphahe(alpha*thermo().alphahe());

	const volScalarField& A = this->alpha();
	const volScalarField B(1 - A);

	eqn -=
		A / B * fvm::ddt(alpha, thermo().rho(), eqn.psi());
	-1 / B * fvm::laplacian
	(
		A*alphahe,
		eqn.psi(),
		"laplacian(" + alphahe.name() + "," + eqn.psi().name() + ")"
	);
}


bool tnbLib::fv::solidEqulibriumEnergySource::read(const dictionary& dict)
{
	if (option::read(dict))
	{
		fieldNames_ = wordList(1, coeffs_.lookupType<word>("field"));

		applied_.setSize(fieldNames_.size(), false);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //