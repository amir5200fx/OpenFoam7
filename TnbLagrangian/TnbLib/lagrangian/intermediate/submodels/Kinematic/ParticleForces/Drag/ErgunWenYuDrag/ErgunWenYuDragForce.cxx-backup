#include <ErgunWenYuDragForce.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ErgunWenYuDragForce<CloudType>::ErgunWenYuDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	WenYuDragForce<CloudType>(owner, mesh, dict, typeName)
{}


template<class CloudType>
tnbLib::ErgunWenYuDragForce<CloudType>::ErgunWenYuDragForce
(
	const ErgunWenYuDragForce<CloudType>& df
)
	:
	WenYuDragForce<CloudType>(df)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ErgunWenYuDragForce<CloudType>::~ErgunWenYuDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::forceSuSp tnbLib::ErgunWenYuDragForce<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	const scalar alphac =
		this->alphacInterp().interpolate
		(
			p.coordinates(),
			p.currentTetIndices()
		);

	if (alphac < 0.8)
	{
		return forceSuSp
		(
			Zero,
			mass / p.rho()*(150 * (1 - alphac) / alphac + 1.75*Re)
			*muc / (alphac*sqr(p.d()))
		);
	}
	else
	{
		return WenYuDragForce<CloudType>::calcCoupled(p, td, dt, mass, Re, muc);
	}
}


// ************************************************************************* //