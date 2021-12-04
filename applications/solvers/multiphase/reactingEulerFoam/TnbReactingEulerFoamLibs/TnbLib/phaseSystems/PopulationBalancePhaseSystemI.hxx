#pragma once

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::pDmdt
(
	const phasePairKey& key
) const
{
	if (!pDmdt_.found(key))
	{
		return phaseSystem::dmdt(key);
	}

	const scalar pDmdtSign(Pair<word>::compare(pDmdt_.find(key).key(), key));

	return pDmdtSign * *pDmdt_[key];
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::
PopulationBalancePhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh),

	populationBalances_
	(
		this->lookup("populationBalances"),
		diameterModels::populationBalanceModel::iNew(*this, pDmdt_)
	)
{
	forAll(populationBalances_, i)
	{
		const tnbLib::diameterModels::populationBalanceModel& popBal =
			populationBalances_[i];

		forAllConstIter(phaseSystem::phasePairTable, popBal.phasePairs(), iter)
		{
			const phasePairKey& key = iter.key();

			if (!this->phasePairs_.found(key))
			{
				this->phasePairs_.insert
				(
					key,
					autoPtr<phasePair>
					(
						new phasePair
						(
							this->phaseModels_[key.first()],
							this->phaseModels_[key.second()]
						)
						)
				);
			}
		}
	}

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
		pDmdt_.insert
		(
			pair,
			new volScalarField
			(
				IOobject
				(
					IOobject::groupName("pDmdt", pair.name()),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimDensity / dimTime, 0)
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::
~PopulationBalancePhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::dmdt
(
	const phasePairKey& key
) const
{
	return BasePhaseSystem::dmdt(key) + this->pDmdt(key);
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::volScalarField>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::dmdts() const
{
	PtrList<volScalarField> dmdts(BasePhaseSystem::dmdts());

	forAllConstIter(pDmdtTable, pDmdt_, pDmdtIter)
	{
		const phasePair& pair = this->phasePairs_[pDmdtIter.key()];
		const volScalarField& pDmdt = *pDmdtIter();

		this->addField(pair.phase1(), "dmdt", pDmdt, dmdts);
		this->addField(pair.phase2(), "dmdt", -pDmdt, dmdts);
	}

	return dmdts;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::massTransferTable>
tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::massTransfer() const
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

		// Note that the phase YiEqn does not contain a continuity error term,
		// so these additions represent the entire mass transfer

		const volScalarField dmdt(this->pDmdt(pair));
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
bool tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::read()
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


template<class BasePhaseSystem>
void tnbLib::PopulationBalancePhaseSystem<BasePhaseSystem>::solve()
{
	BasePhaseSystem::solve();

	forAll(populationBalances_, i)
	{
		populationBalances_[i].solve();
	}
}