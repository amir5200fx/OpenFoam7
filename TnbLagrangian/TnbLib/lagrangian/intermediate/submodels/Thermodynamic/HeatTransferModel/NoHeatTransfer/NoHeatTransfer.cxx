#include <NoHeatTransfer.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoHeatTransfer<CloudType>::NoHeatTransfer
(
	const dictionary&,
	CloudType& owner
)
	:
	HeatTransferModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoHeatTransfer<CloudType>::NoHeatTransfer
(
	const NoHeatTransfer<CloudType>& htm
)
	:
	HeatTransferModel<CloudType>(htm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoHeatTransfer<CloudType>::~NoHeatTransfer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoHeatTransfer<CloudType>::active() const
{
	return false;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoHeatTransfer<CloudType>::Nu
(
	const scalar,
	const scalar
) const
{
	return 0.0;
}


template<class CloudType>
tnbLib::scalar tnbLib::NoHeatTransfer<CloudType>::Pr() const
{
	return 1.0;
}


// ************************************************************************* //