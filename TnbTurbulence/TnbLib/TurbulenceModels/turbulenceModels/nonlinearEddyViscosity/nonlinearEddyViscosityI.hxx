#pragma once
#include <fvc.hxx>
#include <fvm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::nonlinearEddyViscosity<BasicTurbulenceModel>::nonlinearEddyViscosity
(
	const word& modelName,
	const alphaField& alpha,
	const rhoField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	eddyViscosity<BasicTurbulenceModel>
	(
		modelName,
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transport,
		propertiesName
		),

	nonlinearStress_
	(
		IOobject
		(
			IOobject::groupName("nonlinearStress", alphaRhoPhi.group()),
			this->runTime_.timeName(),
			this->mesh_
		),
		this->mesh_,
		dimensionedSymmTensor
		(
			"nonlinearStress",
			sqr(dimVelocity),
			Zero
		)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::nonlinearEddyViscosity<BasicTurbulenceModel>::R() const
{
	tmp<volSymmTensorField> tR
	(
		eddyViscosity<BasicTurbulenceModel>::R()
	);
	tR.ref() += nonlinearStress_;
	return tR;
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::nonlinearEddyViscosity<BasicTurbulenceModel>::devRhoReff() const
{
	tmp<volSymmTensorField> tdevRhoReff
	(
		eddyViscosity<BasicTurbulenceModel>::devRhoReff()
	);
	tdevRhoReff.ref() += this->rho_*nonlinearStress_;
	return tdevRhoReff;
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::nonlinearEddyViscosity<BasicTurbulenceModel>::divDevRhoReff
(
	volVectorField& U
) const
{
	return
		(
			fvc::div(this->rho_*nonlinearStress_)
			+ eddyViscosity<BasicTurbulenceModel>::divDevRhoReff(U)
			);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::nonlinearEddyViscosity<BasicTurbulenceModel>::divDevRhoReff
(
	const volScalarField& rho,
	volVectorField& U
) const
{
	return
		(
			fvc::div(rho*nonlinearStress_)
			+ eddyViscosity<BasicTurbulenceModel>::divDevRhoReff(rho, U)
			);
}


// ************************************************************************* //