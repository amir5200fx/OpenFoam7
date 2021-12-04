#pragma once

#include <phaseSystem.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::IsothermalPhaseModel<BasePhaseModel>::IsothermalPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::IsothermalPhaseModel<BasePhaseModel>::~IsothermalPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
void tnbLib::IsothermalPhaseModel<BasePhaseModel>::correctThermo()
{
	BasePhaseModel::correctThermo();

	// Correct the thermo, but make sure that the temperature remains the same
	tmp<volScalarField> TCopy
	(
		volScalarField::New
		(
			this->thermo().T().name() + ":Copy",
			this->thermo().T()
		)
	);
	this->thermo_->he() = this->thermo().he(this->thermo().p(), TCopy);
	this->thermo_->correct();
	this->thermo_->T() = TCopy;
}


template<class BasePhaseModel>
bool tnbLib::IsothermalPhaseModel<BasePhaseModel>::isothermal() const
{
	return true;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::IsothermalPhaseModel<BasePhaseModel>::heEqn()
{
	FatalErrorInFunction
		<< "Cannot construct an energy equation for an isothermal phase"
		<< exit(FatalError);

	return tmp<fvScalarMatrix>();
}