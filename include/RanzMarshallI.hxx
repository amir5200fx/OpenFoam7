#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::RanzMarshall<CloudType>::RanzMarshall
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	HeatTransferModel<CloudType>(dict, cloud, typeName)
{}


template<class CloudType>
tnbLib::RanzMarshall<CloudType>::RanzMarshall(const RanzMarshall<CloudType>& htm)
	:
	HeatTransferModel<CloudType>(htm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::RanzMarshall<CloudType>::~RanzMarshall()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::RanzMarshall<CloudType>::Nu
(
	const scalar Re,
	const scalar Pr
) const
{
	return 2.0 + 0.6*sqrt(Re)*cbrt(Pr);
}


// ************************************************************************* //