#pragma once

#include <phaseTransferModel.hxx>
#include <fvmSup.hxx>

// * * * * * * * * * * * * Private Member Functions * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::rDmdt
(
	const phasePairKey& key
) const
{
	if (!rDmdt_.found(key))
	{
		return phaseSystem::dmdt(key);
	}

	const scalar rDmdtSign(Pair<word>::compare(rDmdt_.find(key).key(), key));

	return rDmdtSign * *rDmdt_[key];
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::PhaseTransferPhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh)
{
	this->generatePairsAndSubModels
	(
		"phaseTransfer",
		phaseTransferModels_,
		false
	);

	forAllConstIter
	(
		phaseTransferModelTable,
		phaseTransferModels_,
		phaseTransferModelIter
	)
	{
		this->rDmdt_.insert
		(
			phaseTransferModelIter.key(),
			phaseSystem::dmdt(phaseTransferModelIter.key()).ptr()
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::
~PhaseTransferPhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::dmdt
(
	const phasePairKey& key
) const
{
	return BasePhaseSystem::dmdt(key) + this->rDmdt(key);
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::volScalarField>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::dmdts() const
{
	PtrList<volScalarField> dmdts(BasePhaseSystem::dmdts());

	forAllConstIter(rDmdtTable, rDmdt_, rDmdtIter)
	{
		const phasePair& pair = this->phasePairs_[rDmdtIter.key()];
		const volScalarField& rDmdt = *rDmdtIter();

		this->addField(pair.phase1(), "dmdt", rDmdt, dmdts);
		this->addField(pair.phase2(), "dmdt", -rDmdt, dmdts);
	}

	return dmdts;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::massTransferTable>
tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::massTransfer() const
{
	// Create a mass transfer matrix for each species of each phase
	autoPtr<phaseSystem::massTransferTable> eqnsPtr
	(
		new phaseSystem::massTransferTable()
	);

	phaseSystem::massTransferTable& eqns = eqnsPtr();

	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		const PtrList<volScalarField>& Yi = phase.Y();

		forAll(Yi, i)
		{
			eqns.insert
			(
				Yi[i].name(),
				new fvScalarMatrix(Yi[i], dimMass / dimTime)
			);
		}
	}

	// Mass transfer across the interface
	forAllConstIter
	(
		phaseTransferModelTable,
		phaseTransferModels_,
		phaseTransferModelIter
	)
	{
		const phasePair& pair(this->phasePairs_[phaseTransferModelIter.key()]);

		const phaseModel& phase = pair.phase1();
		const phaseModel& otherPhase = pair.phase2();

		// Note that the phase YiEqn does not contain a continuity error term,
		// so these additions represent the entire mass transfer

		const volScalarField dmdt(this->rDmdt(pair));
		const volScalarField dmdt12(negPart(dmdt));
		const volScalarField dmdt21(posPart(dmdt));

		const PtrList<volScalarField>& Yi = phase.Y();

		forAll(Yi, i)
		{
			const word name
			(
				IOobject::groupName(Yi[i].member(), phase.name())
			);

			const word otherName
			(
				IOobject::groupName(Yi[i].member(), otherPhase.name())
			);

			*eqns[name] +=
				dmdt21 * eqns[otherName]->psi()
				+ fvm::Sp(dmdt12, eqns[name]->psi());

			*eqns[otherName] -=
				dmdt12 * eqns[name]->psi()
				+ fvm::Sp(dmdt21, eqns[otherName]->psi());
		}

	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
void tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::correct()
{
	BasePhaseSystem::correct();

	forAllConstIter
	(
		phaseTransferModelTable,
		phaseTransferModels_,
		phaseTransferModelIter
	)
	{
		*rDmdt_[phaseTransferModelIter.key()] =
			dimensionedScalar(dimDensity / dimTime, 0);
	}

	forAllConstIter
	(
		phaseTransferModelTable,
		phaseTransferModels_,
		phaseTransferModelIter
	)
	{
		*rDmdt_[phaseTransferModelIter.key()] +=
			phaseTransferModelIter()->dmdt();
	}
}


template<class BasePhaseSystem>
bool tnbLib::PhaseTransferPhaseSystem<BasePhaseSystem>::read()
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