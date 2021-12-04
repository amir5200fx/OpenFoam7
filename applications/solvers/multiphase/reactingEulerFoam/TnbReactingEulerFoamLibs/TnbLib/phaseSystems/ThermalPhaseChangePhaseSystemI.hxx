#pragma once

#include <alphatPhaseChangeWallFunctionFvPatchScalarField.hxx>
#include <fvcVolumeIntegrate.hxx>
#include <fvmSup.hxx>

// * * * * * * * * * * * * Private Member Functions * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::iDmdt
(
	const phasePairKey& key
) const
{
	if (!iDmdt_.found(key))
	{
		return phaseSystem::dmdt(key);
	}

	const scalar dmdtSign(Pair<word>::compare(iDmdt_.find(key).key(), key));

	return dmdtSign * *iDmdt_[key];
}


template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::wDmdt
(
	const phasePairKey& key
) const
{
	if (!wDmdt_.found(key))
	{
		return phaseSystem::dmdt(key);
	}

	const scalar dmdtSign(Pair<word>::compare(wDmdt_.find(key).key(), key));

	return dmdtSign * *wDmdt_[key];
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::
ThermalPhaseChangePhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh),
	volatile_(this->template lookupOrDefault<word>("volatile", "none")),
	saturationModel_
	(
		saturationModel::New(this->subDict("saturationModel"), mesh)
	),
	phaseChange_(this->lookup("phaseChange"))
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

		// Initially assume no mass transfer
		iDmdt_.insert
		(
			pair,
			new volScalarField
			(
				IOobject
				(
					IOobject::groupName("iDmdt", pair.name()),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimDensity / dimTime, 0)
			)
		);

		// Initially assume no mass transfer
		wDmdt_.insert
		(
			pair,
			new volScalarField
			(
				IOobject
				(
					IOobject::groupName("wDmdt", pair.name()),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimDensity / dimTime, 0)
			)
		);

		// Initially assume no mass transfer
		wMDotL_.insert
		(
			pair,
			new volScalarField
			(
				IOobject
				(
					IOobject::groupName("wMDotL", pair.name()),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimEnergy / dimTime / dimVolume, 0)
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::
~ThermalPhaseChangePhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
const tnbLib::saturationModel&
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::saturation() const
{
	return saturationModel_();
}


template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::dmdt
(
	const phasePairKey& key
) const
{
	return BasePhaseSystem::dmdt(key) + this->iDmdt(key) + this->wDmdt(key);
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::volScalarField>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::dmdts() const
{
	PtrList<volScalarField> dmdts(BasePhaseSystem::dmdts());

	forAllConstIter(iDmdtTable, iDmdt_, iDmdtIter)
	{
		const phasePair& pair = this->phasePairs_[iDmdtIter.key()];
		const volScalarField& iDmdt = *iDmdtIter();

		this->addField(pair.phase1(), "dmdt", iDmdt, dmdts);
		this->addField(pair.phase2(), "dmdt", -iDmdt, dmdts);
	}

	forAllConstIter(wDmdtTable, wDmdt_, wDmdtIter)
	{
		const phasePair& pair = this->phasePairs_[wDmdtIter.key()];
		const volScalarField& wDmdt = *wDmdtIter();

		this->addField(pair.phase1(), "dmdt", wDmdt, dmdts);
		this->addField(pair.phase2(), "dmdt", -wDmdt, dmdts);
	}

	return dmdts;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::heatTransferTable>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::heatTransfer() const
{
	autoPtr<phaseSystem::heatTransferTable> eqnsPtr =
		BasePhaseSystem::heatTransfer();

	phaseSystem::heatTransferTable& eqns = eqnsPtr();

	// Add boundary term
	forAllConstIter
	(
		phaseSystem::phasePairTable,
		this->phasePairs_,
		phasePairIter
	)
	{
		if (this->wMDotL_.found(phasePairIter.key()))
		{
			const phasePair& pair(phasePairIter());

			if (pair.ordered())
			{
				continue;
			}

			const phaseModel& phase1 = pair.phase1();
			const phaseModel& phase2 = pair.phase2();

			*eqns[phase1.name()] += negPart(*this->wMDotL_[pair]);
			*eqns[phase2.name()] -= posPart(*this->wMDotL_[pair]);

			if
				(
					phase1.thermo().he().member() == "e"
					|| phase2.thermo().he().member() == "e"
					)
			{
				const volScalarField dmdt
				(
					this->iDmdt(pair) + this->wDmdt(pair)
				);

				if (phase1.thermo().he().member() == "e")
				{
					*eqns[phase1.name()] +=
						phase1.thermo().p() * dmdt / phase1.thermo().rho();
				}

				if (phase2.thermo().he().member() == "e")
				{
					*eqns[phase2.name()] -=
						phase2.thermo().p() * dmdt / phase2.thermo().rho();
				}
			}
		}
	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::massTransferTable>
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::massTransfer() const
{
	autoPtr<phaseSystem::massTransferTable> eqnsPtr =
		BasePhaseSystem::massTransfer();

	phaseSystem::massTransferTable& eqns = eqnsPtr();

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

		const phaseModel& phase = pair.phase1();
		const phaseModel& otherPhase = pair.phase2();

		const PtrList<volScalarField>& Yi = phase.Y();

		forAll(Yi, i)
		{
			if (Yi[i].member() != volatile_)
			{
				continue;
			}

			const word name
			(
				IOobject::groupName(volatile_, phase.name())
			);

			const word otherName
			(
				IOobject::groupName(volatile_, otherPhase.name())
			);

			// Note that the phase YiEqn does not contain a continuity error
			// term, so these additions represent the entire mass transfer

			const volScalarField dmdt(this->iDmdt(pair) + this->wDmdt(pair));

			*eqns[name] += dmdt;
			*eqns[otherName] -= dmdt;
		}
	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
void
tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::correctInterfaceThermo()
{
	typedef compressible::alphatPhaseChangeWallFunctionFvPatchScalarField
		alphatPhaseChangeWallFunction;

	forAllConstIter
	(
		typename BasePhaseSystem::heatTransferModelTable,
		this->heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair
		(
			this->phasePairs_[heatTransferModelIter.key()]
		);

		const phaseModel& phase1 = pair.phase1();
		const phaseModel& phase2 = pair.phase2();

		const volScalarField& T1(phase1.thermo().T());
		const volScalarField& T2(phase2.thermo().T());

		const volScalarField& he1(phase1.thermo().he());
		const volScalarField& he2(phase2.thermo().he());

		const volScalarField& p(phase1.thermo().p());

		volScalarField& iDmdt(*this->iDmdt_[pair]);
		volScalarField& Tf(*this->Tf_[pair]);

		const volScalarField Tsat(saturationModel_->Tsat(phase1.thermo().p()));

		volScalarField hf1
		(
			he1.member() == "e"
			? phase1.thermo().he(p, Tsat) + p / phase1.rho()
			: phase1.thermo().he(p, Tsat)
		);
		volScalarField hf2
		(
			he2.member() == "e"
			? phase2.thermo().he(p, Tsat) + p / phase2.rho()
			: phase2.thermo().he(p, Tsat)
		);

		volScalarField h1
		(
			he1.member() == "e"
			? he1 + p / phase1.rho()
			: tmp<volScalarField>(he1)
		);

		volScalarField h2
		(
			he2.member() == "e"
			? he2 + p / phase2.rho()
			: tmp<volScalarField>(he2)
		);

		volScalarField L
		(
			(neg0(iDmdt) * hf2 + pos(iDmdt) * h2)
			- (pos0(iDmdt) * hf1 + neg(iDmdt) * h1)
		);

		volScalarField iDmdtNew(iDmdt);

		if (phaseChange_)
		{
			volScalarField H1(heatTransferModelIter().first()->K(0));
			volScalarField H2(heatTransferModelIter().second()->K(0));

			iDmdtNew = (H1 * (Tsat - T1) + H2 * (Tsat - T2)) / L;
		}
		else
		{
			iDmdtNew == dimensionedScalar(iDmdt.dimensions(), 0);
		}

		volScalarField H1(heatTransferModelIter().first()->K());
		volScalarField H2(heatTransferModelIter().second()->K());

		// Limit the H[12] to avoid /0
		H1.max(small);
		H2.max(small);

		Tf = (H1 * T1 + H2 * T2 + iDmdtNew * L) / (H1 + H2);

		Info << "Tf." << pair.name()
			<< ": min = " << min(Tf.primitiveField())
			<< ", mean = " << average(Tf.primitiveField())
			<< ", max = " << max(Tf.primitiveField())
			<< endl;

		scalar iDmdtRelax(this->mesh().fieldRelaxationFactor("iDmdt"));
		iDmdt = (1 - iDmdtRelax) * iDmdt + iDmdtRelax * iDmdtNew;

		if (phaseChange_)
		{
			Info << "iDmdt." << pair.name()
				<< ": min = " << min(iDmdt.primitiveField())
				<< ", mean = " << average(iDmdt.primitiveField())
				<< ", max = " << max(iDmdt.primitiveField())
				<< ", integral = " << fvc::domainIntegrate(iDmdt).value()
				<< endl;
		}

		volScalarField& wDmdt(*this->wDmdt_[pair]);
		volScalarField& wMDotL(*this->wMDotL_[pair]);
		wDmdt = Zero;
		wMDotL = Zero;

		bool wallBoilingActive = false;

		forAllConstIter(phasePair, pair, iter)
		{
			const phaseModel& phase = iter();
			const phaseModel& otherPhase = iter.otherPhase();

			if
				(
					phase.mesh().foundObject<volScalarField>
					(
						"alphat." + phase.name()
						)
					)
			{
				const volScalarField& alphat =
					phase.mesh().lookupObject<volScalarField>
					(
						"alphat." + phase.name()
						);

				const fvPatchList& patches = this->mesh().boundary();
				forAll(patches, patchi)
				{
					const fvPatch& currPatch = patches[patchi];

					if
						(
							isA<alphatPhaseChangeWallFunction>
							(
								alphat.boundaryField()[patchi]
								)
							)
					{
						const alphatPhaseChangeWallFunction& PCpatch =
							refCast<const alphatPhaseChangeWallFunction>
							(
								alphat.boundaryField()[patchi]
								);

						phasePairKey key(phase.name(), otherPhase.name());

						if (PCpatch.activePhasePair(key))
						{
							wallBoilingActive = true;

							const scalarField& patchDmdt =
								PCpatch.dmdt(key);
							const scalarField& patchMDotL =
								PCpatch.mDotL(key);

							const scalar sign
							(
								Pair<word>::compare(pair, key)
							);

							forAll(patchDmdt, facei)
							{
								const label faceCelli =
									currPatch.faceCells()[facei];
								wDmdt[faceCelli] -= sign * patchDmdt[facei];
								wMDotL[faceCelli] -= sign * patchMDotL[facei];
							}
						}
					}
				}
			}
		}

		if (wallBoilingActive)
		{
			Info << "wDmdt." << pair.name()
				<< ": min = " << min(wDmdt.primitiveField())
				<< ", mean = " << average(wDmdt.primitiveField())
				<< ", max = " << max(wDmdt.primitiveField())
				<< ", integral = " << fvc::domainIntegrate(wDmdt).value()
				<< endl;
		}
	}
}


template<class BasePhaseSystem>
bool tnbLib::ThermalPhaseChangePhaseSystem<BasePhaseSystem>::read()
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