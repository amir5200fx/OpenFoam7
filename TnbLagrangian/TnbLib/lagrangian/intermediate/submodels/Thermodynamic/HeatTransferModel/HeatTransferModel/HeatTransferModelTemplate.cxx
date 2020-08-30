#include <HeatTransferModelTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::HeatTransferModel<CloudType>::HeatTransferModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner),
	BirdCorrection_(false)
{}


template<class CloudType>
tnbLib::HeatTransferModel<CloudType>::HeatTransferModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	BirdCorrection_(this->coeffDict().lookup("BirdCorrection"))
{}


template<class CloudType>
tnbLib::HeatTransferModel<CloudType>::HeatTransferModel
(
	const HeatTransferModel<CloudType>& htm
)
	:
	CloudSubModelBase<CloudType>(htm),
	BirdCorrection_(htm.BirdCorrection_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::HeatTransferModel<CloudType>::~HeatTransferModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::Switch& tnbLib::HeatTransferModel<CloudType>::BirdCorrection() const
{
	return BirdCorrection_;
}


template<class CloudType>
tnbLib::scalar tnbLib::HeatTransferModel<CloudType>::htc
(
	const scalar dp,
	const scalar Re,
	const scalar Pr,
	const scalar kappa,
	const scalar NCpW
) const
{
	const scalar Nu = this->Nu(Re, Pr);

	scalar htc = Nu * kappa / dp;

	if (BirdCorrection_ && (mag(htc) > rootVSmall) && (mag(NCpW) > rootVSmall))
	{
		const scalar phit = min(NCpW / htc, 50);
		if (phit > 0.001)
		{
			htc *= phit / (exp(phit) - 1.0);
		}
	}

	return htc;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <HeatTransferModelNew.cxx>

// ************************************************************************* //