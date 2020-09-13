#pragma once
#include <fvc.hxx>
#include <fvm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::linearViscousStress<BasicTurbulenceModel>::linearViscousStress
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
	BasicTurbulenceModel
	(
		modelName,
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transport,
		propertiesName
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::linearViscousStress<BasicTurbulenceModel>::read()
{
	return BasicTurbulenceModel::read();
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::linearViscousStress<BasicTurbulenceModel>::devRhoReff() const
{
	return volSymmTensorField::New
	(
		IOobject::groupName("devRhoReff", this->alphaRhoPhi_.group()),
		(-(this->alpha_*this->rho_*this->nuEff()))
		*dev(twoSymm(fvc::grad(this->U_)))
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::linearViscousStress<BasicTurbulenceModel>::divDevRhoReff
(
	volVectorField& U
) const
{
	return
		(
			-fvc::div((this->alpha_*this->rho_*this->nuEff())*dev2(T(fvc::grad(U))))
			- fvm::laplacian(this->alpha_*this->rho_*this->nuEff(), U)
			);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::linearViscousStress<BasicTurbulenceModel>::divDevRhoReff
(
	const volScalarField& rho,
	volVectorField& U
) const
{
	return
		(
			-fvc::div((this->alpha_*rho*this->nuEff())*dev2(T(fvc::grad(U))))
			- fvm::laplacian(this->alpha_*rho*this->nuEff(), U)
			);
}


template<class BasicTurbulenceModel>
void tnbLib::linearViscousStress<BasicTurbulenceModel>::correct()
{
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //