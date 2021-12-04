#pragma once

#include <phaseSystem.hxx>
#include <fvMatrix.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseModel, class ReactionType>
tnbLib::ReactingPhaseModel<BasePhaseModel, ReactionType>::ReactingPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index),
	reaction_(ReactionType::New(this->thermo_(), this->turbulence_()))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel, class ReactionType>
tnbLib::ReactingPhaseModel<BasePhaseModel, ReactionType>::~ReactingPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel, class ReactionType>
void tnbLib::ReactingPhaseModel<BasePhaseModel, ReactionType>::correctThermo()
{
	BasePhaseModel::correctThermo();

	reaction_->correct();
}


template<class BasePhaseModel, class ReactionType>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::ReactingPhaseModel<BasePhaseModel, ReactionType>::R
(
	volScalarField& Yi
) const
{
	return reaction_->R(Yi);
}


template<class BasePhaseModel, class ReactionType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ReactingPhaseModel<BasePhaseModel, ReactionType>::Qdot() const
{
	return reaction_->Qdot();
}
