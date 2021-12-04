#pragma once

#include <fvmSup.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::OneResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
OneResistanceHeatTransferPhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh)
{
	this->generatePairsAndSubModels
	(
		"heatTransfer",
		heatTransferModels_,
		false
	);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::OneResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
~OneResistanceHeatTransferPhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::heatTransferTable>
tnbLib::OneResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
heatTransfer() const
{
	autoPtr<phaseSystem::heatTransferTable> eqnsPtr
	(
		new phaseSystem::heatTransferTable()
	);

	phaseSystem::heatTransferTable& eqns = eqnsPtr();

	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		eqns.insert
		(
			phase.name(),
			new fvScalarMatrix(phase.thermo().he(), dimEnergy / dimTime)
		);
	}

	// Heat transfer across the interface
	forAllConstIter
	(
		heatTransferModelTable,
		heatTransferModels_,
		heatTransferModelIter
	)
	{
		const volScalarField K(heatTransferModelIter()->K());

		const phasePair& pair(this->phasePairs_[heatTransferModelIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			const phaseModel& phase = iter();
			const phaseModel& otherPhase = iter.otherPhase();

			const volScalarField& he(phase.thermo().he());
			volScalarField Cpv(phase.thermo().Cpv());

			*eqns[phase.name()] +=
				K * (otherPhase.thermo().T() - phase.thermo().T() + he / Cpv)
				- fvm::Sp(K / Cpv, he);
		}
	}

	// Source term due to mass transfer
	forAllConstIter
	(
		phaseSystem::phasePairTable,
		this->phasePairs_,
		phasePairIter
	)
	{
		const phasePair& pair(phasePairIter());

		if (pair.ordered())
		{
			continue;
		}

		const phaseModel& phase1 = pair.phase1();
		const phaseModel& phase2 = pair.phase2();

		const volScalarField& he1(phase1.thermo().he());
		const volScalarField& he2(phase2.thermo().he());

		const volScalarField K1(phase1.K());
		const volScalarField K2(phase2.K());

		// Note that the phase heEqn contains a continuity error term, which
		// implicitly adds a mass transfer term of fvm::Sp(dmdt, he). These
		// additions do not include this term.

		const volScalarField dmdt(this->dmdt(pair));
		const volScalarField dmdt21(posPart(dmdt));
		const volScalarField dmdt12(negPart(dmdt));

		*eqns[phase1.name()] +=
			dmdt21 * he2 - fvm::Sp(dmdt21, he1) + dmdt21 * (K2 - K1);

		*eqns[phase2.name()] -=
			dmdt12 * he1 - fvm::Sp(dmdt12, he2) + dmdt12 * (K1 - K2);
	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
bool tnbLib::OneResistanceHeatTransferPhaseSystem<BasePhaseSystem>::read()
{
	if (BasePhaseSystem::read())
	{
		bool readOK = true;

		// Models ...

		return readOK;
	}
	else
	{
		return false;
	}
}