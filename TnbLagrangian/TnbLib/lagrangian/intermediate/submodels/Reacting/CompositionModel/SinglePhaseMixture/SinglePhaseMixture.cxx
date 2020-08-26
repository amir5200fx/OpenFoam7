#include <SinglePhaseMixture.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
void tnbLib::SinglePhaseMixture<CloudType>::constructIds()
{
	if (this->phaseProps().size() == 0)
	{
		FatalErrorInFunction
			<< "Phase list is empty" << exit(FatalError);
	}
	else if (this->phaseProps().size() > 1)
	{
		FatalErrorInFunction
			<< "Only one phase permitted" << exit(FatalError);
	}

	switch (this->phaseProps()[0].phase())
	{
	case phaseProperties::GAS:
	{
		idGas_ = 0;
		break;
	}
	case phaseProperties::LIQUID:
	{
		idLiquid_ = 0;
		break;
	}
	case phaseProperties::SOLID:
	{
		idSolid_ = 0;
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown phase enumeration" << abort(FatalError);
	}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SinglePhaseMixture<CloudType>::SinglePhaseMixture
(
	const dictionary& dict,
	CloudType& owner
)
	:
	CompositionModel<CloudType>(dict, owner, typeName),
	idGas_(-1),
	idLiquid_(-1),
	idSolid_(-1)
{
	constructIds();
}


template<class CloudType>
tnbLib::SinglePhaseMixture<CloudType>::SinglePhaseMixture
(
	const SinglePhaseMixture<CloudType>& cm
)
	:
	CompositionModel<CloudType>(cm),
	idGas_(cm.idGas_),
	idLiquid_(cm.idLiquid_),
	idSolid_(cm.idSolid_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SinglePhaseMixture<CloudType>::~SinglePhaseMixture()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::scalarField&
tnbLib::SinglePhaseMixture<CloudType>::YMixture0() const
{
	return this->phaseProps()[0].Y();
}


template<class CloudType>
tnbLib::label tnbLib::SinglePhaseMixture<CloudType>::idGas() const
{
	return idGas_;
}


template<class CloudType>
tnbLib::label tnbLib::SinglePhaseMixture<CloudType>::idLiquid() const
{
	return idLiquid_;
}


template<class CloudType>
tnbLib::label tnbLib::SinglePhaseMixture<CloudType>::idSolid() const
{
	return idSolid_;
}


// ************************************************************************* //