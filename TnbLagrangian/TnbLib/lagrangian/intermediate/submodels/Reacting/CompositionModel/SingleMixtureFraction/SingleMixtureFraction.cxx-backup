#include <SingleMixtureFraction.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
void tnbLib::SingleMixtureFraction<CloudType>::constructIds()
{
	forAll(this->phaseProps(), phaseI)
	{
		switch (this->phaseProps()[phaseI].phase())
		{
		case phaseProperties::GAS:
		{
			idGas_ = phaseI;
			break;
		}
		case phaseProperties::LIQUID:
		{
			idLiquid_ = phaseI;
			break;
		}
		case phaseProperties::SOLID:
		{
			idSolid_ = phaseI;
			break;
		}
		default:
		{
			FatalErrorInFunction
				<< "Unknown phase enumeration" << nl << abort(FatalError);
		}
		}
	}

	if (idGas_ < 0)
	{
		FatalErrorInFunction
			<< "No gas phase found in phase list:" << nl
			<< this->phaseTypes() << exit(FatalError);
	}
	if (idLiquid_ < 0)
	{
		FatalErrorInFunction
			<< "No liquid phase found in phase list:" << nl
			<< this->phaseTypes() << exit(FatalError);
	}
	if (idSolid_ < 0)
	{
		FatalErrorInFunction
			<< "No solid phase found in phase list:" << nl
			<< this->phaseTypes() << exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SingleMixtureFraction<CloudType>::SingleMixtureFraction
(
	const dictionary& dict,
	CloudType& owner
)
	:
	CompositionModel<CloudType>(dict, owner, typeName),

	idGas_(-1),
	idLiquid_(-1),
	idSolid_(-1),

	YMixture0_(3)
{
	constructIds();

	if (this->phaseProps().size() != 3)
	{
		FatalErrorInFunction
			<< "Incorrect number of phases: " << nl
			<< "    Please specify 1 gas, 1 liquid and 1 solid"
			<< exit(FatalError);
	}

	this->coeffDict().lookup("YGasTot0") >> YMixture0_[idGas_];
	this->coeffDict().lookup("YLiquidTot0") >> YMixture0_[idLiquid_];
	this->coeffDict().lookup("YSolidTot0") >> YMixture0_[idSolid_];

	if (mag(sum(YMixture0_) - 1.0) > small)
	{
		FatalErrorInFunction
			<< "Sum of phases should be 1. Phase fractions:" << nl
			<< YMixture0_ << exit(FatalError);
	}
}


template<class CloudType>
tnbLib::SingleMixtureFraction<CloudType>::SingleMixtureFraction
(
	const SingleMixtureFraction<CloudType>& cm
)
	:
	CompositionModel<CloudType>(cm),
	idGas_(cm.idGas_),
	idLiquid_(cm.idLiquid_),
	idSolid_(cm.idSolid_),
	YMixture0_(cm.YMixture0_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SingleMixtureFraction<CloudType>::~SingleMixtureFraction()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::scalarField&
tnbLib::SingleMixtureFraction<CloudType>::YMixture0() const
{
	return YMixture0_;
}


template<class CloudType>
tnbLib::label tnbLib::SingleMixtureFraction<CloudType>::idGas() const
{
	return idGas_;
}


template<class CloudType>
tnbLib::label tnbLib::SingleMixtureFraction<CloudType>::idLiquid() const
{
	return idLiquid_;
}


template<class CloudType>
tnbLib::label tnbLib::SingleMixtureFraction<CloudType>::idSolid() const
{
	return idSolid_;
}


// ************************************************************************* //