#pragma once

#include <interfaceCompositionModel.hxx>
#include <massTransferModel.hxx>


// * * * * * * * * * * * * Private Member Functions * * * * * * * * * * * * //
  
using namespace tnbLib;

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::iDmdt
(
	const phasePairKey& key
) const
{
	tmp<volScalarField> tIDmdt = phaseSystem::dmdt(key);

	const phasePair unorderedPair
	(
		this->phases()[key.first()],
		this->phases()[key.second()]
	);

	forAllConstIter(phasePair, unorderedPair, iter)
	{
		const phaseModel& phase = iter();
		const phaseModel& otherPhase = iter.otherPhase();
		const phasePair pair(phase, otherPhase, true);

		if (interfaceCompositionModels_.found(pair))
		{
			const scalar iDmdtSign = Pair<word>::compare(pair, key);

			forAllConstIter
			(
				hashedWordList,
				interfaceCompositionModels_[pair]->species(),
				memberIter
			)
			{
				const word& member = *memberIter;

				const word name(IOobject::groupName(member, phase.name()));
				const word otherName
				(
					IOobject::groupName(member, otherPhase.name())
				);

				tIDmdt.ref() +=
					iDmdtSign
					* (
						*(*iDmdtSu_[pair])[member]
						+ *(*iDmdtSp_[pair])[member] * phase.Y(member)
						);
			}
		}
	}

	return tIDmdt;
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::
InterfaceCompositionPhaseChangePhaseSystem
(
	const fvMesh& mesh
)
	:
	BasePhaseSystem(mesh),
	nInterfaceCorrectors_
	(
		this->template lookupOrDefault<label>("nInterfaceCorrectors", 1)
	)
{
	this->generatePairsAndSubModels
	(
		"interfaceComposition",
		interfaceCompositionModels_
	);

	this->generatePairsAndSubModels
	(
		"massTransfer",
		massTransferModels_,
		false
	);

	// Check that models have been specified in the correct combinations
	forAllConstIter
	(
		interfaceCompositionModelTable,
		interfaceCompositionModels_,
		interfaceCompositionModelIter
	)
	{
		const phasePair& pair =
			this->phasePairs_[interfaceCompositionModelIter.key()];
		const phaseModel& phase = pair.phase1();
		const phaseModel& otherPhase = pair.phase2();

		if (!pair.ordered())
		{
			FatalErrorInFunction
				<< "An interfacial composition model is specified for the "
				<< "unordered " << pair << " pair. Composition models only "
				<< "apply to ordered pairs. An entry for a "
				<< phasePairKey("A", "B", true) << " pair means a model for "
				<< "the A side of the A-B interface; i.e., \"A in the presence "
				<< "of B\""
				<< exit(FatalError);
		}


		const phasePairKey key(phase.name(), otherPhase.name());

		if (!this->phasePairs_.found(key))
		{
			FatalErrorInFunction
				<< "A mass transfer model the " << key << " pair is not "
				<< "specified. This is required by the corresponding interface "
				<< "composition model."
				<< exit(FatalError);
		}

		const phasePair& uoPair = this->phasePairs_[key];

		if (!massTransferModels_[uoPair][uoPair.index(phase)].valid())
		{
			FatalErrorInFunction
				<< "A mass transfer model for the " << pair.phase1().name()
				<< " side of the " << uoPair << " pair is not "
				<< "specified. This is required by the corresponding interface "
				<< "composition model."
				<< exit(FatalError);
		}
	}
	forAllConstIter
	(
		massTransferModelTable,
		massTransferModels_,
		massTransferModelIter
	)
	{
		const phasePair& pair =
			this->phasePairs_[massTransferModelIter.key()];

		if (!this->heatTransferModels_.found(pair))
		{
			FatalErrorInFunction
				<< "A heat transfer model for " << pair << " pair is not "
				<< "specified. This is required by the corresponding species "
				<< "transfer model"
				<< exit(FatalError);
		}
	}

	// Generate mass transfer fields, initially assumed to be zero
	forAllConstIter
	(
		interfaceCompositionModelTable,
		interfaceCompositionModels_,
		interfaceCompositionModelIter
	)
	{
		const interfaceCompositionModel& compositionModel =
			interfaceCompositionModelIter();

		const phasePair& pair =
			this->phasePairs_[interfaceCompositionModelIter.key()];

		iDmdtSu_.insert(pair, new HashPtrTable<volScalarField>());
		iDmdtSp_.insert(pair, new HashPtrTable<volScalarField>());

		forAllConstIter(hashedWordList, compositionModel.species(), memberIter)
		{
			const word& member = *memberIter;

			iDmdtSu_[pair]->insert
			(
				member,
				new volScalarField
				(
					IOobject
					(
						IOobject::groupName("iDmdtSu", pair.name()),
						this->mesh().time().timeName(),
						this->mesh()
					),
					this->mesh(),
					dimensionedScalar(dimDensity / dimTime, 0)
				)
			);

			iDmdtSp_[pair]->insert
			(
				member,
				new volScalarField
				(
					IOobject
					(
						IOobject::groupName("iDmdtSp", pair.name()),
						this->mesh().time().timeName(),
						this->mesh()
					),
					this->mesh(),
					dimensionedScalar(dimDensity / dimTime, 0)
				)
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::
~InterfaceCompositionPhaseChangePhaseSystem()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class BasePhaseSystem>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::dmdt
(
	const phasePairKey& key
) const
{
	return BasePhaseSystem::dmdt(key) + this->iDmdt(key);
}


template<class BasePhaseSystem>
tnbLib::PtrList<tnbLib::volScalarField>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::dmdts() const
{
	PtrList<volScalarField> dmdts(BasePhaseSystem::dmdts());

	forAllConstIter
	(
		interfaceCompositionModelTable,
		interfaceCompositionModels_,
		interfaceCompositionModelIter
	)
	{
		const interfaceCompositionModel& compositionModel =
			interfaceCompositionModelIter();

		const phasePair& pair =
			this->phasePairs_[interfaceCompositionModelIter.key()];
		const phaseModel& phase = pair.phase1();
		const phaseModel& otherPhase = pair.phase2();

		forAllConstIter(hashedWordList, compositionModel.species(), memberIter)
		{
			const word& member = *memberIter;

			const word name(IOobject::groupName(member, phase.name()));
			const word otherName
			(
				IOobject::groupName(member, otherPhase.name())
			);

			const volScalarField iDmdt
			(
				*(*iDmdtSu_[pair])[member]
				+ *(*iDmdtSp_[pair])[member] * phase.Y(member)
			);

			this->addField(phase, "dmdt", iDmdt, dmdts);
			this->addField(otherPhase, "dmdt", -iDmdt, dmdts);
		}
	}

	return dmdts;
}


template<class BasePhaseSystem>
tnbLib::autoPtr<tnbLib::phaseSystem::massTransferTable>
tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::
massTransfer() const
{
	autoPtr<phaseSystem::massTransferTable> eqnsPtr =
		BasePhaseSystem::massTransfer();

	phaseSystem::massTransferTable& eqns = eqnsPtr();

	// Sum up the contribution from each interface composition model
	forAllConstIter
	(
		interfaceCompositionModelTable,
		interfaceCompositionModels_,
		interfaceCompositionModelIter
	)
	{
		const interfaceCompositionModel& compositionModel =
			interfaceCompositionModelIter();

		const phasePair& pair =
			this->phasePairs_[interfaceCompositionModelIter.key()];
		const phaseModel& phase = pair.phase1();
		const phaseModel& otherPhase = pair.phase2();
		const phasePair& unorderedPair =
			this->phasePairs_[phasePair(phase, otherPhase)];

		const volScalarField& Tf(*this->Tf_[unorderedPair]);

		const volScalarField K
		(
			massTransferModels_[unorderedPair][unorderedPair.index(phase)]->K()
		);

		forAllConstIter(hashedWordList, compositionModel.species(), memberIter)
		{
			const word& member = *memberIter;

			const word name(IOobject::groupName(member, phase.name()));
			const word otherName
			(
				IOobject::groupName(member, otherPhase.name())
			);

			const volScalarField KD(K * compositionModel.D(member));

			const volScalarField Yf(compositionModel.Yf(member, Tf));

			*(*iDmdtSu_[pair])[member] = phase.rho() * KD * Yf;
			*(*iDmdtSp_[pair])[member] = -phase.rho() * KD;

			const fvScalarMatrix eqn
			(
				*(*iDmdtSu_[pair])[member]
				+ fvm::Sp(*(*iDmdtSp_[pair])[member], phase.Y(member))
			);

			const volScalarField iDmdt
			(
				*(*iDmdtSu_[pair])[member]
				+ *(*iDmdtSp_[pair])[member] * phase.Y(member)
			);

			// Implicit transport through this phase
			*eqns[name] += eqn;

			// Explicit transport out of the other phase
			if (eqns.found(otherName))
			{
				*eqns[otherName] -= iDmdt;
			}
		}
	}

	return eqnsPtr;
}


template<class BasePhaseSystem>
void tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::
correctInterfaceThermo()
{
	// This loop solves for the interface temperatures, Tf, and updates the
	// interface composition models.
	//
	// The rate of heat transfer to the interface must equal the latent heat
	// consumed at the interface, i.e.:
	//
	// H1*(T1 - Tf) + H2*(T2 - Tf) == mDotL
	//                             == K*rho*(Yfi - Yi)*Li
	//
	// Yfi is likely to be a strong non-linear (typically exponential) function
	// of Tf, so the solution for the temperature is newton-accelerated

	forAllConstIter
	(
		typename BasePhaseSystem::heatTransferModelTable,
		this->heatTransferModels_,
		heatTransferModelIter
	)
	{
		const phasePair& pair =
			this->phasePairs_[heatTransferModelIter.key()];

		const phasePairKey key12(pair.first(), pair.second(), true);
		const phasePairKey key21(pair.second(), pair.first(), true);

		const volScalarField H1(heatTransferModelIter().first()->K());
		const volScalarField H2(heatTransferModelIter().second()->K());
		const dimensionedScalar HSmall("small", heatTransferModel::dimK, small);

		volScalarField& Tf = *this->Tf_[pair];

		for (label i = 0; i < nInterfaceCorrectors_; ++i)
		{
			volScalarField mDotL
			(
				IOobject
				(
					"mDotL",
					this->mesh().time().timeName(),
					this->mesh()
				),
				this->mesh(),
				dimensionedScalar(dimEnergy / dimVolume / dimTime, 0)
			);
			volScalarField mDotLPrime
			(
				IOobject
				(
					"mDotLPrime",
					this->mesh().time().timeName(),
					this->mesh()
				),
				this->mesh(),
				dimensionedScalar(mDotL.dimensions() / dimTemperature, 0)
			);

			// Add latent heats from forward and backward models
			if (this->interfaceCompositionModels_.found(key12))
			{
				this->interfaceCompositionModels_[key12]->addMDotL
				(
					massTransferModels_[pair].first()->K(),
					Tf,
					mDotL,
					mDotLPrime
				);
			}
			if (this->interfaceCompositionModels_.found(key21))
			{
				this->interfaceCompositionModels_[key21]->addMDotL
				(
					massTransferModels_[pair].second()->K(),
					Tf,
					mDotL,
					mDotLPrime
				);
			}

			// Update the interface temperature by applying one step of newton's
			// method to the interface relation
			Tf -=
				(
					H1 * (Tf - pair.phase1().thermo().T())
					+ H2 * (Tf - pair.phase2().thermo().T())
					+ mDotL
					)
				/ (
					max(H1 + H2 + mDotLPrime, HSmall)
					);

			Tf.correctBoundaryConditions();

			Info << "Tf." << pair.name()
				<< ": min = " << min(Tf.primitiveField())
				<< ", mean = " << average(Tf.primitiveField())
				<< ", max = " << max(Tf.primitiveField())
				<< endl;

			// Update the interface compositions
			if (this->interfaceCompositionModels_.found(key12))
			{
				this->interfaceCompositionModels_[key12]->update(Tf);
			}
			if (this->interfaceCompositionModels_.found(key21))
			{
				this->interfaceCompositionModels_[key21]->update(Tf);
			}
		}
	}
}


template<class BasePhaseSystem>
bool tnbLib::InterfaceCompositionPhaseChangePhaseSystem<BasePhaseSystem>::read()
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
