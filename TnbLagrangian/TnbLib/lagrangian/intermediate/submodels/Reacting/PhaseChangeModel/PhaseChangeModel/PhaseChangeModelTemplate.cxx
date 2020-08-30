#include <PhaseChangeModelTemplate.hxx>

#include <IStringStream.hxx>  // added by amir
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::wordList tnbLib::PhaseChangeModel<CloudType>::
enthalpyTransferTypeNames
(
	IStringStream
	(
		"("
		"latentHeat "
		"enthalpyDifference"
		")"
	)()
);


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<class CloudType>
typename tnbLib::PhaseChangeModel<CloudType>::enthalpyTransferType
tnbLib::PhaseChangeModel<CloudType>::wordToEnthalpyTransfer(const word& etName)
const
{
	forAll(enthalpyTransferTypeNames, i)
	{
		if (etName == enthalpyTransferTypeNames[i])
		{
			return enthalpyTransferType(i);
		}
	}

	FatalErrorInFunction
		<< "Unknown enthalpyType " << etName << ". Valid selections are:" << nl
		<< enthalpyTransferTypeNames << exit(FatalError);

	return enthalpyTransferType(0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PhaseChangeModel<CloudType>::PhaseChangeModel
(
	CloudType& owner
)
	:
	CloudSubModelBase<CloudType>(owner),
	enthalpyTransfer_(etLatentHeat),
	dMass_(0.0)
{}


template<class CloudType>
tnbLib::PhaseChangeModel<CloudType>::PhaseChangeModel
(
	const PhaseChangeModel<CloudType>& pcm
)
	:
	CloudSubModelBase<CloudType>(pcm),
	enthalpyTransfer_(pcm.enthalpyTransfer_),
	dMass_(pcm.dMass_)
{}


template<class CloudType>
tnbLib::PhaseChangeModel<CloudType>::PhaseChangeModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	enthalpyTransfer_
	(
		wordToEnthalpyTransfer(this->coeffDict().lookup("enthalpyTransfer"))
	),
	dMass_(0.0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PhaseChangeModel<CloudType>::~PhaseChangeModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const typename tnbLib::PhaseChangeModel<CloudType>::enthalpyTransferType&
tnbLib::PhaseChangeModel<CloudType>::enthalpyTransfer() const
{
	return enthalpyTransfer_;
}


template<class CloudType>
tnbLib::scalar tnbLib::PhaseChangeModel<CloudType>::dh
(
	const label idc,
	const label idl,
	const scalar p,
	const scalar T
) const
{
	return 0.0;
}


template<class CloudType>
tnbLib::scalar tnbLib::PhaseChangeModel<CloudType>::TMax
(
	const scalar p,
	const scalarField& X
) const
{
	return great;
}


template<class CloudType>
tnbLib::scalar tnbLib::PhaseChangeModel<CloudType>::Tvap(const scalarField& X) const
{
	return -great;
}


template<class CloudType>
void tnbLib::PhaseChangeModel<CloudType>::addToPhaseChangeMass(const scalar dMass)
{
	dMass_ += dMass;
}


template<class CloudType>
void tnbLib::PhaseChangeModel<CloudType>::info(Ostream& os)
{
	const scalar mass0 = this->template getBaseProperty<scalar>("mass");
	const scalar massTotal = mass0 + returnReduce(dMass_, sumOp<scalar>());

	Info << "    Mass transfer phase change      = " << massTotal << nl;

	if (this->writeTime())
	{
		this->setBaseProperty("mass", massTotal);
		dMass_ = 0.0;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <PhaseChangeModelNew.cxx>

// ************************************************************************* //