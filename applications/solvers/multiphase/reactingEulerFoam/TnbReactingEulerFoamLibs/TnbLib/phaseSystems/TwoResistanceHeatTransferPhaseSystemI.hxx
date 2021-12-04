#pragma once
#include <BlendedInterfacialModel.hxx>
#include <heatTransferModel.hxx>

#include <HashPtrTable.hxx>

#include <fvcDiv.hxx>
#include <fvmSup.hxx>
#include <fvMatrix.hxx>
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
TwoResistanceHeatTransferPhaseSystem
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

	// Check that models have been specified on both sides of the interfaces
	forAllConstIter
	(
		heatTransferModelTable,
		heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair = this->phasePairs_[heatTransferModelIter.key()];

		if (!heatTransferModels_[pair].first().valid())
		{
			FatalErrorInFunction
				<< "A heat transfer model for the " << pair.phase1().name()
				<< " side of the " << pair << " pair is not specified"
				<< exit(FatalError);
		}
		if (!heatTransferModels_[pair].second().valid())
		{
			FatalErrorInFunction
				<< "A heat transfer model for the " << pair.phase2().name()
				<< " side of the " << pair << " pair is not specified"
				<< exit(FatalError);
		}
	}

	// Calculate initial Tf-s as if there is no mass transfer
	forAllConstIter
	(
		heatTransferModelTable,
		heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair = this->phasePairs_[heatTransferModelIter.key()];

		const phaseModel& phase1 = pair.phase1();
		const phaseModel& phase2 = pair.phase2();

		const volScalarField& T1(phase1.thermo().T());
		const volScalarField& T2(phase2.thermo().T());

		volScalarField H1(heatTransferModels_[pair].first()->K());
		volScalarField H2(heatTransferModels_[pair].second()->K());
		dimensionedScalar HSmall("small", heatTransferModel::dimK, small);

		Tf_.insert
		(
			pair,
			new volScalarField
			(
				IOobject
				(
					IOobject::groupName("Tf", pair.name()),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::NO_READ,
					IOobject::AUTO_WRITE
				),
				(H1 * T1 + H2 * T2) / max(H1 + H2, HSmall)
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
~TwoResistanceHeatTransferPhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::heatTransferTable>
tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
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

	// Heat transfer with the interface
	forAllConstIter
	(
		heatTransferModelTable,
		heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair
		(
			this->phasePairs_[heatTransferModelIter.key()]
		);

		const volScalarField& Tf(*Tf_[pair]);

		const Pair<tmp<volScalarField>> Ks
		(
			heatTransferModelIter().first()->K(),
			heatTransferModelIter().second()->K()
		);

		forAllConstIter(phasePair, pair, iter)
		{
			const phaseModel& phase = iter();

			const volScalarField& he(phase.thermo().he());
			const volScalarField Cpv(phase.thermo().Cpv());
			const volScalarField& K(Ks[iter.index()]);

			*eqns[phase.name()] +=
				K * (Tf - phase.thermo().T())
				+ K / Cpv * he - fvm::Sp(K / Cpv, he);
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

		const volScalarField dmdt(this->dmdt(pair));
		const volScalarField dmdt21(posPart(dmdt));
		const volScalarField dmdt12(negPart(dmdt));

		*eqns[phase1.name()] += -fvm::Sp(dmdt21, he1) + dmdt21 * (K2 - K1);

		*eqns[phase2.name()] -= -fvm::Sp(dmdt12, he2) + dmdt12 * (K1 - K2);

		if (this->heatTransferModels_.found(phasePairIter.key()))
		{
			const volScalarField& Tf(*Tf_[pair]);

			*eqns[phase1.name()] +=
				dmdt21 * phase1.thermo().he(phase1.thermo().p(), Tf);

			*eqns[phase2.name()] -=
				dmdt12 * phase2.thermo().he(phase2.thermo().p(), Tf);
		}
		else
		{
			*eqns[phase1.name()] += dmdt21 * he2;

			*eqns[phase2.name()] -= dmdt12 * he1;
		}
	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
void tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
correctEnergyTransport()
{
	BasePhaseSystem::correctEnergyTransport();

	correctInterfaceThermo();
}


template<class BasePhaseSystem>
void tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::
correctInterfaceThermo()
{
	forAllConstIter
	(
		heatTransferModelTable,
		heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair
		(
			this->phasePairs_[heatTransferModelIter.key()]
		);

		const phaseModel& phase1 = pair.phase1();
		const phaseModel& phase2 = pair.phase2();

		const volScalarField& p(phase1.thermo().p());

		const volScalarField& T1(phase1.thermo().T());
		const volScalarField& T2(phase2.thermo().T());

		volScalarField& Tf(*this->Tf_[pair]);

		const volScalarField L
		(
			phase1.thermo().he(p, Tf) - phase2.thermo().he(p, Tf)
		);

		const volScalarField dmdt(this->dmdt(pair));

		volScalarField H1
		(
			this->heatTransferModels_[pair].first()->K()
		);

		volScalarField H2
		(
			this->heatTransferModels_[pair].second()->K()
		);

		// Limit the H[12] to avoid /0
		H1.max(small);
		H2.max(small);

		Tf = (H1 * T1 + H2 * T2 + dmdt * L) / (H1 + H2);

		Info << "Tf." << pair.name()
			<< ": min = " << min(Tf.primitiveField())
			<< ", mean = " << average(Tf.primitiveField())
			<< ", max = " << max(Tf.primitiveField())
			<< endl;
	}
}


template<class BasePhaseSystem>
bool tnbLib::TwoResistanceHeatTransferPhaseSystem<BasePhaseSystem>::read()
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