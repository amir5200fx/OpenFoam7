#pragma once

#include <phaseSystem.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmSup.hxx>
#include <fvmLaplacian.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseModel, class ThermoType>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::ThermoPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index),
	thermo_(ThermoType::New(fluid.mesh(), this->name()))
{
	thermo_->validate
	(
		IOobject::groupName(phaseModel::typeName, this->name()),
		"h",
		"e"
	);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ThermoType>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::~ThermoPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel, class ThermoType>
bool tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::compressible() const
{
	return !thermo_().incompressible();
}


template<class BasePhaseModel, class ThermoType>
const tnbLib::rhoThermo&
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::thermo() const
{
	return thermo_();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::rhoThermo&
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::thermoRef()
{
	return thermo_();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::rho() const
{
	return thermo_->rho();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::mu() const
{
	return thermo_->mu();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::mu
(
	const label patchi
) const
{
	return thermo_->mu(patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::nu() const
{
	return thermo_->nu();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::nu
(
	const label patchi
) const
{
	return thermo_->nu(patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::kappa() const
{
	return thermo_->kappa();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::kappa
(
	const label patchi
) const
{
	return thermo_->kappa(patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alphahe() const
{
	return thermo_->alphahe();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alphahe
(
	const label patchi
) const
{
	return thermo_->alphahe(patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::kappaEff
(
	const volScalarField& alphat
) const
{
	return thermo_->kappaEff(alphat);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::kappaEff
(
	const scalarField& alphat,
	const label patchi
) const
{
	return thermo_->kappaEff(alphat, patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alpha() const
{
	return thermo_->alpha();
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alpha
(
	const label patchi
) const
{
	return thermo_->alpha(patchi);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alphaEff
(
	const volScalarField& alphat
) const
{
	return thermo_->alphaEff(alphat);
}


template<class BasePhaseModel, class ThermoType>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermoPhaseModel<BasePhaseModel, ThermoType>::alphaEff
(
	const scalarField& alphat,
	const label patchi
) const
{
	return thermo_->alphaEff(alphat, patchi);
}