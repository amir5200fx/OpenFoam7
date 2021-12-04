#pragma once

#include <BlendedInterfacialModel.hxx>
#include <dragModel.hxx>
#include <virtualMassModel.hxx>
#include <liftModel.hxx>
#include <wallLubricationModel.hxx>
#include <turbulentDispersionModel.hxx>

#include <HashPtrTable.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmSup.hxx>
#include <fvcAverage.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>
#include <fvcFlux.hxx>
#include <fvcSnGrad.hxx>
#include <fvMatrix.hxx>


// * * * * * * * * * * * * Private Member Functions * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::Kd
(
	const phasePairKey& key
) const
{
	if (dragModels_.found(key))
	{
		return dragModels_[key]->K();
	}
	else
	{
		return volScalarField::New
		(
			dragModel::typeName + ":K",
			this->mesh_,
			dimensionedScalar(dragModel::dimK, 0)
		);
	}
}


template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::Kdf
(
	const phasePairKey& key
) const
{
	if (dragModels_.found(key))
	{
		return dragModels_[key]->Kf();
	}
	else
	{
		return surfaceScalarField::New
		(
			dragModel::typeName + ":K",
			this->mesh_,
			dimensionedScalar(dragModel::dimK, 0)
		);
	}
}


template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::Vm
(
	const phasePairKey& key
) const
{
	if (virtualMassModels_.found(key))
	{
		return virtualMassModels_[key]->K();
	}
	else
	{
		return volScalarField::New
		(
			virtualMassModel::typeName + ":K",
			this->mesh_,
			dimensionedScalar(virtualMassModel::dimK, 0)
		);
	}
}


