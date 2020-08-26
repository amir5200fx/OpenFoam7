#include <P1.hxx>

#include <fvmLaplacian.hxx>
#include <fvmSup.hxx>
#include <absorptionEmissionModel.hxx>
#include <scatterModel.hxx>
#include <constants.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		defineTypeNameAndDebug(P1, 0);
		addToRadiationRunTimeSelectionTables(P1);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::P1::P1(const volScalarField& T)
	:
	radiationModel(typeName, T),
	G_
	(
		IOobject
		(
			"G",
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh_
	),
	qr_
	(
		IOobject
		(
			"qr",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	a_
	(
		IOobject
		(
			"a",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	),
	e_
	(
		IOobject
		(
			"e",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	),
	E_
	(
		IOobject
		(
			"E",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	)
{}


tnbLib::radiationModels::P1::P1(const dictionary& dict, const volScalarField& T)
	:
	radiationModel(typeName, dict, T),
	G_
	(
		IOobject
		(
			"G",
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh_
	),
	qr_
	(
		IOobject
		(
			"qr",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	a_
	(
		IOobject
		(
			"a",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	),
	e_
	(
		IOobject
		(
			"e",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	),
	E_
	(
		IOobject
		(
			"E",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::P1::~P1()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::radiationModels::P1::read()
{
	if (radiationModel::read())
	{
		// nothing to read

		return true;
	}
	else
	{
		return false;
	}
}


void tnbLib::radiationModels::P1::calculate()
{
	a_ = absorptionEmission_->a();
	e_ = absorptionEmission_->e();
	E_ = absorptionEmission_->E();
	const volScalarField sigmaEff(scatter_->sigmaEff());

	const dimensionedScalar a0("a0", a_.dimensions(), rootVSmall);

	// Construct diffusion
	const volScalarField gamma
	(
		IOobject
		(
			"gammaRad",
			G_.mesh().time().timeName(),
			G_.mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		1.0 / (3.0*a_ + sigmaEff + a0)
	);

	// Solve G transport equation
	solve
	(
		fvm::laplacian(gamma, G_)
		- fvm::Sp(a_, G_)
		==
		-4.0*(e_*physicoChemical::sigma*pow4(T_)) - E_
	);

	volScalarField::Boundary& qrBf = qr_.boundaryFieldRef();

	// Calculate radiative heat flux on boundaries.
	forAll(mesh_.boundaryMesh(), patchi)
	{
		if (!G_.boundaryField()[patchi].coupled())
		{
			qrBf[patchi] =
				-gamma.boundaryField()[patchi]
				* G_.boundaryField()[patchi].snGrad();
		}
	}
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::radiationModels::P1::Rp() const
{
	return volScalarField::New
	(
		"Rp",
		4.0*absorptionEmission_->eCont()*physicoChemical::sigma
	);
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::radiationModels::P1::Ru() const
{
	const volScalarField::Internal& G =
		G_();
	const volScalarField::Internal E =
		absorptionEmission_->ECont()()();
	const volScalarField::Internal a =
		absorptionEmission_->aCont()()();

	return a * G - E;
}


// ************************************************************************* //