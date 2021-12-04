#pragma once

#include <phaseSystem.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseModel>
tnbLib::InertPhaseModel<BasePhaseModel>::InertPhaseModel
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
tnbLib::InertPhaseModel<BasePhaseModel>::~InertPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::InertPhaseModel<BasePhaseModel>::R
(
	volScalarField& Yi
) const
{
	return tmp<fvScalarMatrix>
		(
			new fvScalarMatrix(Yi, dimMass / dimTime)
			);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InertPhaseModel<BasePhaseModel>::Qdot() const
{
	return volScalarField::New
	(
		IOobject::groupName("Qdot", this->name()),
		this->mesh(),
		dimensionedScalar(dimEnergy / dimTime / dimVolume, 0)
	);
}