template<class BasePhaseSystem>
void tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::
addMassTransferMomentumTransfer(phaseSystem::momentumTransferTable& eqns) const
{
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

		// Note that the phase UEqn contains a continuity error term, which
		// implicitly adds a mass transfer term of fvm::Sp(dmdt, U). These
		// additions do not include this term.

		const volScalarField dmdt(this->dmdt(pair));

		if (!pair.phase1().stationary())
		{
			fvVectorMatrix& eqn = *eqns[pair.phase1().name()];
			const volScalarField dmdt21(posPart(dmdt));

			eqn += dmdt21 * pair.phase2().U() - fvm::Sp(dmdt21, eqn.psi());
		}

		if (!pair.phase2().stationary())
		{
			fvVectorMatrix& eqn = *eqns[pair.phase2().name()];
			const volScalarField dmdt12(negPart(dmdt));

			eqn -= dmdt12 * pair.phase1().U() - fvm::Sp(dmdt12, eqn.psi());
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::
MomentumTransferPhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh)
{
	this->generatePairsAndSubModels
	(
		"drag",
		dragModels_
	);

	this->generatePairsAndSubModels
	(
		"virtualMass",
		virtualMassModels_
	);

	this->generatePairsAndSubModels
	(
		"lift",
		liftModels_
	);

	this->generatePairsAndSubModels
	(
		"wallLubrication",
		wallLubricationModels_
	);

	this->generatePairsAndSubModels
	(
		"turbulentDispersion",
		turbulentDispersionModels_
	);

	forAllConstIter
	(
		dragModelTable,
		dragModels_,
		dragModelIter
	)
	{
		const phasePair& pair(this->phasePairs_[dragModelIter.key()]);

		Kds_.insert
		(
			pair,
			new volScalarField
			(
				IOobject::groupName("Kd", pair.name()),
				dragModelIter()->K()
			)
		);

		Kdfs_.insert
		(
			pair,
			new surfaceScalarField
			(
				IOobject::groupName("Kdf", pair.name()),
				dragModelIter()->Kf()
			)
		);
	}

	forAllConstIter
	(
		virtualMassModelTable,
		virtualMassModels_,
		virtualMassModelIter
	)
	{
		const phasePair& pair(this->phasePairs_[virtualMassModelIter.key()]);

		Vms_.insert
		(
			pair,
			new volScalarField
			(
				IOobject::groupName("Vm", pair.name()),
				virtualMassModelIter()->K()
			)
		);

		Vmfs_.insert
		(
			pair,
			new surfaceScalarField
			(
				IOobject::groupName("Vmf", pair.name()),
				virtualMassModelIter()->Kf()
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::
~MomentumTransferPhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::momentumTransferTable>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::momentumTransfer()
{
	// Create a momentum transfer matrix for each phase
	autoPtr<phaseSystem::momentumTransferTable> eqnsPtr
	(
		new phaseSystem::momentumTransferTable()
	);

	phaseSystem::momentumTransferTable& eqns = eqnsPtr();

	forAll(this->movingPhases(), movingPhasei)
	{
		const phaseModel& phase = this->movingPhases()[movingPhasei];

		eqns.insert
		(
			phase.name(),
			new fvVectorMatrix(phase.U(), dimMass * dimVelocity / dimTime)
		);
	}

	// Update the drag coefficients
	forAllConstIter
	(
		dragModelTable,
		dragModels_,
		dragModelIter
	)
	{
		*Kds_[dragModelIter.key()] = dragModelIter()->K();
		*Kdfs_[dragModelIter.key()] = dragModelIter()->Kf();
	}

	// Add the implicit part of the drag force
	forAllConstIter(KdTable, Kds_, KdIter)
	{
		const volScalarField& K(*KdIter());
		const phasePair& pair(this->phasePairs_[KdIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			if (!iter().stationary())
			{
				fvVectorMatrix& eqn = *eqns[iter().name()];

				eqn -= fvm::Sp(K, eqn.psi());
			}
		}
	}

	// Update the virtual mass coefficients
	forAllConstIter
	(
		virtualMassModelTable,
		virtualMassModels_,
		virtualMassModelIter
	)
	{
		*Vms_[virtualMassModelIter.key()] = virtualMassModelIter()->K();
		*Vmfs_[virtualMassModelIter.key()] = virtualMassModelIter()->Kf();
	}

	// Add the virtual mass force
	forAllConstIter(VmTable, Vms_, VmIter)
	{
		const volScalarField& Vm(*VmIter());
		const phasePair& pair(this->phasePairs_[VmIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			const phaseModel& phase = iter();
			const phaseModel& otherPhase = iter.otherPhase();

			if (!phase.stationary())
			{
				fvVectorMatrix& eqn = *eqns[phase.name()];

				const volVectorField& U = eqn.psi();
				const surfaceScalarField& phi = phase.phi();

				eqn -=
					Vm
					* (
						fvm::ddt(U)
						+ fvm::div(phi, U)
						- fvm::Sp(fvc::div(phi), U)
						- otherPhase.DUDt()
						)
					+ this->MRF_.DDt(Vm, U - otherPhase.U());
			}
		}
	}

	// Add the source term due to mass transfer
	addMassTransferMomentumTransfer(eqns);

	return eqnsPtr;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::momentumTransferTable>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::momentumTransferf()
{
	// Create a momentum transfer matrix for each phase
	autoPtr<phaseSystem::momentumTransferTable> eqnsPtr
	(
		new phaseSystem::momentumTransferTable()
	);

	phaseSystem::momentumTransferTable& eqns = eqnsPtr();

	forAll(this->movingPhases(), movingPhasei)
	{
		const phaseModel& phase = this->movingPhases()[movingPhasei];

		eqns.insert
		(
			phase.name(),
			new fvVectorMatrix(phase.U(), dimMass * dimVelocity / dimTime)
		);
	}

	// Create U & grad(U) fields
	PtrList<fvVectorMatrix> UgradUs(this->phaseModels_.size());
	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		if (!phase.stationary())
		{
			const volVectorField& U = phase.U();

			UgradUs.set
			(
				phasei,
				new fvVectorMatrix
				(
					fvm::div(phase.phi(), U)
					- fvm::Sp(fvc::div(phase.phi()), U)
					+ this->MRF().DDt(U)
				)
			);
		}
	}

	// Add the virtual mass force
	forAllConstIter(VmTable, Vms_, VmIter)
	{
		const volScalarField& Vm(*VmIter());
		const phasePair& pair(this->phasePairs_[VmIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			const phaseModel& phase = iter();
			const phaseModel& otherPhase = iter.otherPhase();

			if (!phase.stationary())
			{
				*eqns[phase.name()] -=
					Vm
					* (
						UgradUs[phase.index()]
						- (UgradUs[otherPhase.index()] & otherPhase.U())
						);
			}
		}
	}

	// Add the source term due to mass transfer
	addMassTransferMomentumTransfer(eqns);

	return eqnsPtr;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::AFfs() const
{
	PtrList<surfaceScalarField> AFfs(this->phaseModels_.size());

	// Add the implicit part of the drag force
	forAllConstIter(KdfTable, Kdfs_, KdfIter)
	{
		const surfaceScalarField& Kf(*KdfIter());
		const phasePair& pair(this->phasePairs_[KdfIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField(iter(), "AFf", Kf, AFfs);
		}
	}

	// Add the implicit part of the virtual mass force
	forAllConstIter(VmfTable, Vmfs_, VmfIter)
	{
		const surfaceScalarField& Vmf(*VmfIter());
		const phasePair& pair(this->phasePairs_[VmfIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField(iter(), "AFf", byDt(Vmf), AFfs);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields("AFf", dimDensity / dimTime, AFfs);
	}

	return AFfs;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::phiFs
(
	const PtrList<volScalarField>& rAUs
)
{
	PtrList<surfaceScalarField> phiFs(this->phaseModels_.size());

	// Add the lift force
	forAllConstIter
	(
		liftModelTable,
		liftModels_,
		liftModelIter
	)
	{
		const volVectorField F(liftModelIter()->F<vector>());
		const phasePair& pair(this->phasePairs_[liftModelIter.key()]);

		this->addField
		(
			pair.phase1(),
			"phiF",
			fvc::flux(rAUs[pair.phase1().index()] * F),
			phiFs
		);
		this->addField
		(
			pair.phase2(),
			"phiF",
			-fvc::flux(rAUs[pair.phase2().index()] * F),
			phiFs
		);
	}

	// Add the wall lubrication force
	forAllConstIter
	(
		wallLubricationModelTable,
		wallLubricationModels_,
		wallLubricationModelIter
	)
	{
		const volVectorField F(wallLubricationModelIter()->F<vector>());
		const phasePair&
			pair(this->phasePairs_[wallLubricationModelIter.key()]);

		this->addField
		(
			pair.phase1(),
			"phiF",
			fvc::flux(rAUs[pair.phase1().index()] * F),
			phiFs
		);
		this->addField
		(
			pair.phase2(),
			"phiF",
			-fvc::flux(rAUs[pair.phase2().index()] * F),
			phiFs
		);
	}

	// Add the phase pressure
	DByAfs_.clear();
	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		const surfaceScalarField pPrimeByAf
		(
			fvc::interpolate(rAUs[phasei] * phase.pPrime())
		);

		const surfaceScalarField snGradAlpha1
		(
			fvc::snGrad(phase) * this->mesh_.magSf()
		);

		this->addField(phase, "phiF", pPrimeByAf * snGradAlpha1, phiFs);

		const bool implicitPhasePressure =
			this->mesh_.solverDict(phase.volScalarField::name()).
			template lookupOrDefault<Switch>
			(
				"implicitPhasePressure",
				false
				);

		if (implicitPhasePressure)
		{
			this->addField(phase, "DByAf", pPrimeByAf, DByAfs_);
		}
	}

	// Add the turbulent dispersion force
	forAllConstIter
	(
		turbulentDispersionModelTable,
		turbulentDispersionModels_,
		turbulentDispersionModelIter
	)
	{
		const phasePair&
			pair(this->phasePairs_[turbulentDispersionModelIter.key()]);

		const volScalarField D(turbulentDispersionModelIter()->D());

		const surfaceScalarField DByA1f
		(
			fvc::interpolate(rAUs[pair.phase1().index()] * D)
		);
		const surfaceScalarField DByA2f
		(
			fvc::interpolate(rAUs[pair.phase2().index()] * D)
		);

		const surfaceScalarField snGradAlpha1
		(
			fvc::snGrad(pair.phase1()) * this->mesh_.magSf()
		);

		this->addField(pair.phase1(), "phiF", DByA1f * snGradAlpha1, phiFs);
		this->addField(pair.phase2(), "phiF", -DByA2f * snGradAlpha1, phiFs);

		if (DByAfs_.found(pair.phase1().name()))
		{
			this->addField(pair.phase1(), "DByAf", DByA1f, DByAfs_);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields("phiF", dimForce / dimDensity / dimVelocity, phiFs);
	}

	return phiFs;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::phiFfs
(
	const PtrList<surfaceScalarField>& rAUfs
)
{
	PtrList<surfaceScalarField> phiFfs(this->phaseModels_.size());

	// Add the explicit part of the virtual mass force
	forAllConstIter(VmfTable, Vmfs_, VmfIter)
	{
		const surfaceScalarField& Vmf(*VmfIter());
		const phasePair& pair(this->phasePairs_[VmfIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField
			(
				iter(),
				"phiFf",
				-rAUfs[iter().index()] * Vmf
				* (
					byDt(this->MRF().absolute(iter().phi()().oldTime()))
					+ iter.otherPhase().DUDtf()
					),
				phiFfs
			);
		}
	}

	// Add the lift force
	forAllConstIter
	(
		liftModelTable,
		liftModels_,
		liftModelIter
	)
	{
		const surfaceScalarField Ff(liftModelIter()->Ff());
		const phasePair& pair(this->phasePairs_[liftModelIter.key()]);

		this->addField
		(
			pair.phase1(),
			"phiFs",
			rAUfs[pair.phase1().index()] * Ff,
			phiFfs
		);
		this->addField
		(
			pair.phase2(),
			"phiFf",
			-rAUfs[pair.phase2().index()] * Ff,
			phiFfs
		);
	}

	// Add the wall lubrication force
	forAllConstIter
	(
		wallLubricationModelTable,
		wallLubricationModels_,
		wallLubricationModelIter
	)
	{
		const surfaceScalarField Ff(wallLubricationModelIter()->Ff());
		const phasePair&
			pair(this->phasePairs_[wallLubricationModelIter.key()]);

		this->addField
		(
			pair.phase1(),
			"phiFf",
			rAUfs[pair.phase1().index()] * Ff,
			phiFfs
		);
		this->addField
		(
			pair.phase2(),
			"phiFf",
			-rAUfs[pair.phase2().index()] * Ff,
			phiFfs
		);
	}

	// Add the phase pressure
	DByAfs_.clear();
	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		const surfaceScalarField pPrimeByAf
		(
			rAUfs[phasei] * fvc::interpolate(phase.pPrime())
		);

		const surfaceScalarField snGradAlpha1
		(
			fvc::snGrad(phase) * this->mesh_.magSf()
		);

		this->addField(phase, "phiFf", pPrimeByAf * snGradAlpha1, phiFfs);

		const bool implicitPhasePressure =
			this->mesh_.solverDict(phase.volScalarField::name()).
			template lookupOrDefault<Switch>
			(
				"implicitPhasePressure",
				false
				);

		if (implicitPhasePressure)
		{
			this->addField(phase, "DByAf", pPrimeByAf, DByAfs_);
		}
	}

	// Add the turbulent dispersion force and phase pressure
	forAllConstIter
	(
		turbulentDispersionModelTable,
		turbulentDispersionModels_,
		turbulentDispersionModelIter
	)
	{
		const phasePair&
			pair(this->phasePairs_[turbulentDispersionModelIter.key()]);

		const volScalarField D(turbulentDispersionModelIter()->D());

		const surfaceScalarField DByAf1
		(
			rAUfs[pair.phase1().index()] * fvc::interpolate(D)
		);
		const surfaceScalarField DByAf2
		(
			rAUfs[pair.phase2().index()] * fvc::interpolate(D)
		);

		const surfaceScalarField snGradAlpha1
		(
			fvc::snGrad(pair.phase1()) * this->mesh_.magSf()
		);

		this->addField(pair.phase1(), "phiFf", DByAf1 * snGradAlpha1, phiFfs);
		this->addField(pair.phase2(), "phiFf", -DByAf2 * snGradAlpha1, phiFfs);

		if (DByAfs_.found(pair.phase1().name()))
		{
			this->addField(pair.phase1(), "DByAf", DByAf1, DByAfs_);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields("phiFf", dimForce / dimDensity / dimVelocity, phiFfs);
	}

	return phiFfs;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::phiKdPhis
(
	const PtrList<volScalarField>& rAUs
) const
{
	PtrList<surfaceScalarField> phiKdPhis(this->phaseModels_.size());

	// Add the explicit part of the drag force
	forAllConstIter(KdTable, Kds_, KdIter)
	{
		const volScalarField& K(*KdIter());
		const phasePair& pair(this->phasePairs_[KdIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField
			(
				iter(),
				"phiKdPhi",
				-fvc::interpolate(rAUs[iter().index()] * K)
				* this->MRF().absolute(iter.otherPhase().phi()),
				phiKdPhis
			);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields
		(
			"phiKdPhi",
			dimForce / dimDensity / dimVelocity,
			phiKdPhis
		);
	}

	return phiKdPhis;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::phiKdPhifs
(
	const PtrList<surfaceScalarField>& rAUfs
) const
{
	PtrList<surfaceScalarField> phiKdPhifs(this->phaseModels_.size());

	// Add the explicit part of the drag force
	forAllConstIter(KdfTable, Kdfs_, KdfIter)
	{
		const surfaceScalarField& Kf(*KdfIter());
		const phasePair& pair(this->phasePairs_[KdfIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField
			(
				iter(),
				"phiKdPhif",
				-rAUfs[iter().index()] * Kf
				* this->MRF().absolute(iter.otherPhase().phi()),
				phiKdPhifs
			);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields
		(
			"phiKdPhif",
			dimForce / dimDensity / dimVelocity,
			phiKdPhifs
		);
	}

	return phiKdPhifs;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::volVectorField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::KdUByAs
(
	const PtrList<volScalarField>& rAUs
) const
{
	PtrList<volVectorField> KdUByAs(this->phaseModels_.size());

	// Add the explicit part of the drag force
	forAllConstIter(KdTable, Kds_, KdIter)
	{
		const volScalarField& K(*KdIter());
		const phasePair& pair(this->phasePairs_[KdIter.key()]);

		forAllConstIter(phasePair, pair, iter)
		{
			this->addField
			(
				iter(),
				"KdUByA",
				-rAUs[iter().index()] * K * iter.otherPhase().U(),
				KdUByAs
			);
		}
	}

	if (this->fillFields_)
	{
		this->fillFields("KdUByA", dimVelocity, KdUByAs);
	}

	return KdUByAs;
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::surfaceScalarField>
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::ddtCorrByAs
(
	const PtrList<volScalarField>& rAUs,
	const bool includeVirtualMass
) const
{
	PtrList<surfaceScalarField> ddtCorrByAs(this->phaseModels_.size());

	// Construct phi differences
	PtrList<surfaceScalarField> phiCorrs(this->phaseModels_.size());
	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];

		phiCorrs.set
		(
			phasei,
			this->MRF().absolute(phase.phi()().oldTime())
			- fvc::flux(phase.U()().oldTime())
		);
	}

	// Add correction
	forAll(this->phaseModels_, phasei)
	{
		const phaseModel& phase = this->phaseModels_[phasei];
		const volScalarField& alpha = phase;

		// Apply ddtPhiCorr filter in pure(ish) phases
		surfaceScalarField alphafBar
		(
			fvc::interpolate(fvc::average(fvc::interpolate(alpha)))
		);

		tmp<surfaceScalarField> phiCorrCoeff = pos0(alphafBar - 0.99);

		surfaceScalarField::Boundary& phiCorrCoeffBf =
			phiCorrCoeff.ref().boundaryFieldRef();

		forAll(this->mesh_.boundary(), patchi)
		{
			// Set ddtPhiCorr to 0 on non-coupled boundaries
			if
				(
					!this->mesh_.boundary()[patchi].coupled()
					|| isA<cyclicAMIFvPatch>(this->mesh_.boundary()[patchi])
					)
			{
				phiCorrCoeffBf[patchi] = 0;
			}
		}

		this->addField
		(
			phase,
			"ddtCorrByA",
			-phiCorrCoeff * phiCorrs[phasei] * fvc::interpolate
			(
				byDt(alpha.oldTime() * phase.rho()().oldTime() * rAUs[phasei])
			),
			ddtCorrByAs
		);
	}

	// Add virtual mass correction
	if (includeVirtualMass)
	{
		forAllConstIter(VmTable, Vms_, VmIter)
		{
			const volScalarField& Vm(*VmIter());
			const phasePair& pair(this->phasePairs_[VmIter.key()]);

			forAllConstIter(phasePair, pair, iter)
			{
				const phaseModel& phase = iter();
				const phaseModel& otherPhase = iter.otherPhase();

				this->addField
				(
					iter(),
					"ddtCorrByA",
					-fvc::interpolate(Vm * byDt(rAUs[phase.index()]))
					* (
						phiCorrs[phase.index()]
						+ this->MRF().absolute(otherPhase.phi())
						- fvc::flux(otherPhase.U())
						- phiCorrs[otherPhase.index()]
						),
					ddtCorrByAs
				);
			}
		}
	}

	return ddtCorrByAs;
}


template<class BasePhaseSystem>
void tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::partialElimination
(
	const PtrList<volScalarField>& rAUs
)
{
	Info << "Inverting drag systems: ";

	phaseSystem::phaseModelList& phases = this->phaseModels_;

	// Create drag coefficient matrices
	PtrList<PtrList<volScalarField>> KdByAs(phases.size());
	PtrList<PtrList<surfaceScalarField>> phiKds(phases.size());

	forAll(phases, phasei)
	{
		KdByAs.set
		(
			phasei,
			new PtrList<volScalarField>(phases.size())
		);

		phiKds.set
		(
			phasei,
			new PtrList<surfaceScalarField>(phases.size())
		);
	}

	forAllConstIter(KdTable, Kds_, KdIter)
	{
		const volScalarField& K(*KdIter());
		const phasePair& pair(this->phasePairs_[KdIter.key()]);

		const label phase1i = pair.phase1().index();
		const label phase2i = pair.phase2().index();

		this->addField
		(
			pair.phase2(),
			"KdByA",
			-rAUs[phase1i] * K,
			KdByAs[phase1i]
		);
		this->addField
		(
			pair.phase1(),
			"KdByA",
			-rAUs[phase2i] * K,
			KdByAs[phase2i]
		);

		this->addField
		(
			pair.phase2(),
			"phiKd",
			fvc::interpolate(KdByAs[phase1i][phase2i]),
			phiKds[phase1i]
		);
		this->addField
		(
			pair.phase1(),
			"phiKd",
			fvc::interpolate(KdByAs[phase2i][phase1i]),
			phiKds[phase2i]
		);
	}

	forAll(phases, phasei)
	{
		this->fillFields("KdByAs", dimless, KdByAs[phasei]);
		this->fillFields("phiKds", dimless, phiKds[phasei]);

		KdByAs[phasei][phasei] = 1;
		phiKds[phasei][phasei] = 1;
	}

	// Decompose
	for (label i = 0; i < phases.size(); ++i)
	{
		for (label j = i + 1; j < phases.size(); ++j)
		{
			KdByAs[i][j] /= KdByAs[i][i];
			phiKds[i][j] /= phiKds[i][i];
			for (label k = i + 1; k < phases.size(); ++k)
			{
				KdByAs[j][k] -= KdByAs[j][i] * KdByAs[i][k];
				phiKds[j][k] -= phiKds[j][i] * phiKds[i][k];
			}
		}
	}
	{
		volScalarField detKdByAs(KdByAs[0][0]);
		surfaceScalarField detPhiKdfs(phiKds[0][0]);
		for (label i = 1; i < phases.size(); ++i)
		{
			detKdByAs *= KdByAs[i][i];
			detPhiKdfs *= phiKds[i][i];
		}
		Info << "Min cell/face det = " << gMin(detKdByAs.primitiveField())
			<< "/" << gMin(detPhiKdfs.primitiveField()) << endl;
	}

	// Solve for the velocities and fluxes
	for (label i = 1; i < phases.size(); ++i)
	{
		if (!phases[i].stationary())
		{
			for (label j = 0; j < i; j++)
			{
				phases[i].URef() -= KdByAs[i][j] * phases[j].U();
				phases[i].phiRef() -= phiKds[i][j] * phases[j].phi();
			}
		}
	}
	for (label i = phases.size() - 1; i >= 0; i--)
	{
		if (!phases[i].stationary())
		{
			for (label j = phases.size() - 1; j > i; j--)
			{
				phases[i].URef() -= KdByAs[i][j] * phases[j].U();
				phases[i].phiRef() -= phiKds[i][j] * phases[j].phi();
			}
			phases[i].URef() /= KdByAs[i][i];
			phases[i].phiRef() /= phiKds[i][i];
		}
	}
}


template<class BasePhaseSystem>
void tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::partialEliminationf
(
	const PtrList<surfaceScalarField>& rAUfs
)
{
	Info << "Inverting drag system: ";

	phaseSystem::phaseModelList& phases = this->phaseModels_;

	// Create drag coefficient matrix
	PtrList<PtrList<surfaceScalarField>> phiKdfs(phases.size());

	forAll(phases, phasei)
	{
		phiKdfs.set
		(
			phasei,
			new PtrList<surfaceScalarField>(phases.size())
		);
	}

	forAllConstIter(KdfTable, Kdfs_, KdfIter)
	{
		const surfaceScalarField& K(*KdfIter());
		const phasePair& pair(this->phasePairs_[KdfIter.key()]);

		const label phase1i = pair.phase1().index();
		const label phase2i = pair.phase2().index();

		this->addField
		(
			pair.phase2(),
			"phiKdf",
			-rAUfs[phase1i] * K,
			phiKdfs[phase1i]
		);
		this->addField
		(
			pair.phase1(),
			"phiKdf",
			-rAUfs[phase2i] * K,
			phiKdfs[phase2i]
		);
	}

	forAll(phases, phasei)
	{
		this->fillFields("phiKdf", dimless, phiKdfs[phasei]);

		phiKdfs[phasei][phasei] = 1;
	}

	// Decompose
	for (label i = 0; i < phases.size(); ++i)
	{
		for (label j = i + 1; j < phases.size(); ++j)
		{
			phiKdfs[i][j] /= phiKdfs[i][i];
			for (label k = i + 1; k < phases.size(); ++k)
			{
				phiKdfs[j][k] -= phiKdfs[j][i] * phiKdfs[i][k];
			}
		}
	}
	{
		surfaceScalarField detPhiKdfs(phiKdfs[0][0]);
		for (label i = 1; i < phases.size(); ++i)
		{
			detPhiKdfs *= phiKdfs[i][i];
		}
		Info << "Min face det = " << gMin(detPhiKdfs.primitiveField()) << endl;
	}

	// Solve for the fluxes
	for (label i = 1; i < phases.size(); ++i)
	{
		if (!phases[i].stationary())
		{
			for (label j = 0; j < i; j++)
			{
				phases[i].phiRef() -= phiKdfs[i][j] * phases[j].phi();
			}
		}
	}
	for (label i = phases.size() - 1; i >= 0; i--)
	{
		if (!phases[i].stationary())
		{
			for (label j = phases.size() - 1; j > i; j--)
			{
				phases[i].phiRef() -= phiKdfs[i][j] * phases[j].phi();
			}
			phases[i].phiRef() /= phiKdfs[i][i];
		}
	}
}


template<class BasePhaseSystem>
const tnbLib::HashPtrTable<tnbLib::surfaceScalarField>&
tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::DByAfs() const
{
	return DByAfs_;
}


template<class BasePhaseSystem>
bool tnbLib::MomentumTransferPhaseSystem<BasePhaseSystem>::read()
{
	if (BasePhaseSystem::read())
	{
		bool readOK = true;

		// Read models ...

		return readOK;
	}
	else
	{
		return false;
	}
}